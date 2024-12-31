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

void aoc21_2()
{
}

void aoc21()
{
    i64 result = 0;

    vector<string> data;

    string line;
    ifstream input("aoc_21_data.txt", ios_base::in);
    /* ifstream input("resources/aoc_data/aoc_21_data.txt", ios_base::in); */
    int mode = 0;
    while (getline(input, line, '\n'))
        if (line.length() > 0)
            data.push_back(line);

    for (auto s : data)
        cout << s << endl;

    map<char, vec2i> keypad;
    map<char, vec2i> dirpad;

    keypad.emplace('7', (vec2i){0, 0});
    keypad.emplace('8', (vec2i){0, 1});
    keypad.emplace('9', (vec2i){0, 2});

    keypad.emplace('4', (vec2i){1, 0});
    keypad.emplace('5', (vec2i){1, 1});
    keypad.emplace('6', (vec2i){1, 2});

    keypad.emplace('1', (vec2i){2, 0});
    keypad.emplace('2', (vec2i){2, 1});
    keypad.emplace('3', (vec2i){2, 2});

    keypad.emplace('0', (vec2i){3, 1});
    keypad.emplace('A', (vec2i){3, 2});

    dirpad.emplace('^', (vec2i){0, 1});
    dirpad.emplace('A', (vec2i){0, 2});

    dirpad.emplace('<', (vec2i){1, 0});
    dirpad.emplace('v', (vec2i){1, 1});
    dirpad.emplace('>', (vec2i){1, 2});

    for (auto s : data) {
        i64 val = strtol(s.c_str(), NULL, 10);

        string kp_prs;
        char c = 'A';
        for (char cn : s) {
            vec2i cp = keypad[c];
            vec2i cnp = keypad[cn];

/*             printf("%c at %s\n", c, cp.toString().c_str()); */
/*             printf("%c at %s\n", cn, cnp.toString().c_str()); */

            int di = cnp.i - cp.i;
            int dj = cnp.j - cp.j;

            string stri;
            string strj;
            char stepc = (di < 0) ? '^' : 'v';
            for (int i = 0; i < abs(di); ++i)
                stri.push_back(stepc);
            stepc = (dj < 0) ? '<' : '>';
            for (int i = 0; i < abs(dj); ++i)
                stri.push_back(stepc);

            printf("%c (%s) --> %c (%s) : %s%s\n", c, cp.toString().c_str(),
                    cn, cnp.toString().c_str(), stri.c_str(), strj.c_str());

            kp_prs.append(stri);
            kp_prs.append(strj);
            kp_prs.append("A");

            c = cn;
        }

        printf("[%s]:\t%s (%ld, val: %ld)\n", s.c_str(), kp_prs.c_str(), kp_prs.length(), val);

        string dp_prs;
        for (char cn : kp_prs) {
            vec2i cp = dirpad[c];
            vec2i cnp = dirpad[cn];

/*             printf("%c at %s\n", c, cp.toString().c_str()); */
/*             printf("%c at %s\n", cn, cnp.toString().c_str()); */

            int di = cnp.i - cp.i;
            int dj = cnp.j - cp.j;

            string stri;
            string strj;
            char stepc = (di < 0) ? '^' : 'v';
            for (int i = 0; i < abs(di); ++i)
                stri.push_back(stepc);
            stepc = (dj < 0) ? '<' : '>';
            for (int i = 0; i < abs(dj); ++i)
                stri.push_back(stepc);

            printf("%c (%s) --> %c (%s) : %s%s\n", c, cp.toString().c_str(),
                    cn, cnp.toString().c_str(), stri.c_str(), strj.c_str());

            dp_prs.append(stri);
            dp_prs.append(strj);
            dp_prs.append("A");

            c = cn;
        }

        printf("[%s]:\t%s (%ld)\n", kp_prs.c_str(), dp_prs.c_str(), dp_prs.length());

        string dp_prs2;
        for (char cn : dp_prs) {
            vec2i cp = dirpad[c];
            vec2i cnp = dirpad[cn];

/*             printf("%c at %s\n", c, cp.toString().c_str()); */
/*             printf("%c at %s\n", cn, cnp.toString().c_str()); */

            int di = cnp.i - cp.i;
            int dj = cnp.j - cp.j;

            string stri;
            string strj;
            char stepc = (di < 0) ? '^' : 'v';
            for (int i = 0; i < abs(di); ++i)
                stri.push_back(stepc);
            stepc = (dj < 0) ? '<' : '>';
            for (int i = 0; i < abs(dj); ++i)
                stri.push_back(stepc);

            printf("%c (%s) --> %c (%s) : %s%s\n", c, cp.toString().c_str(),
                    cn, cnp.toString().c_str(), stri.c_str(), strj.c_str());

            dp_prs2.append(stri);
            dp_prs2.append(strj);
            dp_prs2.append("A");

            c = cn;
        }

        i64 r = dp_prs2.length() * val;
        printf("[%s]:\t%s (len: %ld, val: %ld, score: %ld)\n", dp_prs.c_str(), dp_prs2.c_str(), dp_prs2.length(), val, r);

        result += r;
    }

    printf("aoc21:  \t%ld\n", result);
}
