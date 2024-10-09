#include <config/calc-config.h>

config::CalcConfig::CalcConfig(bool dwell_time, bool ngraph, bool pressure) {
    calc_dwell_time_ = dwell_time;
    calc_ngraph_ = ngraph;
    calc_pressure_ = pressure;
}

const bool config::CalcConfig::GetDwellTime() const { return calc_dwell_time_; }

const bool config::CalcConfig::GetNgraph() const { return calc_ngraph_; }

const bool config::CalcConfig::GetPressure() const { return calc_pressure_; }