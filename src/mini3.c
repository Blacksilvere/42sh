/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mini3.c
*/

#include "../include/project.h"

int find_variable_in_path(char *variable, char **env)
{
    int i = 0;

    while (!my_strcmp_begin(variable, env[i]) && env[i])
        ++i;
    return i;
}

char *take_home(char **env)
{
    int pos;
    char *home;

    pos = find_variable_in_path("HOME", env);
    home = my_strcpy(env[pos]);
    while (*home++ != '=');
    if (!(*home))
        return NULL;
    else
        return (home);
}

char *take_home_by_username(char *username)
{
    char str[512];
    char *pwd = my_strcpy(getcwd(str, sizeof(str)));
    char *keep = pwd;

    while (!my_strcmp_begin(username, pwd))
        *++pwd;
    while (*++username == *++pwd);
    *pwd = '\0';
    return (keep);
}

char *take_username(char **env)
{
    int pos;
    char *username;

    pos = find_variable_in_path("USERNAME", env);
    username = my_strcpy(env[pos]);
    while (*username++ != '=');
    if (!(*username))
        return NULL;
    else
        return(take_home_by_username(username));
}

char *get_home(int bool, char **env)
{
    char *home;

    if (bool & 1) {
        home = take_home(env);
        if (!home && env[find_variable_in_path("USERNAME", env)])
            home = take_username(env);
    } else {
        home = take_username(env);
    }
    if (!home)
        return (NULL);
    return (home);
}