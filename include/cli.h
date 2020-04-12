#ifndef _CLI_H_
#define _CLI_H_

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

struct Parameter {
    std::string value;
    std::string prompt;
};

const Parameter SAMPLE_RATE{"44000", "Sample rate(Hz)"};
const Parameter FILENAME{"signal.out", "File name"};
const Parameter LENGTH{"1000", "Length(ms)"};
const Parameter AMP{"1.0", "Amplitude"};
const Parameter FREQ{"440", "Frequency(Hz)"};
const Parameter PHASE{"0", "Phase shift"};
const Parameter START{"0", "Range start(ms)"};
const Parameter FINISH{"1000", "Range finish(ms)"};
const Parameter TYPE{"sin", "Wave type"};

typedef const std::vector<Parameter>& ParamList;
typedef std::unordered_map<std::string, std::function<void(ParamList)>> JumpTable;

void get_args(std::vector<Parameter>& params);
JumpTable create_table();

#endif
