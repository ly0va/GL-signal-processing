#ifndef _CLI_H_
#define _CLI_H_

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

struct Parameter {
    std::string default_value;
    std::string name;
    std::string prompt;
    std::string value;
};

const Parameter SAMPLE_RATE{"44000", "sample_rate", "Sample rate(Hz)", ""};
const Parameter FILENAME{"signal.out", "filename", "File name", ""};
const Parameter LENGTH{"1000", "length", "Length(ms)", ""};
const Parameter AMP{"1.0", "amp", "Amplitude", ""};
const Parameter FREQ{"440", "freq", "Frequency", ""};
const Parameter PHASE{"0", "phase", "Phase shift", ""};
const Parameter START{"0", "start", "Range start(ms)", ""};
const Parameter FINISH{"1000", "finish", "Range finish(ms)", ""};
const Parameter TYPE{"sin", "type", "Wave type", ""};

typedef const std::vector<Parameter>& ParamList;
typedef std::unordered_map<std::string, std::function<void(ParamList)>> JumpTable;

void get_args(std::vector<Parameter>& params);
JumpTable create_table();

#endif
