/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../include/obh/incl.hpp"

/* #include "./solutions/aoc12.cpp" */
/* #include "./solutions/aoc13.cpp" */
/* #include "./solutions/aoc14.cpp" */
/* #include "./solutions/aoc15.cpp" */
/* #include "./solutions/aoc16.cpp" */
/* #include "./solutions/aoc17.cpp" */
/* #include "./solutions/aoc18.cpp" */
/* #include "./solutions/aoc19.cpp" */
/* #include "./solutions/aoc20.cpp" */
/* #include "./solutions/aoc21.cpp" */
/* #include "./solutions/aoc24.cpp" */
/* #include "./solutions/aoc25.cpp" */
#include "./solutions/codewars.cpp"

u64 timefn(void (*fn)(void))
{
    struct timespec t, at;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
    fn();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &at);
    return (at.tv_nsec - t.tv_nsec) / 1000 + (at.tv_sec - t.tv_sec) * 1000000;
}

int main(int argc, char *argv[])
{
    using namespace std;

    u64 time_to_complete;

/*     printf(">> Advent of Code day 12\n"); */
/*     time_to_complete = timefn(aoc12); */
/*     printf("\ttime elapsed: %lumcs\n", time_to_complete); */
/*     time_to_complete = timefn(aoc12_2); */
/*     printf("\ttime elapsed: %lumcs\n", time_to_complete); */

    std::string strs[] = {"lol ok buddy", "ok buddy lol", "buddy budde biddee"};

    for (int i = 0; i < sizeof(strs) / sizeof(std::string); ++i) {
        cout << to_weird_case(strs[i]) << endl;
    }

    multiplication_table(10);

    for (int i = 0; i < 100000; ++i) {
        vector<ull> fibres = ProdFib::productFib(i);
        if (fibres[2])
            cout << fibres[0] << " * " << fibres[1] << " = " << i << " : " << (fibres[2] ? "true" : "false") << endl;
    }

    cout << WeightSort::orderWeight("2000 10003 1234000 44444444 9999 11 11 22 123") << endl;


    return 0;
}




























