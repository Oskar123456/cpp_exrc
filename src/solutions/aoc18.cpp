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

struct vtx {
    int d;
    vec2i pos;
    std::string toString() { return "[d:" + to_string(d) + ", " + pos.toString() + "]"; }
};
bool operator<(const vtx& a, const vtx& b) { return a.d > b.d; }

void print_grid(char *grid, int w, int h)
{
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            printf("%c", grid[i * w + j]);
        }
        printf("\n");
    }
}

void aoc18()
{
    i64 result = 0;

    int h = 71, w = 71, nbytes = 1024;
    vec2i s = {0, 0}, e = {h - 1, w - 1};
    vector<vec2i> data;

    char line[MAXLINE];
    FILE *input = fopen("resources/aoc_data/aoc_18_data.txt", "r");
    while (fgets(line, MAXLINE, input)) {
        if (strlen(line) < 2) continue;
        vec2i v = {-1, -1};
        char *line_ptr = line;
        while (*line_ptr) {
            if (!isdigit(*line_ptr)) {
                line_ptr++;
                continue;
            }
            i32 val = strtol(line_ptr, &line_ptr, 10);
            if (v.i >= 0) v.j = val;
            else v.i = val;
        }
        data.push_back(v);
    }

    char grid[h][w];
    memset(grid, '.', h * w);

    for (int i = 0; i < nbytes; ++i) {
        vec2i v = data[i];
        grid[v.j][v.i] = '#';
    }

    int dist[h][w];
    vec2i src[h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            dist[i][j] = INT32_MAX;
            src[i][j] = {-1, -1};
        }
    }
    dist[s.i][s.j] = 0;

    priority_queue<vtx> q;
    q.push({0, s});
    while (!q.empty()) {
        vtx v = q.top(); q.pop();
        for (int d = 0; d < 4; ++d) {
            vec2i p = v.pos + dir_vec(d);

            if (p.i < 0 || p.i >= h || p.j < 0 || p.j >= w || grid[p.i][p.j] == '#')
                continue;

            if (1 + v.d < dist[p.i][p.j]) {
                dist[p.i][p.j] = 1 + v.d;
                src[p.i][p.j] = v.pos;
                if (p != e)
                    q.push({1 + v.d, p});
            }
        }
    }

    vec2i cv = e;
    grid[cv.i][cv.j] = 'O';
    while (cv != s) {
        cv = src[cv.i][cv.j];
        grid[cv.i][cv.j] = 'O';
    }

    result = dist[e.i][e.j];

    printf("aoc18:  \t%ld\n", result);
}

bool path_exists(int h, int w, char *grid)
{
    vec2i s = {0, 0}, e = {h - 1, w - 1};

    int dist[h][w];
    vec2i src[h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            dist[i][j] = INT32_MAX;
            src[i][j] = {-1, -1};
        }
    }
    dist[s.i][s.j] = 0;

    priority_queue<vtx> q;
    q.push({0, s});
    while (!q.empty()) {
        vtx v = q.top(); q.pop();
        for (int d = 0; d < 4; ++d) {
            vec2i p = v.pos + dir_vec(d);

            if (p.i < 0 || p.i >= h || p.j < 0 || p.j >= w || grid[p.i * w + p.j] == '#')
                continue;

            if (1 + v.d < dist[p.i][p.j]) {
                dist[p.i][p.j] = 1 + v.d;
                src[p.i][p.j] = v.pos;
                if (p != e)
                    q.push({1 + v.d, p});
            }
        }
    }

    return dist[e.i][e.j] == INT32_MAX;
}

void aoc18_2()
{
    i64 result = 0;

    int h = 71, w = 71, nbytes = 1024;
    vec2i s = {0, 0}, e = {h - 1, w - 1};
    vector<vec2i> data;

    char line[MAXLINE];
    FILE *input = fopen("resources/aoc_data/aoc_18_data.txt", "r");
    while (fgets(line, MAXLINE, input)) {
        if (strlen(line) < 2) continue;
        vec2i v = {-1, -1};
        char *line_ptr = line;
        while (*line_ptr) {
            if (!isdigit(*line_ptr)) {
                line_ptr++;
                continue;
            }
            i32 val = strtol(line_ptr, &line_ptr, 10);
            if (v.i >= 0) v.j = val;
            else v.i = val;
        }
        data.push_back(v);
    }

    char grid[h][w];
    memset(grid, '.', h * w);

    for (int i = 0; i < nbytes; ++i) {
        vec2i v = data[i];
        grid[v.j][v.i] = '#';
    }

    int dist[h][w];
    vec2i src[h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            dist[i][j] = INT32_MAX;
            src[i][j] = {-1, -1};
        }
    }
    dist[s.i][s.j] = 0;

    priority_queue<vtx> q;
    q.push({0, s});
    while (!q.empty()) {
        vtx v = q.top(); q.pop();
        for (int d = 0; d < 4; ++d) {
            vec2i p = v.pos + dir_vec(d);

            if (p.i < 0 || p.i >= h || p.j < 0 || p.j >= w || grid[p.i][p.j] == '#')
                continue;

            if (1 + v.d < dist[p.i][p.j]) {
                dist[p.i][p.j] = 1 + v.d;
                src[p.i][p.j] = v.pos;
                if (p != e)
                    q.push({1 + v.d, p});
            }
        }
    }

    vec2i blocker;
    for (int i = nbytes; i < data.size(); ++i) {
        grid[data[i].j][data[i].i] = '#';
        bool blocked = path_exists(h, w, (char*)grid);
        if (blocked) {
            blocker = data[i];
            break;
        }
    }

    vec2i cv = e;
    grid[cv.i][cv.j] = 'O';
    while (cv != s) {
        cv = src[cv.i][cv.j];
        if (grid[cv.i][cv.j] != '#')
            grid[cv.i][cv.j] = 'O';
    }

    result = dist[e.i][e.j];

    printf("aoc18:  \t%s\n", blocker.toString().c_str());
}

