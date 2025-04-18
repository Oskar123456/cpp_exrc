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
    vec2i vs = {8 - (tolower(start[1]) - '0'), tolower(start[0]) - 'a'};
    vec2i ve = {8 - (tolower(finish[1]) - '0'), tolower(finish[0]) - 'a'};
    priority_queue<cvert> vq;
    vq.push({0, vs.i, vs.j});

    vector<vector<int>> dist(8, vector(8, INT32_MAX));
    /* int dist[8][8]; */
    /* for (int i = 0; i < 8; ++i) */
    /*     for (int j = 0; j < 8; ++j) */
    /*         dist[i][j] = INT32_MAX; */

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

        /* u8 board[8][8]; memset(board, 0, 64); */

        for (int i = 0; i < 8; ++i) {
            vec2i vn = vns[i];
            if (vn.i < 0 || vn.i >= 8 || vn.j < 0 || vn.j >= 8)
                continue;
            /* board[vn.i][vn.j] = 1; */
            if (dist[vn.i][vn.j] <= v.d + 1)
                continue;
            dist[vn.i][vn.j] = v.d + 1;
            if (vn != ve)
                vq.push({v.d + 1, vn.i, vn.j});
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

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == vs.i && vs.j == j) printf("   K ");
            else if (i == ve.i && ve.j == j) printf("[%3d]", dist[i][j]);
            else printf(" %3d ", dist[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 8; ++i) {
        printf("---");
    }
    printf("\n");


    return dist[ve.i][ve.j];
}

struct vec2 { int i, j; };
vec2 DIRS[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

int path_finder2(std::string maze)
{
    int w = 0, h = 0;
    vector<string> m(1);
    for (int i = 0; i < maze.length(); ++i) {
        if (maze[i] == '\n') {
            if (w == 0)
                w = i;
            m.push_back(string());
            h++;
            continue;
        }
        m[h].push_back(maze[i]);
    }
    h++;


    for (string s : m)
        cout << s << endl;

    int dist[h][w];
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            dist[i][j] = INT32_MAX;
    dist[0][0] = 0;

    priority_queue<cvert> q;
    q.push({0, 0, 0});

    while (!q.empty()) {
        cvert v = q.top(); q.pop();
        for (vec2 dir : DIRS) {
            int i = v.i + dir.i;
            int j = v.j + dir.j;
            if (i < 0 || i >= h || j < 0 || j >= w)
                continue;
            int d = v.d + abs(m[i][j] - m[v.i][v.j]);
            if (dist[i][j] <= d)
                continue;
            dist[i][j] = d;
            if (!(i == h - 1 && j == w - 1))
                q.push({d, i, j});
        }
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            printf("%3d", dist[i][j]);
        }
        printf("\n");
    }

    return dist[h - 1][w - 1];
}


string longest_palindrome(string input)
{
    int l = input.length();
    int s = 0, smax = 0;

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j <= 1; ++j) {
            int lo = i;
            int hi = i + j;
            while (lo >= 0 && hi < l && input[lo] == input[hi]) {
                int scur = hi - lo + 1;
                if (scur > smax) {
                    smax = scur;
                    s = lo;
                }
                lo--;
                hi++;
            }
        }
    }

    printf("%d %d\n", s, smax);

    return input.substr(s, smax);
}

string encode_rail_fence_cipher(const string &str, int n)
{
    vector<string> rfc(n);
    int rfc_idx = 0, incr = 1;;

    for (int i = 0; i < str.length(); ++i) {
        rfc[rfc_idx].push_back(str[i]);
        if (rfc_idx == n - 1)
            incr = -1;
        else if (rfc_idx == 0)
            incr = 1;
        rfc_idx += incr;
    }

    string s;
    for (int i = 0; i < n; ++i)
        s += rfc[i];

    return s;
}

string decode_rail_fence_cipher(const string &str, int n)
{
    if (n <= 0) return str;

    int L = 2 * (n - 1);

    vector<string> rfc(n);
    int str_idx = 0;

    string str_pad(str);
    if (str.length() % L)
        str_pad.resize(str.length() + (L - (str.length() % L)), '?');

    cout << "str_pad: " << str_pad << endl;

    for (int i = 0; i < n / 2; ++i) {
        int l = str_pad.length() / (2 * (n - i - 1));
        rfc[i] = str_pad.substr(0, l);
        rfc[n - i - 1] = str_pad.substr(str_pad.length() - l - 2, l);
        str_pad = str_pad.substr(l, (str_pad.length() - 2 * l - 1));
    }

    rfc[n / 2] = str_pad;

    for (string ss : rfc) {
        cout << ss << endl;
    }

    vector<int> rfc_idxs(n, 0);
    string s;

    int rfc_idx = 0, incr = 1;;

    for (int i = 0; i < str.length(); ++i) {
        s.push_back(rfc[rfc_idx][rfc_idxs[rfc_idx]++]);
        if (rfc_idx == n - 1)
            incr = -1;
        else if (rfc_idx == 0)
            incr = 1;
        rfc_idx += incr;
    }

    cout << s << endl;

    return s;
}

string format_duration(int seconds)
{
    if (seconds < 1) {
        return "now";
    }

    string u[] = { "year", "day", "hour", "minute", "second" };
    int us[] = { INT32_MAX, 365 * 24 * 60 * 60, 24 * 60 * 60, 60 * 60, 60, 1 };

    vector<int> ts;
    vector<string> units;

    for (int i = 0; i < 5; ++i) {
        int t = (seconds % us[i]) / us[i + 1];
        if (t > 0) {
            ts.push_back(t);
            units.push_back(u[i]);
        }
    }

    string str;

    for (size_t i = 0; i < ts.size(); ++i) {
        if (i == ts.size() - 1 && ts.size() > 1) {
            str += " and ";
        } else if (i > 0) {
            str += ", ";
        }
        str += to_string(ts[i]) + " " + units[i] + (ts[i] > 1 ? "s" : "");
    }

    return str;
}

template <typename T>
void ssum(const T& t, double& sum)
{
    if constexpr (is_same_v<T, char>) {
        return;
    }
    if constexpr (is_arithmetic_v<T>) {
        sum += t;
    }
}

template <typename... Ts>
double tuple_sum(const tuple<Ts...>& tpl)
{
    double sum = 0;

    std::apply
    (
        [&sum](Ts const&... tupleArgs)
        {
            ((ssum(tupleArgs, sum)), ...);
        }, tpl
    );

    return sum;
}

u64 n_choose_k(u64 n, u64 k)
{
    if (k == 0) {
        return 1;
    }
    return (n * n_choose_k(n - 1, k - 1)) / k;
}

map<int, u64> exp_sum_mem;
map<pair<int, int>, u64> count_all_subset_sums_mem;

void gen_all_subset_sums(int target, int idx, vector<vector<int>>& subsets, vector<int>& current_subset)
{
    if (target == 0) {
        subsets.push_back(current_subset);
        return;
    }
    for (int i = idx; target - i >= 0; ++i) {
        current_subset.push_back(i);
        gen_all_subset_sums(target - i, i, subsets, current_subset);
        current_subset.pop_back();
    }
}

u64 count_all_subset_sums(int target, int idx)
{
    if (count_all_subset_sums_mem.count(make_pair(target, idx))) {
        return count_all_subset_sums_mem[make_pair(target, idx)];
    }

    if (target == 0) {
        return 1;
    }

    u64 retval = 0;

    for (int i = idx; target - i >= 0; ++i) {
        retval += count_all_subset_sums(target - i, i);
    }

    count_all_subset_sums_mem[make_pair(target, idx)] = retval;

    /* cout << "mem'ing count_all_subset_sums(" << target << "," << idx << ")" << " : " << retval << endl; */

    return retval;
}

u64 exp_sum(unsigned int n)
{
    if (exp_sum_mem.count(n)) {
        return exp_sum_mem[n];
    }
    u64 ans = count_all_subset_sums(n, 1);
    exp_sum_mem[n] = ans;
    return ans;
}

vector<vector<int>> pyramid(size_t n)
{
    vector<vector<int>> pyramid;
    for (int i = 1; i <= n; ++i) {
        pyramid.push_back(vector<int>(i, 1));
    }
    return pyramid;
}

set<u64> hamber_mem;

void init_hamber_mem(int n)
{
    hamber_mem.clear();

    priority_queue<u64, vector<u64>, greater<u64>> q;
    q.push(1);

    while (hamber_mem.size() < 13'282) {
        u64 m = q.top(); q.pop();

        while (q.top() == m && q.size() > 1) {
            q.pop();
        }

        hamber_mem.insert(m);

        if (m <= UINT64_MAX / 2)
            q.push(m * 2);
        if (m <= UINT64_MAX / 3)
            q.push(m * 3);
        if (m <= UINT64_MAX / 5)
            q.push(m * 5);
    }
}

u64 hamber(int n)
{
    if (n < 0) {
        return -1;
    }

    if (hamber_mem.size() < n) {
        init_hamber_mem(n);
    }

    auto it = hamber_mem.begin();
    advance(it, n - 1);
    return *it;
}

vector<int> deleteNth(vector<int> arr, int n)
{
    vector<int> arr_trimmed;
    map<int, int> arr_freqs;

    for (int i = 0; i < arr.size(); ++i) {
        if (arr_freqs.count(arr[i]) == 0) {
            arr_freqs[arr[i]] = 1;
        } else {
            arr_freqs[arr[i]]++;
        }
        if (arr_freqs[arr[i]] <= n) {
            arr_trimmed.push_back(arr[i]);
        }
    }

    return arr_trimmed;
}

/* using i64 = long long; */

int persistence(i64 n)
{
    int retval = 0;

    while (n >= 10) {
        i64 product = 1;
        i64 nn = n;
        while (nn > 0) {
            product *= nn % 10;
            nn /= 10;
        }
        n = product;
        retval++;
        cout << n << ", ";
    }
    cout << " : " << retval << endl;

    return retval;
}


























