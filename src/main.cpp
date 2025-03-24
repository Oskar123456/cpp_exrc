/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include <obh/incl.hpp>
#include <obh/util.hpp>

#include <codecvt>
#include <string>
#include <locale>
#include <wctype.h>
#include <wchar.h>

using namespace std;

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

u64 u64_append_one(u64 n)
{
    return n + (1 << (log2_floor(n) + 1));
}

u64 mystery(u64 n)
{
    while (n > 0) {
        cout << n << " : " << u64_print_bin(n, 2) << endl;
        n /= 2;
    }
    return n;
}

int main(int argc, char *argv[])
{

    for (int i = 1; i < 101; ++i) {
        mystery(i);
    }

    return 0;
}




























