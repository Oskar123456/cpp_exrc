/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"
#include "../../include/obh/util.hpp"

#include "raylib.h"

using namespace std;

struct gate {
    int id;
    string a, b, out;
    string op;
    bool done;
};

void aoc24_2()
{
    i64 result = 0;

    vector<gate> gates;
    map<string, int> signals;
    vector<pair<string, string>> signal_deps;

    string line;
    /* ifstream input("aoc_24_data.txt", ios_base::in); */
    ifstream input("resources/aoc_data/aoc_24_data.txt", ios_base::in);
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
            signals.emplace(line_split[0], -1);
            signals.emplace(line_split[2], -1);
            signals.emplace(line_split[4], -1);
            gates.push_back({(int)gates.size(), line_split[0], line_split[2], line_split[4], line_split[1], false});
            signal_deps.push_back(make_pair(line_split[4], line_split[0]));
            signal_deps.push_back(make_pair(line_split[4], line_split[2]));
        }
    }


    /* const int screenWidth = 800; */
    /* const int screenHeight = 450; */
    /* InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing"); */
    /* SetExitKey(0); */
    /* SetTargetFPS(60);               // Set our game to run at 60 frames-per-second */
    /* //-------------------------------------------------------------------------------------- */

    /* // Main game loop */
    /* while (!WindowShouldClose())    // Detect window close button or ESC key */
    /* { */
    /*     // Update */
    /*     //---------------------------------------------------------------------------------- */
    /*     //---------------------------------------------------------------------------------- */

    /*     // Draw */
    /*     //---------------------------------------------------------------------------------- */
    /*     BeginDrawing(); */
    /*         ClearBackground(RAYWHITE); */
    /*         DrawText("some basic shapes available on raylib", 20, 20, 20, DARKGRAY); */
    /*     EndDrawing(); */
    /*     //---------------------------------------------------------------------------------- */
    /* } */
    /* // De-Initialization */
    /* //-------------------------------------------------------------------------------------- */
    /* CloseWindow();        // Close window and OpenGL context */
    /* //-------------------------------------------------------------------------------------- */

    printf("aoc24_2:  \t%ld\n", result);
}

void aoc24()
{
    i64 result = 0;

    vector<gate> gates;
    map<string, int> signals;
    vector<pair<string, string>> signal_deps;

    string line;
    /* ifstream input("aoc_24_data.txt", ios_base::in); */
    ifstream input("resources/aoc_data/aoc_24_data.txt", ios_base::in);
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
            signals.emplace(line_split[0], -1);
            signals.emplace(line_split[2], -1);
            signals.emplace(line_split[4], -1);
            gates.push_back({(int)gates.size(), line_split[0], line_split[2], line_split[4], line_split[1], false});
            signal_deps.push_back(make_pair(line_split[4], line_split[0]));
            signal_deps.push_back(make_pair(line_split[4], line_split[2]));
        }
    }

/*     for (auto sb : signals) */
/*         cout << sb.first << "," << sb.second << endl; */
/*     for (auto g : gates) */
/*         cout << g.a << " " << g.op << " " << g.b << " (" << g.id << ")" << endl; */
/*     for (auto sd : signal_deps) */
/*         cout << sd.first << " deps on " << sd.second << endl; */

    int done = 0;
    while (done < gates.size()) {
        for (int i = 0; i < gates.size(); ++i) {
            gate g = gates[i];
            int a_val = signals[g.a];
            int b_val = signals[g.b];
            if (g.done || a_val < 0 || b_val < 0)
                continue;
            gates[i].done = true;
            if (g.op == "AND") signals[g.out] = a_val & b_val;
            if (g.op == "OR") signals[g.out]  = a_val | b_val;
            if (g.op == "XOR") signals[g.out] = a_val ^ b_val;
            /* printf("update %s to %d\n", g.out.c_str(), signals[g.out]); */
            done++;
        }
    }

    for (auto sb : signals)
        cout << sb.first << "," << sb.second << endl;

    int i = 0;
    for (auto s : signals) {
        if (s.first[0] != 'z')
            continue;
        result += (i64)s.second << i++;
    }

    printf("aoc24:  \t%ld\n", result);
}

















