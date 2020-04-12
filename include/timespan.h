#ifndef _TIMESPAN_H_
#define _TIMESPAN_H_

#include "wave.h"
#include <vector>

class Timespan {
private:
    std::vector<float> samples;
    int32_t sample_rate;
    int32_t millis;

public:
    Timespan(int32_t millis = 1000, int32_t sample_rate = 44000);
    Timespan(const char *filename, int32_t sample_rate);
    void saveCSV(const char *filename) const;
    void saveWAV(const char *filename) const;
    void apply(const Wave& wave);
    void show(const char *filename) const;
};

#endif
