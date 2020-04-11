#include "timespan.h"
#include <fstream>
#include <cmath>
#include <sndfile.h>

Timespan::Timespan(int32_t millis, int32_t sample_rate) {
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

Timespan::Timespan(const char *filename, int32_t sample_rate) {
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
    int32_t start_ind = (wave.start / 1000.0) * sample_rate;
    int32_t finish_ind = (wave.finish / 1000.0) * sample_rate;
    for (int sample = start_ind; sample < finish_ind; sample++) {
        float t = float(sample - start_ind) / sample_rate;
        if (wave.type == "sin") {
            samples[sample] += wave.amp * 
                sin(2 * M_PI * (wave.freq * t + wave.phase));
        } else if (wave.type == "tri") {
            samples[sample] += wave.amp * (2/M_PI) * 
                asin(sin(2 * M_PI * (wave.freq * t + wave.phase)));
        } else if (wave.type == "sq") {
            samples[sample] += wave.amp *
                (sin(2 * M_PI * (wave.freq * t + wave.phase)) < 0 ? -1 : 1);
        }
    }
}

int32_t Timespan::get_sample_rate() const {
    return sample_rate;
}

void Timespan::saveWAV(const char *filename) const {
    SF_INFO sfinfo ;
    sfinfo.channels = 1;
    sfinfo.samplerate = sample_rate;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    SNDFILE *outfile = sf_open(filename, SFM_WRITE, &sfinfo);
    sf_count_t cnt = sf_write_float(outfile, &samples[0], samples.size()) ;
    sf_write_sync(outfile);
    sf_close(outfile);
}

