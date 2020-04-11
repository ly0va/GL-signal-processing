#ifndef _WAVE_H_
#define _WAVE_H_
#include <inttypes.h>

struct Wave {

    enum class Type {
        Sin, Triangle
    };

    float amp;
    float phase;
    int32_t freq;
    int32_t start;
    int32_t finish;
    Type type;
};


#endif
