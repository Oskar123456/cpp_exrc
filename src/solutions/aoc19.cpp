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
    FILE *input = fopen("aoc_19_data.txt", "r");
    /* FILE *input = fopen("resources/aoc_data/aoc_19_data.txt", "r"); */
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

    qsort(ptrns, arrlen(ptrns), sizeof(char*), strlen_cmp);

    int arr[512];
    for (int i = 0; i < arrlen(ptrns); ++i) {
        int score = word_score(ptrns, i, 0, arr, 0);
        arrput(ptrn_scores, score);
    }

    for (int i = 0; i < arrlen(ptrns); ++i) {
        printf("%s (%d)", ptrns[i], ptrn_scores[i]);
        if (i < arrlen(ptrns) - 1) printf(", ");
    }
    printf("\n");

    for (int i = 0; i < arrlen(targs); ++i) {
        int idx = 0;
        int score = 1;
        int t_len = strlen(targs[i]);
        while (targs[i][idx]) {
            bool m = false;
            for (int j = arrlen(ptrns) - 1; j >= 0; --j) {
                /* printf("[scoring] testing if %s matched by %s\n", &targs[i][idx], ptrns[j]); */
                int p_len = strlen(ptrns[j]);
                if (p_len > t_len - idx)
                    continue;
                if (strncmp((const char*)&targs[i][idx], ptrns[j], p_len))
                    continue;
                printf("[scoring] %s matched by %s (%d) for total %d * %d = %d\n",
                        &targs[i][idx], ptrns[j], ptrn_scores[j], ptrn_scores[j], score, ptrn_scores[j] * score);
                idx += p_len;
                score *= ptrn_scores[j];
                m = true;
                break;
            }
            if (!m) {
                score = 0;
                break;
            }
        }
        printf("there are %d ways to make %s\n", score, targs[i]);
        result += score;
    }

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
