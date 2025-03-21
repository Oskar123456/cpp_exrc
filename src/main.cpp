/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include <obh/incl.hpp>
#include <obh/util.hpp>

#include <codecvt>
#include <string>
#include <locale>
#include <wctype.h>
#include <wchar.h>

using namespace std;

struct vertex {
    int dist;
    vec2i pos;
};
int operator<(const vertex& a, const vertex& b) { return a.dist < b.dist; }

string format_duration(int seconds)
{
    if (seconds < 1) {
        return "now";
    }

    string u[] = { "year", "day", "hour", "minute", "second" };
    int us[] = { INT32_MAX, 365 * 24 * 60 * 60, 24 * 60 * 60, 60 * 60, 60, 1 };

    vector<int> ts;
    vector<string> units;

    for (int i = 0; i < 5; ++i) {
        int t = (seconds % us[i]) / us[i + 1];
        if (t > 0) {
            ts.push_back(t);
            units.push_back(u[i]);
        }
    }

    string str;

    for (size_t i = 0; i < ts.size(); ++i) {
        if (i == ts.size() - 1 && ts.size() > 1) {
            str += " and ";
        } else if (i > 0) {
            str += ", ";
        }
        str += to_string(ts[i]) + " " + units[i] + (ts[i] > 1 ? "s" : "");
    }

    return str;
}

int main(int argc, char *argv[])
{
    cout << format_duration(1) << endl;
    cout << format_duration(777777777) << endl;
    cout << format_duration(0) << endl;

    return 0;
}




























