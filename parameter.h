#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include <string>

struct Parameter {
    std::string default_value;
    std::string name;
    std::string prompt;
    std::string value;
};

// namespace?
const Parameter sample_rate{"44000", "sample_rate", "Sample rate(Hz)", ""};
const Parameter filename{"signal.csv", "filename", "File name", ""};
const Parameter length{"1000", "length", "Length(ms)", ""};
const Parameter amp{"1.0", "amp", "Amplitude", ""};
const Parameter freq{"440", "freq", "Frequency", ""};
const Parameter phase{"0", "phase", "Phase shift", ""};
const Parameter start{"0", "start", "Range start(ms)", ""};
const Parameter finish{"1000", "finish", "Range finish(ms)", ""};
const Parameter type{"sin", "type", "Wave type", ""};

#endif

