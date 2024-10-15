#ifndef CALC_CONFIG_H_
#define CALC_CONFIG_H_

namespace config {
class CalcConfig {
   public:
    CalcConfig(bool dwell_time = true, bool ngraph = true, bool pressure = true,
               bool is_template_init = false);
    const bool GetDwellTime() const;
    const bool GetNgraph() const;
    const bool GetPressure() const;
    const bool GetIsTemplateInit() const;
    void SetDwellTime(bool dwell_time);
    void SetNgraph(bool ngraph);
    void SetPressure(bool pressure);
    void SetIsTemplateInit(bool is_template_init);

   private:
    bool calc_dwell_time_;
    bool calc_ngraph_;
    bool calc_pressure_;
    bool is_template_init_;
};

}  // namespace config

#endif