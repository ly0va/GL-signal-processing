#ifndef _WAVE_H_
#define _WAVE_H_

#include <inttypes.h>
#include <string>

struct Wave {
    float amp;
    float phase;
    int32_t freq;
    int32_t start;
    int32_t finish;
    std::string type;
};

#endif
