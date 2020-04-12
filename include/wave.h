#ifndef _WAVE_H_
#define _WAVE_H_

#include <inttypes.h>

const char TRIANGLE = 't';
const char SINE = 's';
const char RECT = 'r';

struct Wave {
    float amp;
    float phase;
    int32_t freq;
    int32_t start;
    int32_t finish;
    char type;
};

#endif
