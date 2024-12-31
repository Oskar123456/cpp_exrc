/*****************************************************
Create Date:        2024-12-12
Author:             Oskar Bahner Hansen
Email:              oskarbahner@gmail.com
Description:        exercise template
License:            none
*****************************************************/

#include "../../include/obh/incl.hpp"
#include "../../include/obh/util.hpp"

#define STB_DS_IMPLEMENTATION
#include "../../include/stb/stb_ds.h"

using namespace std;

int strlen_cmp(const void* a, const void* b)
{
    return (int)strlen(*(char**)a) - (int)strlen(*(char**)b);
}

bool make_pattern_2(const char** ptrns, int* ptrn_lens, int ptrn_num,
        const char* targ, int targ_len, int targ_idx, i64 *sum)
{
    if (targ_idx >= targ_len)  {
        *sum = *sum + 1;
        /* printf("result is %ld atm\n", *sum); */
        return true;
    }
    for (int i = 0; i < ptrn_num; ++i) {
        if (ptrn_lens[i] > targ_len - targ_idx)
            continue;
        if (strncmp(&targ[targ_idx], ptrns[i], ptrn_lens[i]) == 0) {
            make_pattern_2(ptrns, ptrn_lens, ptrn_num, targ, targ_len, targ_idx + ptrn_lens[i], sum);
        }
    }
    return true;
}

i64 word_score(char** ptrns, int ptrns_idx, int word_idx, int* ptrns_used, int ptrns_used_num)
{
    if (word_idx >= strlen(ptrns[ptrns_idx])) {
        printf("%s matched by ", ptrns[ptrns_idx]);
        for (int i = 0; i < ptrns_used_num; ++i) {
            printf("%s", ptrns[ptrns_used[i]]);
            if (i < ptrns_used_num - 1)
                printf("|");
        }
        printf("\n");
        return 1;
    }

    i64 sum = 0;

    for (int i = 0; i <= ptrns_idx; ++i) {
        int plen = strlen(ptrns[ptrns_idx]);
        int mlen = strlen(ptrns[i]);
        if (mlen > plen - word_idx)
            continue;
        if (strncmp(ptrns[i], &ptrns[ptrns_idx][word_idx], mlen) == 0) {
            ptrns_used[ptrns_used_num] = i;
            sum += word_score(ptrns, ptrns_idx, word_idx + mlen, ptrns_used, ptrns_used_num + 1);
        }
    }


    return sum;
}

void aoc19_2()
{
    i64 result = 0;

    char **ptrns = NULL;
    int *ptrn_scores = NULL;

    char **targs = NULL;

    char line[MAXLINE];
    /* FILE *input = fopen("aoc_19_data.txt", "r"); */
    FILE *input = fopen("resources/aoc_data/aoc_19_data.txt", "r");
    int mode = 0;
    while (fgets(line, MAXLINE, input)) {
        if (strlen(line) < 2) {
            mode++;
            continue;
        }

        char *line_ptr = line, *line_ptr_p = line;
        if (mode == 0) {
            while ((line_ptr = strpbrk(line_ptr_p, ",\n"))) {
                char *s = strndup(line_ptr_p, line_ptr - line_ptr_p);
                arrput(ptrns, s);
                line_ptr_p = line_ptr + 2;
            }
        } else {
            char *s = strndup(line, strlen(line) - 1);
            arrput(targs, s);
        }
    }

    /*******************/

    printf("patterns:\t");
    for (int i = 0; i < arrlen(ptrns); ++i) {
        printf("%s", ptrns[i]);
        if (i < arrlen(ptrns) - 1)
            printf(", ");
    }
    printf("\n");

    for (int i = 0; i < arrlen(targs); ++i) {
        char *s = targs[i];
        int slen = strlen(s);
        u64 matched[slen + 1] = {0};
        matched[0] = 1;

        char res[1024];
        int nwritten = 0;
        nwritten += sprintf(res, "_%s_:\t", s);

        for (int k = 0; k < slen; ++k) {
            if (!matched[k])
                continue;
            for (int j = 0; j < arrlen(ptrns); ++j) {
                char *p = ptrns[j];
                int plen = strlen(p);
                if (plen > slen - k)
                    continue;
                if (strncmp(&s[k], p, plen) == 0) {
                    matched[k + plen] += matched[k];
                }
            }
        }

        if (matched[slen]) {
            printf("✓ %s (%lu)\n", res, matched[slen]);
            result += matched[slen];
        } else
            printf("☒ %s (%lu)\n", res, matched[slen]);
    }

    /*******************/

    printf("aoc19_2:  \t%ld\n", result);
}

bool make_pattern(const char** ptrns, int* ptrn_lens, int ptrn_num, const char* targ, int targ_len, int targ_idx, char *cur, int cur_num)
{
    if (targ_idx >= targ_len)  {
        cur[targ_idx + cur_num] = 0;
        printf("%s == %s\n", targ, cur);
        return true;
    }
    for (int i = 0; i < ptrn_num; ++i) {
        if (ptrn_lens[i] > targ_len - targ_idx)
            continue;
        if (strncmp(&targ[targ_idx], ptrns[i], ptrn_lens[i]) == 0) {
            cur[targ_idx + ptrn_lens[i] + cur_num] = '_';
            memcpy(&cur[targ_idx + cur_num], ptrns[i], ptrn_lens[i]);
            if (make_pattern(ptrns, ptrn_lens, ptrn_num, targ, targ_len, targ_idx + ptrn_lens[i], cur, cur_num + 1))
                return true;
        }
    }
    return false;
}

void aoc19()
{
    i64 result = 0;

    const char **ptrns = NULL;
    int *ptrn_lens = NULL;

    const char **targs = NULL;
    int *targ_lens = NULL;

    char line[MAXLINE];
    /* FILE *input = fopen("aoc_19_data.txt", "r"); */
    FILE *input = fopen("resources/aoc_data/aoc_19_data.txt", "r");
    int mode = 0;
    while (fgets(line, MAXLINE, input)) {
        if (strlen(line) < 2) {
            mode++;
            continue;
        }

        char *line_ptr = line, *line_ptr_p = line;
        if (mode == 0) {
            while ((line_ptr = strpbrk(line_ptr_p, ",\n"))) {
                char *s = strndup(line_ptr_p, line_ptr - line_ptr_p);
                arrput(ptrns, s);
                int l = strlen(s);
                arrput(ptrn_lens, l);
                line_ptr_p = line_ptr + 2;
            }
        } else {
            char *s = strndup(line, strlen(line) - 1);
            arrput(targs, s);
            int l = strlen(s);
            arrput(targ_lens, l);
        }
    }

    for (int i = 0; i < arrlen(ptrns); ++i) {
        printf("%s (%d)", ptrns[i], ptrn_lens[i]);
        if (i < arrlen(ptrns) - 1) printf(", ");
    }
    printf("\n");
/*     for (int i = 0; i < arrlen(targs); ++i) { */
/*         printf("%s (%d)\n", targs[i], targ_lens[i]); */
/*     } */
/*     printf("\n"); */

    char buf[MAXLINE];
    for (int i = 0; i < arrlen(targs); ++i) {
        if (make_pattern(ptrns, ptrn_lens, arrlen(ptrns), targs[i], targ_lens[i], 0, buf, 0))
            result++;
    }

    printf("aoc19:  \t%ld\n", result);
}
