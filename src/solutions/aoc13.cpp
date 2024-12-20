/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"

void aoc13()
{
    using namespace std;
    u64 result = 0;

    ifstream input("resources/aoc_data/aoc_13_data.txt", ios::in);

    vector<vector<u64>> a_vals;
    vector<vector<u64>> b_vals;
    vector<vector<u64>> xy_vals;

    int m = 0;;
    string line;
    while (getline(input, line)) {
        if (line.length() < 2)
            continue;
        vector<u64> vals;
        const char *line_ptr = line.c_str();
        while (*line_ptr) {
            if (!isdigit(*line_ptr)) {
                line_ptr++;
                continue;
            }
            char *end_ptr;
            i64 val = strtol(line_ptr, &end_ptr, 10);
            vals.push_back(val);
            line_ptr = end_ptr;
        }
        if (m == 0) a_vals.push_back(vals);
        if (m == 1) b_vals.push_back(vals);
        if (m == 2) xy_vals.push_back(vals);
        m = (m + 1) % 3;
    }

    for (int i = 0; i < (int)a_vals.size(); ++i) {
        i64 xa = a_vals[i][0];
        i64 ya = a_vals[i][1];

        i64 xb = b_vals[i][0];
        i64 yb = b_vals[i][1];

        i64 x0 = xy_vals[i][0];
        i64 y0 = xy_vals[i][1];

        i64 b = (x0 * ya - y0 * xa) / (xb * ya - yb * xa);
        i64 a = (x0 - b * xb) / xa;

        if (a * xa + b * xb == x0 && a * ya + b * yb == y0)
            result += a * 3 + b;
    }

    printf("aoc 13: %lu\n", result);
}

void aoc13_2()
{
    using namespace std;
    u64 result = 0;

    ifstream input("resources/aoc_data/aoc_13_data.txt", ios::in);

    vector<vector<u64>> a_vals;
    vector<vector<u64>> b_vals;
    vector<vector<u64>> xy_vals;

    int m = 0;;
    string line;
    while (getline(input, line)) {
        if (line.length() < 2)
            continue;
        vector<u64> vals;
        const char *line_ptr = line.c_str();
        while (*line_ptr) {
            if (!isdigit(*line_ptr)) {
                line_ptr++;
                continue;
            }
            char *end_ptr;
            i64 val = strtol(line_ptr, &end_ptr, 10);
            vals.push_back(val);
            line_ptr = end_ptr;
        }
        if (m == 0) a_vals.push_back(vals);
        if (m == 1) b_vals.push_back(vals);
        if (m == 2) xy_vals.push_back(vals);
        m = (m + 1) % 3;
    }

    for (int i = 0; i < (int)a_vals.size(); ++i) {
        xy_vals[i][0] += 10000000000000;
        xy_vals[i][1] += 10000000000000;

        i64 xa = a_vals[i][0];
        i64 ya = a_vals[i][1];

        i64 xb = b_vals[i][0];
        i64 yb = b_vals[i][1];

        i64 x0 = xy_vals[i][0];
        i64 y0 = xy_vals[i][1];

        i64 b = (x0 * ya - y0 * xa) / (xb * ya - yb * xa);
        i64 a = (x0 - b * xb) / xa;

        if (a * xa + b * xb == x0 && a * ya + b * yb == y0)
            result += a * 3 + b;
    }

    printf("aoc 13_2: %lu\n", result);
}


