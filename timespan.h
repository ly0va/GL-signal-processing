#ifndef _TIMESPAN_H_
#define _TIMESPAN_H_

#include "wave.h"
#include <vector>

class Timespan {
private:
    std::vector<float> samples;
    uint32_t sample_rate;
    uint32_t millis;

public:
    Timespan() = default;
    Timespan(uint32_t millis, uint32_t sample_rate);
    Timespan(const char *filename, uint32_t sample_rate);
    void save(const char *filename) const;
    void apply(const Wave& wave);
    uint32_t get_sample_rate() const;
};

#endif
