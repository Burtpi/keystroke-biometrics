#ifndef CALC_CONFIG_H_
#define CALC_CONFIG_H_

namespace config {
class CalcConfig {
   public:
    CalcConfig(bool dwell_time = true, bool ngraph = true,
               bool pressure = true);
    const bool GetDwellTime() const;
    const bool GetNgraph() const;
    const bool GetPressure() const;

   private:
    bool calc_dwell_time_;
    bool calc_ngraph_;
    bool calc_pressure_;
};

}  // namespace config

#endif