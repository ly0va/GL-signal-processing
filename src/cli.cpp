#include "timespan.h"
#include "cli.h"
#include "player.h"
#include <iostream>
#include <stdexcept>

static const char *HELP = R"(COMMANDS:
    new         - create a new timespan
    gen         - generate a new wave (types are: sin, tri, rect)
    load        - load timespan from .csv file
    save-csv    - save timespan to .csv file
    save-wav    - save timespan to .wav file
    help        - show this help
    info        - show info about current timespan
    show        - show the timespan graph (uses graph.py)
    play        - plays the timespan (requires mpv)
    quit        - quit the program
)";

static const char *TEMP_CSV = "/tmp/temp-signal.csv";
static const char *TEMP_WAV = "/tmp/temp-signal.wav";

void get_args(std::vector<Parameter>& params) {
    std::string value;
    for (auto& param: params) {
        std::cout << param.prompt << " [" 
                  << param.value /* default value */ << "]: ";
        std::getline(std::cin, value);
        if (value != "") {
            param.value = value;
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
        char type = params[5].value[0];
        if (type != 's' && type != 'r' && type != 't') {
            throw std::invalid_argument("Invalid wave type");
        }
        std::string finish = params[4].value;
        Wave wave{
            stof(params[0].value), 
            stof(params[1].value), 
            stoi(params[2].value), 
            stoi(params[3].value), 
            finish == FINISH.value
                ? ts.get_len()
                : stoi(finish),
            params[5].value[0]
        };
        ts.apply(wave);
    };
    jump_table["save-csv"] = [&](ParamList params) {
        ts.saveCSV(params[0].value.c_str());
    };
    jump_table["load"] = [&](ParamList params) {
        ts = Timespan(params[0].value.c_str(), stoi(params[1].value));
    };
    jump_table["show"] = [&](ParamList params) {
        ts.saveCSV(TEMP_CSV);
        ts.show(TEMP_CSV);
    };
    jump_table["help"] = [&](ParamList params) {
        std::cout << HELP;
    };
    jump_table["save-wav"] = [&](ParamList params) {
        ts.saveWAV(params[0].value.c_str());
    };
    jump_table["play"] = [&](ParamList params) {
        ts.saveWAV(TEMP_WAV);
        playWAV(TEMP_WAV);
    };
    jump_table["info"] = [&](ParamList params) {
        std::cout << "Current timespan info:\n"
                  << "  Duration:    " << ts.get_len() << " ms\n"
                  << "  Sample rate: " << ts.get_sample_rate() << " Hz\n";
    };
    return jump_table;
}


