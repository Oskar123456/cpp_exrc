#ifndef UTIL_H
#define UTIL_H

#include "../../include/obh/incl.hpp"

using namespace std;

u64 timefn(void (*fn)(void))
{
    struct timespec t, at;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
    fn();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &at);
    return (at.tv_nsec - t.tv_nsec) / 1000 + (at.tv_sec - t.tv_sec) * 1000000;
}

void vec_print(vector<int> v)
{
    printf("[");
    for (int i = 0; i < (int)v.size(); ++i) {
        cout << to_string(v[i]);
        if (i < v.size() - 1)
            printf(",");
    }
    printf("]\n");
}

int log2_floor(u64 n)
{
    int log = -1;
    while (n > 0) {
        ++log;
        n /= 2;
    }
    return log;
}

string u64_print_bin(u64 n, int leading_zeroes)
{
    string bin_str;
    for (int i = 0; n > 0; n /= 2) {
        bin_str = (char)(((n >> i) & 1) + '0') + bin_str;
    }
    while (leading_zeroes-- > 0) {
        bin_str = '0' + bin_str;
    }
    return bin_str;
}

std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

#endif /* ifndef UTIL_H */
