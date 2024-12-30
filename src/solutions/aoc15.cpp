/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"
#include "./util.cpp"

using namespace std;

bool inbounds(vector<string>& map, ivec2_t& pos)
{
    return false;
}

bool isin(ivec2_t p, vector<ivec2_t> ps)
{
    for (int i = 0; i < ps.size(); ++i) {
        if (ps[i] == p) return true;
    }
    return false;
}

bool bigmove(ivec2_t& pos, ivec2_t& dir, vector<string>& map)
{
    vector<ivec2_t> to_move;
    to_move.push_back(pos);

    for (int i = 0; i < to_move.size(); ++i) {
        ivec2_t p = to_move[i];
        ivec2_t p_nxt = p + dir;
        ivec2_t p_nxt_r = {p_nxt.x + 1, p_nxt.y};
        ivec2_t p_nxt_l = {p_nxt.x - 1, p_nxt.y};

        //printf("%d, %s %s\n", i, p.toString().c_str(), p_nxt.toString().c_str());

        char p_nxt_c = map[p_nxt.y][p_nxt.x];
        if (p_nxt_c == '.') continue;
        if (p_nxt_c == '#') return false;
        if (p_nxt_c == '[') {
            if (!isin(p_nxt, to_move))
                to_move.push_back(p_nxt);
            if (dir.y != 0 && !isin(p_nxt_r, to_move))
                to_move.push_back(p_nxt_r);
        }
        if (p_nxt_c == ']') {
            if (!isin(p_nxt, to_move))
                to_move.push_back(p_nxt);
            if (dir.y != 0 && !isin(p_nxt_l, to_move))
                to_move.push_back(p_nxt_l);
        }
    }

/*     printf("%s dir: %s >> to move:", pos.toString().c_str(), dir.toString().c_str()); */
/*     for (int i = 0; i < to_move.size(); ++i) { */
/*         cout << to_move[i] << ","; */
/*     } */
/*     printf("\n"); */
/*     for (int i = 0; i < map.size(); ++i) { */
/*         printf("%s\n", map[i].c_str()); */
/*     } */

    for (int i = to_move.size() - 1; i >= 0; --i) {
        ivec2_t p = to_move[i];
        ivec2_t p_nxt = p + dir;
        map[p_nxt.y][p_nxt.x] = map[p.y][p.x];
        map[p.y][p.x] = '.';
    }
    /* for (int i = 0; i < map.size(); ++i) { */
    /*     printf("%s\n", map[i].c_str()); */
    /* } */
    /* printf("\n"); */

    return true;
}

bool verf(vector<string>& map)
{
    return true;
}

void aoc15_2()
{
    u64 result = 0;

    /* ifstream input("aoc15datatest.txt", ios_base::in); */
    ifstream input("resources/aoc_data/aoc_15_data.txt", ios_base::in);

    vector<string> map;
    ivec2_t robot_pos;
    string moves;
    bool making_map = true;
    for (int i = 0; i < MAXLINE; ++i) {
        string line, bigline;
        getline(input, line, '\n');
        if (line.empty()) {
            making_map = false;
            continue;
        }
        if (making_map) {
            for (int j = 0; j < line.length(); ++j) {
                if (line[j] == '@') {
                    bigline.append("@.");
                    robot_pos.x = bigline.length() - 2;
                    robot_pos.y = i;
                }
                if (line[j] == '#') bigline.append("##");
                if (line[j] == '.') bigline.append("..");
                if (line[j] == 'O') bigline.append("[]");
            }
            map.push_back(bigline);
        } else  {
            moves.append(line);
        }
    }

    for (int i = 0; i < map.size(); ++i) {
        printf("%s\n", map[i].c_str());
    }
    printf("%s\n thing at %s\n\n", moves.c_str(), robot_pos.toString().c_str());

    string ms = "^>v<";
    vector<ivec2_t> dirs = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    for (int i = 0; i < moves.length(); ++i) {
        ivec2_t dir = dirs[ms.find_first_of(moves[i])];
        ivec2_t posn = robot_pos + dir;

        bool moved = bigmove(robot_pos, dir, map);
        if (moved)
            robot_pos = posn;

        //printf("%c (%b) %s\n", moves[i], moved, robot_pos.toString().c_str());
        /* for (int i = 0; i < map.size(); ++i) { */
        /*     printf("%s\n", map[i].c_str()); */
        /* } */

        //usleep(100000);
    }

    for (int i = 0; i < map.size(); ++i) {
        printf("%s\n", map[i].c_str());
    }

    for (int i = 1; i < map.size() - 1; ++i) {
        for (int j = 1; j < map[i].length() - 1; ++j) {
            if (map[i][j] == '[')
                result += i * 100 + j;
        }
    }

    printf("aoc 15_2: %lu\n", result);
}

bool move(ivec2_t& pos, ivec2_t& dir, vector<string>& map)
{
    ivec2_t posn = pos + dir;
    if (map[pos.y][pos.x] == '.')
        return true;
    if (map[posn.y][posn.x] == '#')
        return false;
    if (move(posn, dir, map)) {
        map[posn.y][posn.x] = map[pos.y][pos.x];
        map[pos.y][pos.x] = '.';
        return true;
    }
    return false;
}

void aoc15()
{
    u64 result = 0;

    /* ifstream input("aoc15datatest.txt", ios_base::in); */
    ifstream input("resources/aoc_data/aoc_15_data.txt", ios_base::in);

    vector<string> map;
    ivec2_t robot_pos;
    string moves;
    bool making_map = true;
    for (int i = 0; i < MAXLINE; ++i) {
        string line;
        getline(input, line, '\n');
        if (line.empty()) {
            making_map = false;
            continue;
        }
        if (making_map) {
            int x;
            if ((x = line.find('@')) >= 0) {
                robot_pos.x = x;
                robot_pos.y = i;
            }
            map.push_back(line);
        }
        else moves.append(line);
    }

    for (int i = 0; i < map.size(); ++i) {
        printf("%s\n", map[i].c_str());
    }
    printf("%s\n thing at %d %d\n\n", moves.c_str(), robot_pos.x, robot_pos.y);

    string ms = "^>v<";
    vector<ivec2_t> dirs = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    for (int i = 0; i < moves.length(); ++i) {
        ivec2_t dir = dirs[ms.find_first_of(moves[i])];
        ivec2_t new_pos = dir + robot_pos;

        if (move(robot_pos, dir, map))
            robot_pos = new_pos;

        /* for (int i = 0; i < map.size(); ++i) { */
        /*     printf("%s\n", map[i].c_str()); */
        /* } */
        /* printf("%c\n", moves[i]); */
    }

    for (int i = 1; i < map.size() - 1; ++i) {
        for (int j = 1; j < map[i].length() - 1; ++j) {
            if (map[i][j] == 'O')
                result += i * 100 + j;
        }
    }

    for (int i = 0; i < map.size(); ++i) {
        printf("%s\n", map[i].c_str());
    }

    printf("aoc 15: %lu\n", result);
}


