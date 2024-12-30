/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"
#include <cstring>

#define MAXLINE 4096

void aoc14_2()
{
    using namespace std;
    u64 result = 0;

    //FILE *input = fopen("aoc14datatest.txt", "r");
    FILE *input = fopen("resources/aoc_data/aoc_14_data.txt", "r");

    vector<vector<int>> robots;

    char line[MAXLINE];
    while (fgets(line, MAXLINE, input)) {
        vector<int> robot_pos;
        char *line_ptr = line;
        while (*line_ptr) {
            if (!isdigit(*line_ptr) && *line_ptr != '-') {
                line_ptr++;
                continue;
            }
            i64 val = strtol(line_ptr, &line_ptr, 10);
            robot_pos.push_back(val);
        }
        robots.push_back(robot_pos);
    }

    int w = 101;
    int h = 103;
    int qs[h][w];

    for (int secs = 0; secs < 400000; ++secs) {
        memset(qs, 0, w * h * sizeof(int));
        bool overlap = false;
        for (int i = 0; i < robots.size(); ++i) {
            int pos_x = robots[i][0];
            int pos_y = robots[i][1];
            int vel_x = robots[i][2];
            int vel_y = robots[i][3];

            int pos_x_fin = (((pos_x + secs * vel_x) % w) + w) % w;
            int pos_y_fin = (((pos_y + secs * vel_y) % h) + h) % h;

            if (++qs[pos_y_fin][pos_x_fin] > 1)
                overlap = true;
        }
        if (!overlap) {
            for (int k = 0; k < h; ++k) {
                for (int m = 0; m < w; ++m) {
                    printf("%c", (qs[k][m] > 0) ? qs[k][m] + '0' : ' ');
                }
                printf("\n");
            }
            result = secs;
            break;
        }
    }

    printf("aoc 14_2: %lu\n", result);
}

void aoc14()
{
    using namespace std;
    u64 result = 0;

    //FILE *input = fopen("aoc14datatest.txt", "r");
    FILE *input = fopen("resources/aoc_data/aoc_14_data.txt", "r");

    vector<vector<int>> robots;

    char line[MAXLINE];
    while (fgets(line, MAXLINE, input)) {
        vector<int> robot_pos;
        char *line_ptr = line;
        while (*line_ptr) {
            if (!isdigit(*line_ptr) && *line_ptr != '-') {
                line_ptr++;
                continue;
            }
            i64 val = strtol(line_ptr, &line_ptr, 10);
            robot_pos.push_back(val);
        }
        robots.push_back(robot_pos);
    }

    int w = 101;
    int h = 103;
    int seconds = 100;
    int qs[2][2] = {0};

    for (int i = 0; i < robots.size(); ++i) {
        int pos_x = robots[i][0];
        int pos_y = robots[i][1];
        int vel_x = robots[i][2];
        int vel_y = robots[i][3];

        int pos_x_fin = (((pos_x + seconds * vel_x) % w) + w) % w;
        int pos_y_fin = (((pos_y + seconds * vel_y) % h) + h) % h;

        printf("%d %d\n", pos_x_fin, pos_y_fin);

        if (pos_x_fin == w / 2 || pos_y_fin == h / 2)
            continue;

        qs[pos_y_fin < h / 2][pos_x_fin < w / 2]++;

    }

    result = 1;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2;j++) {
            result *= qs[i][j];
        }
    }

    printf("aoc 14: %lu\n", result);
}


