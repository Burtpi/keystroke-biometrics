#include <database/models/key-hit.h>
#include <gsl/gsl_spline.h>
#include <include/fftw3.h>
#include <utils/math/utils-math.h>

#include <cmath>
#include <iostream>

database::models::KeyHit::KeyHit(int hid, int elapsed_time, float pressure,
                                 bool is_big, bool is_special) {
    hid_ = hid;
    time_stamps_.push_back(elapsed_time);
    pressures_.push_back(pressure);
    dwell_time_ = 0;
    total_energy_ = 0;
    is_pressed_ = true;
    was_pressed_ = true;
    is_calculated_ = false;
    is_special_char_ = is_special;
    is_big_char_ = is_big;
}

database::models::KeyHit::KeyHit() {
    is_pressed_ = false;
    was_pressed_ = true;
    is_calculated_ = false;
}

int database::models::KeyHit::GetHid() const { return hid_; }
std::vector<float> database::models::KeyHit::GetPressures() {
    return pressures_;
}
bool database::models::KeyHit::GetIsPressed() const { return is_pressed_; }
int database::models::KeyHit::GetFirstTimeStamp() const {
    return time_stamps_.front();
}
bool database::models::KeyHit::GetWasPressed() const { return was_pressed_; }
bool database::models::KeyHit::GetIsSpecial() const { return is_special_char_; }
bool database::models::KeyHit::GetIsBig() const { return is_big_char_; }
bool database::models::KeyHit::GetIsCalculated() const {
    return is_calculated_;
}
int database::models::KeyHit::GetDwellTime() const { return dwell_time_; }
double database::models::KeyHit::GetTotalEnergy() const {
    return total_energy_;
}
float database::models::KeyHit::GetMagnitude() const { return magnitude_; }

void database::models::KeyHit::PushBackTimeStamp(int time_stamp) {
    time_stamps_.push_back(time_stamp);
}
void database::models::KeyHit::PushBackPressure(float pressure) {
    pressures_.push_back(pressure);
}

void database::models::KeyHit::SetHid(int hid) { hid_ = hid; }

void database::models::KeyHit::SetIsSpecial(bool is_special) {
    is_special_char_ = is_special;
}

void database::models::KeyHit::SetIsBig(bool is_big) { is_big_char_ = is_big; }

void database::models::KeyHit::SetDwellTime(int dwell_time) {
    dwell_time_ = dwell_time;
}

void database::models::KeyHit::SetTotalEnergy(double total_energy) {
    total_energy_ = total_energy;
}

void database::models::KeyHit::SetMagnitude(float magnitude) {
    magnitude_ = magnitude;
}

void database::models::KeyHit::SetIsPressed(bool is_pressed) {
    is_pressed_ = is_pressed;
}

void database::models::KeyHit::SetWasPressed(bool was_pressed) {
    was_pressed_ = was_pressed;
}

void database::models::KeyHit::SetIsCalculated(bool is_calculated) {
    is_calculated_ = is_calculated;
}

void database::models::KeyHit::UpdateKeyHit(int elapsed_time, float pressure) {
    time_stamps_.push_back(elapsed_time);
    pressures_.push_back(pressure);
}

void database::models::KeyHit::Calculate() {
    CalculateDwellTime();
    Interpolate();
    CalculateDFTOfPressure();
}

void database::models::KeyHit::CalculateDwellTime() {
    dwell_time_ = time_stamps_.back() - time_stamps_.front();
}

void database::models::KeyHit::Interpolate() {
    std::vector<int> time_stamps_copy = time_stamps_;
    std::vector<float> pressure_copy = pressures_;

    for (int i = 0; i < pressure_copy.size();) {
        if (pressure_copy[i] == 1.0) {
            time_stamps_copy.erase(time_stamps_copy.begin() + i);
            pressure_copy.erase(pressure_copy.begin() + i);
        } else {
            ++i;
        }
    }
    double *time_stamps_array = new double[time_stamps_copy.size()];
    double *pressure_array = new double[pressure_copy.size()];

    for (size_t i = 0; i < time_stamps_copy.size(); ++i) {
        time_stamps_array[i] = static_cast<double>(time_stamps_copy[i]);
        pressure_array[i] = static_cast<double>(pressure_copy[i]);
    }

    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline *spline =
        gsl_spline_alloc(gsl_interp_akima, time_stamps_copy.size());

    gsl_spline_init(spline, time_stamps_array, pressure_array,
                    time_stamps_copy.size());

    for (int i = time_stamps_copy.front(); i <= time_stamps_copy.back(); ++i) {
        time_stamps_interp_.push_back(i);
    }
    for (int i = 0; i < time_stamps_interp_.size(); ++i) {
        float new_pressure = static_cast<float>(
            gsl_spline_eval(spline, time_stamps_interp_[i], acc));
        pressures_interp_.push_back(new_pressure);
    }
    delete[] time_stamps_array;
    delete[] pressure_array;
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
}

void database::models::KeyHit::CalculateDFTOfPressure() {
    int N = static_cast<int>(pressures_interp_.size());
    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    for (int i = 0; i < N; i++) {
        in[i][0] = pressures_interp_[i];
        in[i][1] = 0.0;
    }
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    CalculateMagnitude(out, N);
    CalculateTotalEnergy(out, N);

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

void database::models::KeyHit::CalculateMagnitude(fftw_complex *out, int size) {
    std::vector<float> magnitudes;
    for (int i = 0; i < size; i++) {
        float magnitude = static_cast<float>(
            std::sqrt(std::pow(out[i][0], 2) + std::pow(out[i][1], 2)));
        magnitudes.push_back(magnitude);
    }
    magnitude_ = static_cast<float>(utils::math::CalculateMean(magnitudes));
}

void database::models::KeyHit::CalculateTotalEnergy(fftw_complex *out,
                                                    int size) {
    for (int i = 0; i < size; i++) {
        total_energy_ += std::pow(out[i][0], 2) + std::pow(out[i][1], 2);
    }
}

void database::models::KeyHit::SaveKeyHitToCsv(std::ofstream &file) const {
    if (dwell_time_ > 0 && dwell_time_ <= 500 && total_energy_ > 0 &&
        magnitude_ > 0) {
        file << hid_ << "," << is_special_char_ << "," << is_big_char_ << ","
             << dwell_time_ << "," << total_energy_ << "," << magnitude_
             << ",{";
        bool first_iter = true;

        auto save_iter = [&file, &first_iter](auto entries) {
            for (const auto &entry : entries) {
                if (!first_iter) {
                    file << ",";
                }
                file << entry;
                first_iter = false;
            }
        };
        save_iter(time_stamps_);
        file << "},{";
        first_iter = true;
        save_iter(pressures_);
        file << "}\n";
    }
}