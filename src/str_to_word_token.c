/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** str to word array
*/

#include "../include/project.h"

int count_token(char *str, char token)
{
    int numberOfLine = 0;
    int if_nothing = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; ++numberOfLine) {
        for (; str[i] && !ALPANUME_TOKEN(str[i], token); ++i);
        for (; str[i] && ALPANUME_TOKEN(str[i], token); ++i)
            ++if_nothing;
    }
    if (!if_nothing)
        return (0);
    else
        return (numberOfLine);
}

int count_long_token(char *str, char token)
{
    int i = 0;
    int a = 0;

    while (!ALPANUME_TOKEN(str[a], token) && str[a])
        ++a;
    while (ALPANUME_TOKEN(str[i], token))
        ++i;
    return (i);
}

char **str_to_word_token(char *str, char token)
{
    int longArray = count_token(str, token);
    char **array;
    int y;
    int x;

    if (!(longArray))
        return (NULL);
    if (!(array = malloc(sizeof(char*) * (longArray + 1))))
        return (NULL);
    for (y = 0; *str; ++y) {
        while (!ALPANUME_TOKEN(*str, token))
            *++str;
        if (!(longArray = count_long_token(str, token)))
            break;
        array[y] = malloc(sizeof(char) * (longArray + 1));
        for (x = 0; ALPANUME_TOKEN(*str, token); ++x)
            array[y][x] = *str++;
        array[y][x] = '\0';
    }
    array[y] = NULL;
    return (array);
}