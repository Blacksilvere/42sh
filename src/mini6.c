/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mini6.c
*/

#include "../include/project.h"

char **function_unsetenv(char **array, char **env)
{
    int pos;

    ++array;
    if (!array[0]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return (env);
    }
    while (array[0]) {
        pos = find_variable_in_path(array[0], env);
        if (env[pos])
            env = delete_variable(env, pos);
        ++array;
    }
    return (env);
}

char **system_fuction(char **array, char **env)
{
    if (my_strcmp("cd", array[0])) {
        env = function_cd(array, env);
        return (env);
    }
    if (my_strcmp("setenv", array[0])) {
        env = function_setenv(array, env);
        return (env);
    }
    if (my_strcmp("unsetenv", array[0])) {
        env = function_unsetenv(array, env);
        return (env);
    }
    binary_exe(array, env);
    return (env);
}

int how_many_malloc(char **av)
{
    int i = 0;
    int a = 0;
    if (!av)
        return (1);
    while (av[i] && !a) {
        if (SEPARATOR(av[i][0])) {
            ++a;
        }
        ++i;
    }
    return(i);
}

void add_list(list_t **list)
{
    list_t *new = malloc(sizeof(list_t));

    if (!new)
        exit(84);
    new->next = NULL;
    new->separator = 0;
    new->av = NULL;
    if (!(*list))
        new->prev = NULL;
    else
        new->prev = *list;
    *list = new;
}

list_t *my_separator(char **av, char **env)
{
    list_t *list = NULL;
    list_t *keep = NULL;
    int i = 0;
    int size;

    add_list(&list);
    size = how_many_malloc(av);
    list->av = malloc(sizeof(list_t) * (size + 2));
    keep = list;
    while (av[0]) {
        if (SEPARATOR(av[0][0])) {
            list->av[i] = NULL;
            if (!i) {
                free(list->av);
                list->av = NULL;
            }
            i = 0;
            add_list(&list);
            list->prev->next = list;
            list->separator = av[0][0];
            size = how_many_malloc(av + 1);
            list->av = malloc(sizeof(list_t) * (size + 2));
        } else {
            list->av[i] = av[0];
            ++i;
        }
        ++av;
    }
    list->av[i] = NULL;
    if (!i) {
        free(list->av);
        list->av = NULL;
    }
    return (keep);
}