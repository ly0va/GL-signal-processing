#include "timespan.h"
#include <fstream>
#include <cmath>

Timespan::Timespan(uint32_t millis, uint32_t sample_rate) {
    this->millis = millis;
    this->sample_rate = sample_rate;
    uint32_t n_samples = (millis / 1000.0) * sample_rate;
    samples.resize(n_samples);
}

void Timespan::save(const char *filename) const {
    // TODO: issue a warning to cerr if overriding existing file
    std::ofstream output(filename);
    for (float sample: samples) {
        output << sample << '\n';
    }
    output.close();
}

Timespan::Timespan(const char *filename, uint32_t sample_rate) {
    // TODO: issue an error/warning if filename don't exist
    // or incorrect format
    std::ifstream input(filename);
    float sample;
    while (input >> sample) {
        samples.push_back(sample);
    }
    this->sample_rate = sample_rate;
    millis = samples.size() * 1000 / sample_rate;
}

void Timespan::apply(const Wave& wave) {
    if (wave.finish > millis) return; // FIXME
    uint32_t start_ind = (wave.start / 1000.0) * sample_rate;
    uint32_t finish_ind = (wave.finish / 1000.0) * sample_rate;
    for (int sample = start_ind; sample < finish_ind; sample++) {
        float t = float(sample - start_ind) / sample_rate;
        if (wave.type == Wave::Type::Sin) {
            samples[sample] += wave.amp * 
                sin(2 * M_PI * (wave.freq * t + wave.phase));
        } else if (wave.type == Wave::Type::Triangle) {
            samples[sample] += wave.amp * (2/M_PI) * 
                asin(sin(2 * M_PI * (wave.freq * t + wave.phase)));
        }
    }
}

uint32_t Timespan::get_sample_rate() const {
    return sample_rate;
}
