/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"
#include "../../include/obh/util.hpp"

using namespace std;

struct gate {
    int id;
    string a, b;
    string op;
};

void aoc24_2()
{
}

void aoc24()
{
    i64 result = 0;

    vector<gate> gates;
    map<string, bool> signals;
    map<string, int> signal_deps;

    string line;
    ifstream input("aoc_24_data.txt", ios_base::in);
    /* ifstream input("resources/aoc_data/aoc_24_data.txt", ios_base::in); */
    int mode = 0;
    while (getline(input, line, '\n')) {
        if (line.length() < 1) {
            mode = 1;
            continue;
        }
        if (mode == 0) {
            int i = line.find_first_of(' ');
            signals.emplace(line.substr(0, i - 1), stoi(line.substr(i + 1)));
        }
        if (mode == 1) {
            vector<string> line_split(1);
            for (char c : line) {
                if (c == ' ') {
                    string s;
                    line_split.push_back(s);
                    continue;
                }
                line_split[line_split.size() - 1].push_back(c);
            }
            gates.push_back({(int)gates.size(), line_split[0], line_split[2], line_split[1]});
            signal_deps.emplace(line_split[4], gates.size() - 1);
        }
    }

    for (auto sb : signals)
        cout << sb.first << "," << sb.second << endl;
    for (auto g : gates)
        cout << g.a << " " << g.op << " " << g.b << " (" << g.id << ")" << endl;
    for (auto sd : signal_deps)
        cout << sd.first << " deps on " << sd.second << endl;

    printf("aoc24:  \t%ld\n", result);
}

















