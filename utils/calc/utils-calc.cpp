#include <config/config-manager.h>
#include <database/database.h>
#include <database/models/key-hit.h>
#include <database/models/ngraph.h>
#include <database/templates/template-container.h>
#include <utils/calc/utils-calc.h>
#include <utils/math/utils-math.h>

#include <optional>
#include <vector>

void utils::calc::CalculateCurrentObjects() {
    std::vector<database::models::KeyHit>& key_hits =
        database_manager.GetKeyHitContainer().GetEntries();
    std::vector<database::models::KeyHit>& modifier_keys =
        database_manager.GetModifierKeyHitContainer().GetEntries();

    CalculateKeyHits(key_hits);
    CalculateKeyHits(modifier_keys);
    CalculateNgraphs();
}

void utils::calc::CalculateKeyHits(
    std::vector<database::models::KeyHit>& key_hits) {
    std::vector<database::models::CalcTemplate>& calc_templates =
        database_manager.GetTemplateContainer().GetCalcTemplate();

    for (database::models::KeyHit& key_hit : key_hits) {
        CalculateKeyHit(key_hit, calc_templates);
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

    std::optional<database::models::CalcKeyHit>& calc_key_hit =
        calc_template.calc_key_hit_container.FindEntry(key_hit);

    if (calc_key_hit) {
        double score;
        if (global_config_manager.GetCalcConfig().GetDwellTime()) {
            score = utils::math::CalculateZScore(
                key_hit.GetDwellTime(), calc_key_hit->GetDwellTime().mean,
                calc_key_hit->GetDwellTime().std_deviation);
            z_scores.push_back(CalculateScore(score));
        }
        if (global_config_manager.GetCalcConfig().GetPressure()) {
            score = utils::math::CalculateZScore(
                key_hit.GetTotalEnergy(), calc_key_hit->GetTotalEnergy().mean,
                calc_key_hit->GetTotalEnergy().std_deviation);
            z_scores.push_back(CalculateScore(score));

            score = utils::math::CalculateZScore(
                key_hit.GetMagnitude(), calc_key_hit->GetMagnitude().mean,
                calc_key_hit->GetMagnitude().std_deviation);
            z_scores.push_back(CalculateScore(score));
        }
        CalculateZScores(z_scores, calc_template);
    }
}

void utils::calc::CalculateNgraphs() {
    std::vector<database::models::Ngraph>& ngraphs =
        database_manager.GetNgraphContainer().GetEntries();
    std::vector<database::models::CalcTemplate>& calc_templates =
        database_manager.GetTemplateContainer().GetCalcTemplate();

    for (database::models::Ngraph& ngraph : ngraphs) {
        if (!ngraph.GetIsCalculated()) {
            CalculateNgraph(ngraph, calc_templates);
        }
    }
}

void utils::calc::CalculateNgraph(
    database::models::Ngraph& ngraph,
    std::vector<database::models::CalcTemplate>& calc_templates) {
    for (database::models::CalcTemplate& calc_template : calc_templates) {
        CalculateNgraphTemplateScore(calc_template, ngraph);
    }
    ngraph.SetIsCalculated(true);
}

void utils::calc::CalculateNgraphTemplateScore(
    database::models::CalcTemplate& calc_template,
    database::models::Ngraph& ngraph) {
    std::vector<double> z_scores;

    std::optional<database::models::CalcNgraph>& calc_ngraph =
        calc_template.calc_ngraph_container.FindEntry(ngraph);

    if (calc_ngraph) {
        double score;
        if (global_config_manager.GetCalcConfig().GetNgraph()) {
            score = utils::math::CalculateZScore(
                ngraph.GetFlightTime(), calc_ngraph->GetFlightTime().mean,
                calc_ngraph->GetFlightTime().std_deviation);
            z_scores.push_back(CalculateScore(score));
        }
        CalculateZScores(z_scores, calc_template);
    }
}

double utils::calc::CalculateScore(double score) {
    if (score >= 3 && score <= 5)
        return 3;
    else if (score <= -3 && score >= -5)
        return -3;
    else if (score < 3 && score > -3)
        return score;
}

void utils::calc::CalculateZScores(
    std::vector<double> z_scores,
    database::models::CalcTemplate& calc_template) {
    if (!z_scores.empty()) {
        double z_score =
            round(std::abs(utils::math::CalculateMean(z_scores)) * 10000) /
            10000;
        calc_template.score += (1 - z_score);
    }
}