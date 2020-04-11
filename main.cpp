#include <bits/stdc++.h>
#include "timespan.h"
#include "parameter.h"

using namespace std;

void get_args(vector<Parameter>& params) {
    for (auto& param: params) {
        cout << ' ' << param.prompt << " [" 
             << param.default_value << "]: ";
        getline(cin, param.value);
        if (param.value == "\n" || param.value == "") {
            param.value = param.default_value;
        }
    }
}

void help() {
    cout << "HELP!!\n";
}

void main_loop() {
    string cmd;
    vector<Parameter> params;
    Timespan ts;
    do {
        cout << "> ";
        getline(cin, cmd);
        if (cmd == "new") {
            params = {length, sample_rate};
            get_args(params);
            ts = Timespan(stoi(params[0].value), stoi(params[1].value));
        } else if (cmd == "gen" || cmd == "generate") {
            params = {amp, phase, freq, start, finish, type};
            get_args(params);
            Wave wave{
                stof(params[0].value), 
                stof(params[1].value), 
                stoi(params[2].value), 
                stoi(params[3].value), 
                stoi(params[4].value), 
                params[5].value == "sin" 
                    ? Wave::Type::Sin 
                    : Wave::Type::Triangle
            };
            ts.apply(wave);
        } else if (cmd == "save") {
            params = {filename};
            get_args(params);
            ts.save(params[0].value.c_str());
        } else if (cmd == "load") {
            params = {filename, sample_rate};
            get_args(params);
            ts = Timespan(params[0].value.c_str(), stoi(params[1].value));
        } else if (cmd == "help") {
            help();
        } else if (cmd == "show") {
            ts.save("/tmp/_.csv");
            string graph_cmd =  "./graph.py /tmp/_.csv " + to_string(ts.get_sample_rate());
            system(graph_cmd.c_str());
        } else if (cmd != "quit") {
            cerr << "Invalid command!\n";
        }
    } while (cmd != "quit");
}


int main(int argc, char **argv) {
    main_loop();
    return 0;
}

