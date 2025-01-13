/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template for things like
                    codewars etc.
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"
#include "../../include/obh/util.hpp"

using namespace std;

long sum_prp_divs(long n)
{
    long sum = 1;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (!(n % i)) {
            sum += i;
            sum += (n / i != i) ? n / i : 0;
        }
    }
    return sum;
}

string buddy(long long start, long long limit)
{
    for (int i = start; i <= limit; ++i) {
        long spd_i = sum_prp_divs(i);
        for (int j = i + 1; ; ++j) {
            if (spd_i < j + 1)
                break;
            if (!(spd_i == j + 1))
                continue;
            long spd_j = sum_prp_divs(j);
            if (spd_j == i + 1)
                return "(" + to_string(i) + " " + to_string(j) + ")";
        }
    }
    return "Nothing";
}

struct vertex {
    int d;
    vec2i pos;
};
int operator<(const vertex& a, const vertex& b) { return a.d > b.d; }

int path_finder(string maze)
{
    vector<string> m;
    string line;
    for (int i = 0; i <= maze.length(); ++i) {
        if (maze[i] == '\n' || i == maze.length()) {
            m.push_back(line);
            line.clear();
        }
        else line.push_back(maze[i]);
    }

    int w = m.size(), h = m.size();

    int ds[h][w];
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            ds[i][j] = INT32_MAX;
    ds[0][0] = 0;

    vec2i srcs[h][w];
    srcs[0][0] = {-1, -1};

    priority_queue<vertex> q;
    q.push({0});

    while (!q.empty()) {
        vertex v = q.top(); q.pop();
        for (int i = 0; i < 4; ++i) {
            vec2i posn = v.pos + dir_vec(i);
            if (posn.i < 0 || posn.i >= h || posn.j < 0 || posn.j >= w || m[posn.i][posn.j] == 'W')
                continue;
            int d = v.d + 1;
            if (d >= ds[posn.i][posn.j])
                continue;
            ds[posn.i][posn.j] = d;
            srcs[posn.i][posn.j] = v.pos;
            q.push({d, posn});
        }
    }

    if (ds[h - 1][w - 1] == INT32_MAX)
        return -1;
    return ds[h - 1][w - 1];
}






































