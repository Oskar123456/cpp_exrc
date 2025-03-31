/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include <obh/incl.hpp>
#include <obh/util.hpp>

#include <string>
#include <random>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std;

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

int main(int argc, char *argv[])
{
    persistence(39);

    return 0;
}




























