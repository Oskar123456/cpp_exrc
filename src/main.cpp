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

void print_bool_array(bool arr[], int len)
{
    printf("[");
    for (int i = 0; i < len; ++i) {
        printf("%d", arr[i]);
        if (i < len - 1) {
            printf(" ");
        }
    }
    printf("]\n");
}

void check_digits(unsigned n, bool digits[])
{
    if (n == 0) {
        digits[0] = true;
    }
    while (n > 0) {
        digits[n % 10] = true;
        n /= 10;
    }
}

unsigned integer_depth(unsigned n)
{
    if (n == 0) {
        return (unsigned)-1;
    }

    unsigned nn = n, i;
    bool done = false;
    bool digits[10] = { 0 };

    for (i = 0; !done; nn += n, ++i) {
        check_digits(nn, digits);

        done = true;
        for (int j = 0; j < 10; ++j) {
            if (!digits[j]) {
                done = false;
            }
        }
    }

    return i;
}

bool isPrime(int num)
{
    if ((num != 2 && !(num % 2)) || num < 2) {
        return false;
    }

    int num_sqr = (int)sqrt(num);
    for (int i = 3; i <= num_sqr; i += 2) {
        if (!(num % i)) {
            return false;
        }
    }

    return true;
}

bool scramble(const string& s1, const string& s2)
{
    int arr[1 << 8] = { 0 };
    memset(arr, 0, (1 << 8) * sizeof(int));
    for (char c : s2) {
        arr[(int)c]++;
    }
    for (char c : s1) {
        arr[(int)c]--;
    }
    for (int i = 0; i < 1 << 8; ++i) {
        if (arr[i] > 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    cout << scramble("rkqodlw", "world") << endl;
    cout << scramble("cedewaraaossoqqyt", "codewars") << endl;
    cout << scramble("katas", "steak") << endl;

    return 0;
}




























