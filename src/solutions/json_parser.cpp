/*****************************************************
Create Date:        2025-02-09
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template for things like
                    codewars etc.
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"
#include "../../include/obh/util.hpp"

#include <algorithm>

using namespace std;

/* data types */
enum Json_Type { JT_NONE, JT_NULL, JT_STRING, JT_NUMBER, JT_BOOLEAN, JT_ARRAY, JT_OBJECT };
typedef struct Json Json;
typedef struct Json_Field Json_Field;
typedef struct Json_Object Json_Object;
/* parsing */
Json json_parse(string& str);
int json_parse_str(string& str, string& str_out, int& i);
Json_Field json_parse_num(string& str, int& i);
void json_parse_obj(string& str, Json_Object& obj, int& i);
Json_Field json_parse_arr(string& str, int& i);
Json_Field json_parse_field(string& str, int& i);
void json_parse_error(string& str, int& i);
/* write */
string json_write(Json& json);
void json_write_object(string& str, Json_Object obj, int depth);
/* util */
int json_skip_ws(string& str, int& i);
/* implementation */
struct Json_Object { vector<Json_Field> children; };
struct Json_Field { string name; Json_Type type; string str; double num; bool _bool; Json_Object obj; vector<Json_Field> arr; };
struct Json { Json_Type type; Json_Field field; };

static int indentation = 2;

void json_write_newline_indent(string& str, bool comma, int depth)
{
    if (comma)
        str.push_back(',');
    str.push_back('\n');
    for (int i = 0; i < depth * indentation; ++i) {
        str.push_back(' ');
    }
}

string json_write(Json& json)
{
    string str;

    if (json.type == JT_NONE)
        str.append("error parsing...");

    /* if (json.type == JT_OBJECT) */
    /*     str.push_back('{'); */
    /* if (json.type == JT_ARRAY) */
    /*     str.push_back('['); */

    switch (json.type) {
        case JT_OBJECT:
            json_write_object(str, json.field.obj, 1);
            break;
        case JT_ARRAY:
            break;
        default:
            break;
    }

    /* if (json.type == JT_OBJECT) */
    /*     str.push_back('}'); */
    /* if (json.type == JT_ARRAY) */
    /*     str.push_back(']'); */

    return str;
}

void json_write_object(string& str, Json_Object obj, int depth)
{
    /* for (int i = 0; i < depth * indentation; ++i) */
    /*     str.push_back(' '); */

    str.push_back('{');

    for (int i = 0; i < obj.children.size(); ++i) {
        Json_Field jsf = obj.children[i];
        json_write_newline_indent(str, (i != 0), depth);
        switch (jsf.type) {
            case (JT_STRING):
                str.append(jsf.name + " : " + jsf.str);
                break;
            case JT_OBJECT:
                str.append(jsf.name + " : ");
                json_write_object(str, jsf.obj, depth + 1);
                break;
            default:
                break;
        }
    }

    str.push_back('\n');
    for (int i = 0; i < (depth - 1) * indentation; ++i)
        str.push_back(' ');
    str.append("}");
}

int json_skip_ws(string& str, int& i)
{
    while (i < str.length() && iswspace(str[i]))
        i++;
    return i;
}

Json json_parse(string& str)
{
    Json js;

    int i = 0;
    json_skip_ws(str, i);

    if (str[i] == '{') {
        js.type = JT_OBJECT;
        js.field.type = JT_OBJECT;
        json_parse_obj(str, js.field.obj, ++i);
    }
    else if (str[i] == '[') {
        /* js.type = JT_ARRAY; */
        /* js.field.type = JT_ARRAY; */
        /* js.field.arr = json_parse_arr(str, ++i); */
    }
    else {
        js.type = JT_NONE;
    }

    return js;
}

Json_Field json_parse_field(string& str, int& i)
{
    Json_Field jsf;

    json_skip_ws(str, i);
    if (i >= str.length() || str[i] != '"')
        goto FAIL;

    /* printf("at beginning of id\n"); */

    json_parse_str(str, jsf.name, ++i);
    if (i >= str.length())
        goto FAIL;

    /* printf("parsed id \"%s\"\n", jsf.name.c_str()); */

    json_skip_ws(str, i);
    if (str[i] != ':')
        goto FAIL;

    /* printf("at beginning of value\n"); */

    json_skip_ws(str, ++i);
    if (i >= str.length())
        goto FAIL;

    switch (str[i]) {
        case '"':
            jsf.type = JT_STRING;
            json_parse_str(str, jsf.str, ++i);
            /* printf("parsed value \"%s\"\n", jsf.str.c_str()); */
            break;
        case '{':
            jsf.type = JT_OBJECT;
            json_parse_obj(str, jsf.obj, ++i);
            /* printf("parsed value \"%s\"\n", jsf.str.c_str()); */
            break;
        default:
            goto FAIL;
            break;
    }

    return jsf;
FAIL:
    jsf.type = JT_NONE;
    json_parse_error(str, i);
    return jsf;
}

int json_parse_str(string& str, string& str_out, int& i)
{
    bool escaped = false;
    while (i < str.length() && !(!escaped && str[i] == '"')) {
        if (!escaped && str[i] == '\\')
            escaped = true;
        else {
            str_out.push_back(str[i]);
            escaped = false;
        }
        ++i;
    }

    if (i >= str.length())
        return -1;
    return ++i;
}

Json_Field json_parse_num(string& str, int& i)
{
    Json_Field jsf;

    return jsf;
}

Json_Field json_parse_bool(string& str, int& i)
{
    Json_Field jsf;

    return jsf;
}

void json_parse_obj(string& str, Json_Object& obj, int& i)
{
    for (;;) {
        Json_Field field = json_parse_field(str, i);
        if (field.type != JT_NONE)
            obj.children.push_back(field);
        else
            break;
        json_skip_ws(str, i);
        if (str[i] != ',')
            break;
        ++i;
    }
}

Json_Field json_parse_arr(string& str, int& i)
{
    Json_Field jsf;

    return jsf;
}

void json_parse_id(string& str, string& str_out, int& i)
{
}

void json_parse_error(string& str, int& i)
{
    printf("failed parsing at %d:\n%s[[[%c]]]%s[+%d...]\n", i,
            str.substr(0, i).c_str(), str[i],
            str.substr(i + 1, (min((int)str.length() - i - 1, 20))).c_str(),
            (int)str.length() - i - 1 - 20);
}

































