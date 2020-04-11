#include "timespan.h"
#include "cli.h"
#include <iostream>

static const char *HELP = R"(COMMANDS:
    new         - create a new timespan
    gen         - generate a new wave
    load        - load timespan from .csv file
    save-csv    - save timespan to .csv file
    save-wav    - save timespan to .wav file
    help        - show this help
    show        - show the timespan graph (uses graph.py)
    play        - plays the timespan (requires mpv)
    quit        - quit the program
)";

void get_args(std::vector<Parameter>& params) {
    for (auto& param: params) {
        std::cout << param.prompt << " [" 
             << param.default_value << "]: ";
        std::getline(std::cin, param.value);
        if (param.value == "\n" || param.value == "") {
            param.value = param.default_value;
        }
    }
}

JumpTable create_table() {
    static Timespan ts;
    JumpTable jump_table;
    jump_table["new"] = [&](ParamList params) {
        ts = Timespan(stoi(params[0].value), stoi(params[1].value));
    };
    jump_table["gen"] = [&](ParamList params) {
        Wave wave{
            stof(params[0].value), 
            stof(params[1].value), 
            stoi(params[2].value), 
            stoi(params[3].value), 
            stoi(params[4].value), 
            params[5].value
        };
        ts.apply(wave);
    };
    jump_table["save-csv"] = [&](ParamList params) {
        ts.save(params[0].value.c_str());
    };
    jump_table["load"] = [&](ParamList params) {
        ts = Timespan(params[0].value.c_str(), stoi(params[1].value));
    };
    jump_table["show"] = [&](ParamList params) {
        ts.save("/tmp/_.csv");
        std::string graph_cmd = "./graph.py /tmp/_.csv " 
                + std::to_string(ts.get_sample_rate());
        system(graph_cmd.c_str());
    };
    jump_table["help"] = [&](ParamList params) {
        std::cout << HELP;
    };
    jump_table["save-wav"] = [&](ParamList params) {
        ts.saveWAV(params[0].value.c_str());
    };
    jump_table["play"] = [&](ParamList params) {
        ts.saveWAV("/tmp/_.wav");
        system("mpv /tmp/_.wav");
    };
    return jump_table;
}

