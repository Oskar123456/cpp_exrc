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

#define H 5
#define W 5

void aoc25_2()
{
    i64 result = 0;

    vector<vector<int>> keys;
    vector<vector<int>> locks;

    string line;
    /* ifstream input("aoc_25_data.txt", ios_base::in); */
    ifstream input("resources/aoc_data/aoc_25_data.txt", ios_base::in);
    while (getline(input, line, '\n')) {
        if (line.length() < 2) continue;

        bool iskey = line[0] == '#';

        vector<int> lines(W);
        for (int i = 0; i < H; ++i) {
            getline(input, line, '\n');
            for (int j = 0; j < W; ++j)
                lines[j] += (line[j] == '#');
        }
        if (iskey) keys.push_back(lines);
        else locks.push_back(lines);
        getline(input, line, '\n');
    }

    printf("aoc25_2:  \t%ld\n", result);
}

void aoc25()
{
    i64 result = 0;

    vector<vector<int>> keys;
    vector<vector<int>> locks;

    string line;
    /* ifstream input("aoc_25_data.txt", ios_base::in); */
    ifstream input("resources/aoc_data/aoc_25_data.txt", ios_base::in);
    while (getline(input, line, '\n')) {
        if (line.length() < 2) continue;

        bool iskey = line[0] == '#';

        vector<int> lines(W);
        for (int i = 0; i < H; ++i) {
            getline(input, line, '\n');
            for (int j = 0; j < W; ++j)
                lines[j] += (line[j] == '#');
        }
        if (iskey) keys.push_back(lines);
        else locks.push_back(lines);
        getline(input, line, '\n');
    }

    for (auto k : keys) {
        for (auto l : locks) {
            bool match = true;
            for (int i = 0; i < W; ++i)
                if (k[i] + l[i] > H)
                    match = false;
            if (match) {
                cout << "key ";
                for (int j = 0; j < W; ++j)
                    cout << k[j] << ",";
                cout << " matches lock ";
                for (int j = 0; j < W; ++j)
                    cout << l[j] << ",";
                cout << endl;

                result++;
            }
            else {
                cout << "key ";
                for (int j = 0; j < W; ++j)
                    cout << k[j] << ",";
                cout << " doesn't match lock ";
                for (int j = 0; j < W; ++j)
                    cout << l[j] << ",";
                cout << endl;
            }
        }
    }


    printf("aoc25:  \t%ld\n", result);
}

















