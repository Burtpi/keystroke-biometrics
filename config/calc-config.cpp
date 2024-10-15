#include <config/calc-config.h>

config::CalcConfig::CalcConfig(bool dwell_time, bool ngraph, bool pressure,
                               bool is_template_init) {
    calc_dwell_time_ = dwell_time;
    calc_ngraph_ = ngraph;
    calc_pressure_ = pressure;
    is_template_init_ = is_template_init;
}

const bool config::CalcConfig::GetDwellTime() const { return calc_dwell_time_; }

const bool config::CalcConfig::GetNgraph() const { return calc_ngraph_; }

const bool config::CalcConfig::GetPressure() const { return calc_pressure_; }

const bool config::CalcConfig::GetIsTemplateInit() const {
    return is_template_init_;
}

void config::CalcConfig::SetDwellTime(bool dwell_time) {
    calc_dwell_time_ = dwell_time;
}
void config::CalcConfig::SetNgraph(bool ngraph) { calc_ngraph_ = ngraph; }
void config::CalcConfig::SetPressure(bool pressure) {
    calc_pressure_ = pressure;
}
void config::CalcConfig::SetIsTemplateInit(bool is_template_init) {
    is_template_init_ = is_template_init;
}