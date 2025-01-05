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

int divisors(long long n)
{
    i64 retval = 0;

    for (int i = 1; i <= sqrt(n); ++i) {
        if (n % i) continue;
        if (n / i == i) retval++;
        else retval += 2;
    }

    return retval;
}

string DNAStrand(const string& dna)
{
    map<char, char> complements = {{'A', 'T'}, {'T', 'A'}, {'G', 'C'}, {'C', 'G'}};

    string dna_complement;

    for (unsigned char c : dna)
        dna_complement.push_back(complements[c]);

    return dna_complement;
}

vector<int> tribonacci(vector<int> signature, int n)
{
    vector<int> result = {signature[0], signature[1], signature[2]};
    for (int i = 3; i < n; ++i) {
        result.push_back(result[i - 3] + result[i - 2] + result[i - 1]);
    }
    return vector<int>(result.begin(), result.begin() + n);
}


string get_middle(std::string input)
{
    int len = (input.length() % 2) ? 1 : 2;
    return input.substr(input.length() / 2 - 1 + (input.length() % 2), len);
}

std::string to_weird_case(std::string_view str)
{
    std::string str_cpy(str);
    for (int i = 0, wi = 0; i < str.length(); ++i) {
        if (str_cpy[i] == ' ') {wi = 0; continue;}
        if (wi++ % 2) str_cpy[i] = tolower(str_cpy[i]);
        else str_cpy[i] = toupper(str_cpy[i]);
    }

    return {str_cpy.begin(), str_cpy.end()};
}

vector<vector<int>> multiplication_table(int n)
{
    vector<vector<int>> v(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            v[i][j] = (i + 1) * (j + 1);

    return v;
}

typedef unsigned long long ull;
class ProdFib
{
    inline static std::vector<ull> fibs = {0, 1};

    public:
        static std::vector<ull> productFib(ull prod)
        {
            int i;
            for (i = 1; prod > fibs[i] * fibs[i - 1]; ++i)
                if (fibs.size() < i + 2)
                    fibs.push_back(fibs[i] + fibs[i - 1]);

            return {fibs[i - 1], fibs[i], prod == fibs[i - 1] * fibs[i]};
        }
};

class WeightSort
{
    public:
        static bool num_weight_cmp(const std::string a, const std::string b) {
            int a_w = 0, b_w = 0;
            for (char c : a) a_w += c - '0';
            for (char c : b) b_w += c - '0';
            if (a_w == b_w) return a < b;
            else return a_w < b_w;
        }

        static std::string orderWeight(const std::string &strng)
        {
            char buf[512];
            int buf_idx = 0;
            std::vector<std::string> nums;

            for (int i = 0; i < (int)strng.length(); ++i) {
                if (strng[i] == ' ') {
                    buf[buf_idx] = 0;
                    nums.push_back(buf);
                    buf_idx = 0;
                    continue;
                }

                buf[buf_idx++] = strng[i];

                if (i == (int)strng.length() - 1) {
                    buf[buf_idx] = 0;
                    nums.push_back(buf);
                }
            }

            sort(nums.begin(), nums.end(), num_weight_cmp);

            std::string nums_sorted;
            for (int i = 0; i < (int)nums.size(); ++i) {
                nums_sorted += nums[i];
                if (i < (int)nums.size() - 1)
                    nums_sorted += " ";
            }

            return nums_sorted;
        }
};

























