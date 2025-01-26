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

std::vector<int> snail(const std::vector<std::vector<int>> &snail_map)
{
    u32 h = snail_map.size();
    u32 w = snail_map[0].size();

    vector<int> s;
    pair<int, int> dir = {0, 1};
    pair<int, int> pos = {0, 0}, posn;
    bool vis[h][w];
    memset(vis, 0, h * w);

    while (pos.first >= 0 && pos.first < h && pos.second >= 0 && pos.second < w && !vis[pos.first][pos.second]) {
        /* cout << "at " << pos.first << "," << pos.second << endl; */
        s.push_back(snail_map[pos.first][pos.second]);
        vis[pos.first][pos.second] = 1;

        posn.first = pos.first + dir.first;
        posn.second = pos.second + dir.second;

        if (posn.first < 0 || posn.first >= h || posn.second < 0 || posn.second >= w || vis[posn.first][posn.second]) {
            int tmp = dir.second;
            dir.second = -dir.first;
            dir.first = tmp;
            /* cout << "turning " << dir.first << "," << dir.second << endl; */
        }

        pos.first += dir.first;
        pos.second += dir.second;

        if (pos.first >= 0 && pos.first <= h && pos.second >= 0 && pos.second <= w && !vis[pos.first][pos.second])
        {
            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    if (i == pos.first && j == pos.second)
                        printf("[%2d]", snail_map[i][j]);
                    else
                        printf(" %2d ", snail_map[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }

    return s;
}


unsigned long long countChangeRec(const unsigned int money, std::map<pair<int, int>, int> mem, int idx, const std::vector<unsigned int>& coins)
{
    if (money == 0) return 1;

    unsigned long long r = 0;
    for (int i = idx; i < coins.size(); ++i) {
        if (money < coins[i]) continue;
        if (!mem.count(make_pair(money - coins[i], idx)))
            mem[make_pair(money - coins[i], idx)] = countChangeRec(money - coins[i], mem, i, coins);
        r += mem[make_pair(money - coins[i], idx)];
    }

    return r;
}

unsigned long long countChange(const unsigned int money, const std::vector<unsigned int>& coins)
{
    std::map<pair<int, int>, int> mem;
    return countChangeRec(money, mem, 0, coins);
}

u64 countRecur(vector<u64>& coins, u64 n, u64 sum, vector<vector<u64>> &memo)
{
    if (sum == 0) return 1;

    if (sum < 0 || n == 0) return 0;

    if (memo[n-1][sum] != 0) return memo[n-1][sum];

    if (sum >= coins[n-1]) {
        return memo[n-1][sum] =
            countRecur(coins, n, sum - coins[n-1], memo) +
            countRecur(coins, n - 1, sum, memo);
    }
    else {
        return countRecur(coins, n - 1, sum, memo);
    }
}

u64 count(u64 sum, vector<u64> &coins)
{
    vector<vector<u64>> memo(coins.size(), vector<u64>(sum+1, 0));
    return countRecur(coins, coins.size(), sum, memo);
}

unsigned long long countChange2(const unsigned int money, const std::vector<unsigned int>& coins) {
    std::vector<unsigned long long> ways(money + 1, 0);

    // Initialization
    ways[0] = 1;

    for (auto &coin : coins) {
        for (int i = 0; i < money + 1; ++i) {
            if (coin <= i) {
                ways[i] += ways[i - coin];
            }
        }
    }

    return ways[money];
}

string multiply(string a, string b)
{
    string res(a.length() + b.length() + 1, '0');

    /* cout << a << endl; */
    /* cout << b << endl; */
    /* cout << res.length() << endl; */

    int i;
    for (i = a.length() - 1; i >= 0; --i) {
        int av = a[i] - '0';
        int c = 0;
        for (int j = b.length() - 1; j >= 0; --j) {
            int res_idx = res.length() - a.length() + i - b.length() + j + 1;
            int bv = b[j] - '0';
            int avbv = av * bv;
            int rv = res[res_idx] - '0';
            int rvavbv = rv + avbv;
            res[res_idx] = (rvavbv % 10) + '0';
            c = rvavbv / 10;
            printf("(j:%d,i:%d) %d * %d = %d\n", j, i, av, bv, avbv);
            for (int k = res_idx - 1; c; k--) {
                rv = res[k] - '0';
                res[k] = ((rv + c) % 10) + '0';
                c = (rv + c) / 10;
            }
            cout << res << endl;
        }
    }

    i = 0;
    while (res[i] == '0') i++;
    return (i == res.length()) ? "0" : string(res.begin() + i, res.end());
}

bool path_finder_2(string maze)
{
    int h = 0, w = maze.find_first_of('\n') - 1;
    vector<string> m(1);
    for (int i = 0; i < maze.length(); ++i) {
        if (maze[i] == '\n') {
            h++;
            m.push_back(string());
            continue;
        }
        m[h].push_back(maze[i]);
    }
    if (m[h].length() < 1)
        m.erase(m.end() - 1);

    /* for (string s : m) */
        /* cout << s << endl; */

    /* printf("dims: %d %d\n", h, w); */

    vec2i s = {0, 0};
    vec2i e = {h, w};

    map<vec2i, int> ds;
    map<vec2i, vec2i> srcs;
    priority_queue<vertex> q;
    q.push({0, {0, 0}});
    ds[{0, 0}] = 0;
    while (!q.empty()) {
        vec2i p = q.top().pos;
        int d = q.top().d;
        q.pop();
        /* printf("visiting %s (%d)\n", p.toString().c_str(), d); */
        for (int i = 0; i < 4; ++i) {
            vec2i dir = dir_vec(i);
            vec2i p_nxt = dir + p;
            if (p_nxt.i < 0 || p_nxt.i > h || p_nxt.j < 0 || p_nxt.j > w || m[p_nxt.i][p_nxt.j] == 'W')
                continue;

            int d_nxt = d + 1;
            if (ds.count(p_nxt) && ds[p_nxt] < d_nxt)
                continue;

            ds[p_nxt] = d_nxt;
            srcs[p_nxt] = p;
            if (p_nxt != e)
                q.push({d_nxt, p_nxt});
        }
    }

    /* printf("start d: %d\n", ds[s]); */
    /* if (ds.count(e)) */
        /* printf("end   d: %d\n", ds[e]); */

    vec2i v = e;
    while (true) {
        /* m[v.i][v.j] = 'O'; */
        v = srcs[v];
        if (!srcs.count(v)) {
            /* m[v.i][v.j] = 'O'; */
            break;
        }
        /* cout << ","; */
    }
    /* cout << endl; */

    /* for (string s : m) */
        /* cout << s << endl; */

    return ds.count(e);
}

struct cvert {
    int d;
    int i, j;
};
int operator<(const cvert& a, const cvert& b) { return a.d > b.d; }

int knight(string start, string finish)
{
    vec2i vns[8];
    vec2i vs = {tolower(start[0]) - 'a', tolower(start[1]) - '0'};
    vec2i ve = {tolower(finish[0]) - 'a', tolower(finish[1]) - '0'};
    priority_queue<cvert> vq;
    vq.push({0, vs.i, vs.j});

    int dist[8][8];
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            dist[i][j] = INT32_MAX;

    while(!vq.empty()) {
        cvert v = vq.top(); vq.pop();
        vns[0] = {v.i - 2, v.j - 1};
        vns[1] = {v.i - 2, v.j + 1};
        vns[2] = {v.i - 1, v.j + 2};
        vns[3] = {v.i + 1, v.j + 2};
        vns[4] = {v.i + 2, v.j - 1};
        vns[5] = {v.i + 2, v.j + 1};
        vns[6] = {v.i - 1, v.j - 2};
        vns[7] = {v.i + 1, v.j - 2};

        u8 board[8][8]; memset(board, 0, 64);

        for (int i = 0; i < 8; ++i) {
            vec2i vn = vns[i];
            if (vn.i < 0 || vn.i >= 8 || vn.j < 0 || vn.j >= 8)
                continue;
            board[vn.i][vn.j] = 1;

        }

        /* for (int i = 0; i < 8; ++i) { */
        /*     for (int j = 0; j < 8; ++j) { */
        /*         if (i == v.i && v.j == j) printf(" K "); */
        /*         else printf("%s", board[i][j] ? " . " : " o "); */
        /*     } */
        /*     printf("\n"); */
        /* } */

        /* for (int i = 0; i < 8; ++i) { */
        /*     printf("---"); */
        /* } */
        /* printf("\n"); */
    }


    return 0;
}























