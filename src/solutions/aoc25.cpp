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

void aoc25_2()
{
}

void aoc25()
{
    i64 result = 0;

    string line;
    ifstream input("aoc_25_data.txt", ios_base::in);
    /* ifstream input("resources/aoc_data/aoc_25_data.txt", ios_base::in); */
    int mode = 0;
    while (getline(input, line, '\n')) {
        memset(&result, 0, sizeof(int));
    }

    printf("aoc24:  \t%ld\n", result);
}

















