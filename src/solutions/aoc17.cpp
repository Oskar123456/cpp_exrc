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

void aoc17_2()
{
    i64 result = 0;














    printf("aoc17_2:\t%ld\n", result);
}

void aoc17()
{
    i64 result = 0;

    vector<string> data;
    string line;
    /* ifstream input("resources/aoc_data/aoc_17_data.txt"); */
    ifstream input("aoc_17_data_test.txt");
    while (getline(input, line, '\n'))
        data.push_back(line);

    for (auto str : data)
        cout << str << endl;


    printf("\naoc17:  \t%ld\n", result);
}
