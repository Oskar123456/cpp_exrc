/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"
#include <cassert>
#include <cstring>
#include <set>

std::string strprintf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    va_end(args);
    int len = std::vsnprintf(nullptr, 0, fmt, args);
    char buf[len + 1];
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    return std::string(buf);
}


struct iVec2_t {
    union {
        int y;
        int i;
    };
    union {
        int x;
        int j;
    };

    std::string toString() const;

    friend bool operator<(const iVec2_t& l, const iVec2_t& r)
    {
        return std::tie(l.x, l.y)
             < std::tie(r.x, r.y);
    }

    friend bool operator==(const iVec2_t& l, const iVec2_t& r)
    {
        return l.x == r.x && l.y == r.y;
    }
};

struct Plant {
    char type;
    iVec2_t root_pos;

    std::string toString() const;
};

std::string Plant::toString() const
{
    return strprintf("[%c | %s]", this->type, this->root_pos.toString().c_str());
}

std::string iVec2_t::toString() const
{
    return strprintf("(%d %d)", this->x, this->y);
}

void aoc12_2()
{
    using namespace std;
    u64 result = 0;

    ifstream input("resources/aoc_data/aoc_12_data.txt", ios::in);
    //ifstream input("aoc12datatest.txt", ios::in);
    vector<string> data;
    string line;
    while (getline(input, line) && line.length() > 1)
        data.push_back(line);
    int w = data[0].length(), h = data.size();

    int label = 0;
    set<iVec2_t> visited;
    map<int, vector<iVec2_t>> groups;
    vector<iVec2_t> stack;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            iVec2_t cur_pos = {i, j};
            if (visited.find(cur_pos) != visited.end())
                continue;

            stack.push_back(cur_pos);
            vector<iVec2_t> new_group_set;
            while (stack.size() > 0) {
                cur_pos = stack[stack.size() - 1];
                stack.pop_back();

                if (cur_pos.j < 0 || cur_pos.j >= w || cur_pos.i < 0 || cur_pos.i >= h)
                    continue;

                if (data[cur_pos.i][cur_pos.j] != data[i][j])
                    continue;

                if (visited.find(cur_pos) != visited.end())
                    continue;

                stack.push_back((iVec2_t){cur_pos.i + 1, cur_pos.j});
                stack.push_back((iVec2_t){cur_pos.i - 1, cur_pos.j});
                stack.push_back((iVec2_t){cur_pos.i, cur_pos.j + 1});
                stack.push_back((iVec2_t){cur_pos.i, cur_pos.j - 1});

                visited.emplace(cur_pos);
                new_group_set.push_back((iVec2_t){cur_pos.i, cur_pos.j});
            }
            //printf("placing group %d: ", label);
            //for (int k = 0; k < new_group_set.size(); ++k)
                //printf("%s", new_group_set[k].toString().c_str());
            //printf("\n");

            groups.emplace(label, new_group_set);
            label++;
        }
    }

    for (auto it = groups.begin(); it != groups.end(); it++) {
        int perimeter = 0;
        for (int i = 0; i < (int)it->second.size(); ++i) {
            iVec2_t cur_pos = it->second[i];
            iVec2_t arr[8];
            arr[0] = {cur_pos.i - 1, cur_pos.j};
            arr[1] = {cur_pos.i, cur_pos.j + 1};
            arr[2] = {cur_pos.i + 1, cur_pos.j};
            arr[3] = {cur_pos.i, cur_pos.j - 1};

            arr[4] = {cur_pos.i - 1, cur_pos.j + 1};
            arr[5] = {cur_pos.i + 1, cur_pos.j + 1};
            arr[6] = {cur_pos.i + 1, cur_pos.j - 1};
            arr[7] = {cur_pos.i - 1, cur_pos.j - 1};

            bool exists[8] = { 0 };
            for (int k = 0; k < (int)it->second.size(); k++) {
                for (int m = 0; m < 8; m++) {
                    if (arr[m] == it->second[k]) exists[m] = true;
                }
            }
            int corners = 0;
            for (int m = 0; m < 4; m++) {
                if (!exists[m] && !exists[(m + 1) % 4])
                    corners++;
                if (exists[m] && exists[(m + 1) % 4] && !exists[m + 4])
                    corners++;
            }
            perimeter += corners;
            //printf("[%d] %s ", it->first, cur_pos.toString().c_str());
            //printf("%b %b %b %b (%d)\n", exists[0], exists[1], exists[2], exists[3], corners);
        }
        result += perimeter * it->second.size();
    }

    printf("aoc 12_2: %lu\n", result);
}

void aoc12()
{
    using namespace std;
    u64 result = 0;

    ifstream input("resources/aoc_data/aoc_12_data.txt", ios::in);
    //ifstream input("aoc12datatest.txt", ios::in);
    vector<string> data;
    string line;
    while (getline(input, line) && line.length() > 1)
        data.push_back(line);
    int w = data[0].length(), h = data.size();

    int label = 0;
    set<iVec2_t> visited;
    map<int, vector<iVec2_t>> groups;
    vector<iVec2_t> stack;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            iVec2_t cur_pos = {i, j};
            if (visited.find(cur_pos) != visited.end())
                continue;

            stack.push_back(cur_pos);
            vector<iVec2_t> new_group_set;
            while (stack.size() > 0) {
                cur_pos = stack[stack.size() - 1];
                stack.pop_back();

                if (cur_pos.j < 0 || cur_pos.j >= w || cur_pos.i < 0 || cur_pos.i >= h)
                    continue;

                if (data[cur_pos.i][cur_pos.j] != data[i][j])
                    continue;

                if (visited.find(cur_pos) != visited.end())
                    continue;

                stack.push_back((iVec2_t){cur_pos.i + 1, cur_pos.j});
                stack.push_back((iVec2_t){cur_pos.i - 1, cur_pos.j});
                stack.push_back((iVec2_t){cur_pos.i, cur_pos.j + 1});
                stack.push_back((iVec2_t){cur_pos.i, cur_pos.j - 1});

                visited.emplace(cur_pos);
                new_group_set.push_back((iVec2_t){cur_pos.i, cur_pos.j});
            }
            //printf("placing group %d: ", label);
            //for (int k = 0; k < new_group_set.size(); ++k)
                //printf("%s", new_group_set[k].toString().c_str());
            //printf("\n");

            groups.emplace(label, new_group_set);
            label++;
        }
    }

    /*
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            for (auto it = groups.begin(); it != groups.end(); it++) {
                for (int k = 0; k < it->second.size(); ++k) {
                    if (it->second[k].i == i && it->second[k].j == j)
                        printf("%3d", it->first);
                }
            }
        }
        printf("\n");
    }
     * */

    for (auto it = groups.begin(); it != groups.end(); it++) {
        int perimeter = 0;
        for (int i = 0; i < (int)it->second.size(); ++i) {
            iVec2_t cur_pos = it->second[i];
            int c = 0;
            for (int y = -1; y < 2; ++y) {
                for (int x = -1; x < 2; ++x) {
                    if (y == 0 && x == 0) continue;
                    if (!(y == 0 || x == 0)) continue;
                    if (cur_pos.y + y < 0 || cur_pos.y + y >= h || cur_pos.x + x < 0 || cur_pos.x + x >= w) {
                        perimeter++;
                        c++;
                        continue;
                    }
                    bool found = false;
                    for (auto vec = it->second.begin(); vec != it->second.end(); vec++) {
                        if (*vec == cur_pos) continue;
                        if (*vec == (iVec2_t){cur_pos.y + y, cur_pos.x + x})
                            found = true;
                    }
                    if (!found) {
                        perimeter++;
                        c++;
                    }
                }
            }
            //printf("%s contributes %d to perim\n", cur_pos.toString().c_str(), c);
        }
        //printf("group %d: %d %lu\n", it->first, perimeter, it->second.size());
        result += perimeter * it->second.size();
    }

    printf("aoc 12: %lu\n", result);
}


