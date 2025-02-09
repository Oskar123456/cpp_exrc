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
/* #include "./solutions/codewars.cpp" */
#include "./solutions/json_parser.cpp"

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


    /* ifstream in("resources/weather_api.json"); */
    ifstream in("resources/only_strings.json");
    string in_str;

    char b[4096];
    while (in.read(b, sizeof(b))) {
        in_str.append(b, sizeof(b));
    }
    in_str.append(b, in.gcount());

    printf("%s[+%ld...]\n", in_str.substr(0, 100).c_str(), in_str.length() - 100);

    Json json = json_parse(in_str);

    string json_str = json_write(json);

    cout << json_str << endl;

    return 0;
}




























