#include <config/config-manager.h>
#include <database/database.h>
#include <database/models/key-hit.h>
#include <database/models/ngraph.h>
#include <database/templates/template-container.h>
#include <utils/calc/utils-calc.h>
#include <utils/math/utils-math.h>

#include <iostream>
#include <optional>
#include <vector>

void utils::calc::CalculateCurrentObjects() {
    database_manager.GetMergedObjectsContainer().Sort();

    std::vector<database::containers::MergedObjectsVariant>& merged_objects =
        database_manager.GetMergedObjectsContainer().GetEntries();

    std::vector<database::models::CalcTemplate>& calc_templates =
        database_manager.GetTemplateContainer().GetCalcTemplate();

    for (database::containers::MergedObjectsVariant& object : merged_objects) {
        if (database::models::KeyHit* key_hit =
                std::get_if<database::models::KeyHit>(&object)) {
            CalculateKeyHit(*key_hit, calc_templates);
        } else if (database::models::Ngraph* ngraph =
                       std::get_if<database::models::Ngraph>(&object)) {
            CalculateNgraph(*ngraph, calc_templates);
        }
    }
}

void utils::calc::CalculateKeyHit(
    database::models::KeyHit& key_hit,
    std::vector<database::models::CalcTemplate>& calc_templates) {
    if (key_hit.GetIsPressed() == false && key_hit.GetIsCalculated() == false) {
        for (database::models::CalcTemplate& calc_template : calc_templates) {
            CalculateKeyHitTemplateScore(calc_template, key_hit);
        }
        key_hit.SetIsCalculated(true);
    }
}

void utils::calc::CalculateKeyHitTemplateScore(
    database::models::CalcTemplate& calc_template,
    database::models::KeyHit& key_hit) {
    std::vector<double> z_scores;

    std::optional<database::models::CalcKeyHit> calc_key_hit =
        calc_template.calc_key_hit_container.FindEntry(key_hit);
    if (calc_key_hit.has_value()) {
        double score;
        if (global_config_manager.GetCalcConfig().GetDwellTime() &&
            key_hit.GetDwellTime() <= 500) {
            score = utils::math::CalculateZScore(
                key_hit.GetDwellTime(), calc_key_hit->GetDwellTime().mean,
                calc_key_hit->GetDwellTime().std_deviation);
            std::optional<double> z_score_dwell = CalculateScore(score);
            if (z_score_dwell.has_value())
                z_scores.push_back(z_score_dwell.value());
        }
        if (global_config_manager.GetCalcConfig().GetPressure()) {
            score = utils::math::CalculateZScore(
                key_hit.GetTotalEnergy(), calc_key_hit->GetTotalEnergy().mean,
                calc_key_hit->GetTotalEnergy().std_deviation);
            std::optional<double> z_score_energy = CalculateScore(score);
            if (z_score_energy.has_value())
                z_scores.push_back(z_score_energy.value());

            score = utils::math::CalculateZScore(
                key_hit.GetMagnitude(), calc_key_hit->GetMagnitude().mean,
                calc_key_hit->GetMagnitude().std_deviation);
            std::optional<double> z_score_magnitude = CalculateScore(score);
            if (z_score_magnitude.has_value())
                z_scores.push_back(z_score_magnitude.value());
        }
        CalculateZScores(z_scores, calc_template);
    }
}

void utils::calc::CalculateNgraph(
    database::models::Ngraph& ngraph,
    std::vector<database::models::CalcTemplate>& calc_templates) {
    if (!ngraph.GetIsCalculated()) {
        for (database::models::CalcTemplate& calc_template : calc_templates) {
            CalculateNgraphTemplateScore(calc_template, ngraph);
        }
        ngraph.SetIsCalculated(true);
    }
}

void utils::calc::CalculateNgraphTemplateScore(
    database::models::CalcTemplate& calc_template,
    database::models::Ngraph& ngraph) {
    std::vector<double> z_scores;

    std::optional<database::models::CalcNgraph> calc_ngraph =
        calc_template.calc_ngraph_container.FindEntry(ngraph);

    if (calc_ngraph.has_value()) {
        double score;
        if (global_config_manager.GetCalcConfig().GetNgraph() &&
            ngraph.GetFlightTime() <= 1000) {
            score = utils::math::CalculateZScore(
                ngraph.GetFlightTime(), calc_ngraph->GetFlightTime().mean,
                calc_ngraph->GetFlightTime().std_deviation);
            std::optional<double> z_score = CalculateScore(score);
            if (z_score.has_value()) z_scores.push_back(z_score.value());
        }
        CalculateZScores(z_scores, calc_template);
    }
}

std::optional<double> utils::calc::CalculateScore(double score) {
    if (score >= 3 && score <= 5)
        return 3;
    else if (score <= -3 && score >= -5)
        return -3;
    else if (score < 3 && score > -3)
        return score;
    else
        return std::nullopt;
}

void utils::calc::CalculateZScores(
    std::vector<double> z_scores,
    database::models::CalcTemplate& calc_template) {
    if (!z_scores.empty()) {
        double z_score =
            round(std::abs(utils::math::CalculateMean(z_scores)) * 10000) /
            10000;
        if (z_score > 1) {
            z_score *= 2;
        }
        calc_template.score += (1 - z_score);

        if (calc_template.score >= 100) {
            calc_template.score = 100;
        } else if (calc_template.score <= 0) {
            calc_template.score = 0;
        }
    }
}