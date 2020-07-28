/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** str to word array
*/

#include "../include/project.h"

int count_long_array(char *str)
{
    int numberOfLine = 0;
    int if_nothing = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; ++numberOfLine) {
        for (; str[i] && !ALPANUME(str[i]); ++i);
        for (; str[i] && ALPANUME(str[i]); ++i)
            ++if_nothing;
    }
    if (!if_nothing)
        return (0);
    else
        return (numberOfLine);
}

int count_long(char *str)
{
    int i = 0;
    int a = 0;

    while (!ALPANUME(str[a]) && str[a])
        ++a;
    while (ALPANUME(str[i + a]))
        ++i;
    return (i);
}

char **str_to_word_array(char *str)
{
    int longArray = count_long_array(str);
    char **array;
    int y;
    int x;

    if (!(longArray))
        return (NULL);
    if (!(array = malloc(sizeof(char*) * (longArray + 1))))
        return (NULL);
    for (y = 0; *str && (longArray = count_long(str)); ++y) {
        while (!ALPANUME(*str) && *str)
            *++str;
        if (!(*str))
            break;
        array[y] = malloc(sizeof(char) * (longArray + 1));
        for (x = 0; ALPANUME(*str) && *str; ++x)
            array[y][x] = *str++;
        array[y][x] = '\0';
    }
    array[y] = NULL;
    return (array);
}