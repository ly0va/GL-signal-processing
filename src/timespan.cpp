#include "timespan.h"
#include <fstream>
#include <cmath>
#include <sndfile.h>
#include <stdexcept>

Timespan::Timespan(int32_t len, int32_t sample_rate) {
    this->len = len;
    this->sample_rate = sample_rate;
    uint32_t n_samples = (len / 1000.0) * sample_rate;
    samples.resize(n_samples);
}

void Timespan::saveCSV(const char *filename) const {
    std::ofstream output(filename);
    if (!output.is_open()) {
        throw std::runtime_error("Unable to open the file");
    }
    for (float sample: samples) {
        output << sample << '\n';
    }
    output.close();
}

Timespan::Timespan(const char *filename, int32_t sample_rate) {
    std::ifstream input(filename);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open the file");
    }
    float sample;
    while (input >> sample) {
        samples.push_back(sample);
    }
    this->sample_rate = sample_rate;
    len = samples.size() * 1000 / sample_rate;
}

void Timespan::apply(const Wave& wave) {
    if (wave.finish > len || wave.start < 0) {
        throw std::invalid_argument("Wave goes beyond the timespan");
    }
    int32_t start_ind = (wave.start / 1000.0) * sample_rate;
    int32_t finish_ind = (wave.finish / 1000.0) * sample_rate;
    for (int sample = start_ind; sample < finish_ind; sample++) {
        float t = float(sample - start_ind) / sample_rate;
        if (wave.type == SINE) {
            samples[sample] += wave.amp * 
                sin(2 * M_PI * (wave.freq * t + wave.phase));
        } else if (wave.type == TRIANGLE) {
            samples[sample] += wave.amp * (2/M_PI) * 
                asin(sin(2 * M_PI * (wave.freq * t + wave.phase)));
        } else if (wave.type == RECT) {
            samples[sample] += wave.amp *
                (sin(2 * M_PI * (wave.freq * t + wave.phase)) < 0 ? -1 : 1);
        }
    }
}

void Timespan::show(const char *filename) const {
    std::string graph_cmd = "/usr/bin/python3 graph.py ";
    graph_cmd += filename;
    graph_cmd += " " + std::to_string(sample_rate);
    system(graph_cmd.c_str());
}

int32_t Timespan::get_len() const {
    return len;
}

int32_t Timespan::get_sample_rate() const {
    return sample_rate;
}
