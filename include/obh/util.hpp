#ifndef UTIL_HPP
#define UTIL_HPP

#include "incl.hpp"

#define MAXLINE 4096

struct vec2i {
    union {
        struct { int x, y; };
        struct { int i, j; };
    };
    void rot90() { int tmp = this->x; this->x = -y; this->y = tmp; }
    int operator<(const vec2i& a) { return std::tie(this->x, this->y) < std::tie(a.x, a.y); }
    int operator==(const vec2i& a) { return this->x == a.x && this->y == a.y; }
    vec2i operator+(const vec2i& a) { return {this->x + a.x, this->y + a.y}; }
    vec2i operator-(const vec2i& a) { return {this->x - a.x, this->y - a.y}; }
    operator std::string() { return "[" + std::to_string(this->x) + "," + std::to_string(this->y) + "]"; }
    std::string toString() const { return "[" + std::to_string(this->x) + "," + std::to_string(this->y) + "]"; }
};
std::ostream & operator<<(std::ostream & Str, vec2i const & v) { return Str << v.toString(); }
int operator<(const vec2i& a, const vec2i& b) { return std::tie(a.x, a.y) < std::tie(b.x, b.y); }
int operator!=(const vec2i& a, const vec2i& b) { return a.x != b.x || a.y != b.y; }
int operator==(const vec2i& a, const vec2i& b) { return a.x == b.x && a.y == b.y; }

enum DIR { NORTH, EAST, SOUTH, WEST, DIR_NUM };
std::string DIR_NAMES[] = { "NORTH", "EAST", "SOUTH", "WEST", "DIR_NUM" };
std::string dir_name(int d) { return DIR_NAMES[d]; }
/* vec2i dirs[4] = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } }; */
/* vec2i dirsget(DIR d) { return dirs[d]; } */
vec2i dir_vecs[4] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
vec2i dir_vec(int d) { return dir_vecs[d]; }
vec2i dir_vec(DIR d) { return dir_vecs[d]; }

#endif
