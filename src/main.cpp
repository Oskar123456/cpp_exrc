/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../include/obh/incl.hpp"

#include "./solutions/aoc12.cpp"
#include "./solutions/aoc13.cpp"

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

    printf(">> Advent of Code day 12\n");
    time_to_complete = timefn(aoc12);
    printf("\ttime elapsed: %lumcs\n", time_to_complete);
    time_to_complete = timefn(aoc12_2);
    printf("\ttime elapsed: %lumcs\n", time_to_complete);

    printf(">> Advent of Code day 13\n");
    time_to_complete = timefn(aoc13);
    printf("\ttime elapsed: %lumcs\n", time_to_complete);
    time_to_complete = timefn(aoc13_2);
    printf("\ttime elapsed: %lumcs\n", time_to_complete);

    return 0;
}
