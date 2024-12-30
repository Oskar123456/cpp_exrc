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

struct vertex {
    int dir;
    vec2i pos;

    std::string toString() { return "[dir:" + dir_name(dir) + ", " + pos.toString() + "]"; }
};
bool operator<(const vertex& a, const vertex& b) { return std::tie(a.dir, a.pos) < std::tie(b.dir, b.pos); }
bool operator==(const vertex& a, const vertex& b) { return a.pos == b.pos && a.dir == b.dir; }

struct vertex_q {
    int d;
    vertex v;
};
bool operator<(const vertex_q& a, const vertex_q& b) { return a.d > b.d; }

vector<pair<int, vertex>> adj(vertex v, int d)
{
    vector<pair<int, vertex>> vs = {
        make_pair(d + 1, (vertex){v.dir,           v.pos + dir_vec(v.dir)}),
        make_pair(d + 1000, (vertex){(v.dir + 1) % 4, v.pos}),
        make_pair(d + 1000, (vertex){(v.dir + 3) % 4, v.pos}),
    };
    return vs;
}

void aoc16_2()
{
    i64 result = 0;

    vector<string> data;
    vec2i s, e;

    string line;
    ifstream input("resources/aoc_data/aoc_16_data.txt");
    /* ifstream input("aoc_16_data_test.txt"); */
    while (getline(input, line, '\n')) {
        data.push_back(line);
        i64 si = line.find_first_of('S');
        i64 ei = line.find_first_of('E');
        if (si != string::npos) s = {(int)data.size() - 1, (int)si};
        if (ei != string::npos) e = {(int)data.size() - 1, (int)ei};
    }

    for (int i = 0; i < data.size(); ++i)
        cout << data[i] << endl;
    cout << endl;

    int h = data.size(), w = data[0].length();

    printf("s:%s e:%s\n", s.toString().c_str(), e.toString().c_str());

    /*****************************/

    map<vertex, int> dists;
    map<vertex, set<vertex>> srcs;

    priority_queue<vertex_q> q;
    q.push({0, (vertex){EAST, s}});
    while (!q.empty()) {
        vertex_q qtop = q.top(); q.pop();
        for (auto step : adj(qtop.v, qtop.d)) {
            int vd = step.first;
            vertex vn = step.second;

            if (data[vn.pos.i][vn.pos.j] == '#')
                continue;

            if (!dists.count(vn)) {
                dists.emplace(vn, vd);
                set<vertex> sv;
                srcs.emplace(vn, sv);
                q.push({vd, vn});
            }

            if (dists[vn] > vd) {
                dists[vn] = vd;
                srcs[vn].clear();
                srcs[vn].emplace(qtop.v);

                set<vertex> prevsrcstest = srcs.find(vn)->second;
                assert(prevsrcstest.size() == 1);
                for (auto tt : prevsrcstest)
                    assert(tt == qtop.v);

                q.push({vd, vn});
            }

            if (dists[vn] == vd) {
                srcs[vn].emplace(qtop.v);
            }

        }
    }

    char map[h][w];
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            map[i][j] = data[i][j];
        }
    }

    stack<vertex> vis;
    int e_min = INT32_MAX, e_min_idx;
    for (int i = 0; i < 4; ++i) {
        if (dists[{i, e}] > e_min)
            continue;
        e_min = dists[{i, e}];
        e_min_idx = i;
    }
    vis.push({(vertex){e_min_idx, e}});

    while (!vis.empty()) {
        vertex v = vis.top(); vis.pop();
        map[v.pos.i][v.pos.j] = 'O';
        if (v.pos == s) continue;
        for (auto vn : srcs[v])
            vis.push(vn);
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            printf("%c", map[i][j]);
            if (map[i][j] == 'O')
                result++;
        }
        printf("\n");
    }


    printf("aoc16_2:\t%ld\n", result);
}



































