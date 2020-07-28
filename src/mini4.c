/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mini4.c
*/

#include "../include/project.h"

char *take_old(char **env)
{
    int pos = find_variable_in_path("OLDPWD", env);
    char *old = my_strcpy(env[pos]);

    while (*old++ != '=');
    return (old);
}

char *the_pwd(void)
{
    char str[512];
    char *pwd = my_strcpy(getcwd(str, sizeof(str)));

    return (pwd);
}

char **change_pwd(char **env)
{
    int i;
    char *commade[] = {"setenv", "PWD", global()[0].pwd, NULL};

    env = function_setenv(commade, env);
    i = find_variable_in_path("OLDPWD", env);
    if (env[i]) {
        env[i] = my_strcat("OLDPWD=", global()[0].oldpwd);
    }
    return (env);
}

void switch_pwd()
{
    char *tmp;

    tmp = global()[0].oldpwd;
    global()[0].oldpwd = global()[0].pwd;
    global()[0].pwd = tmp;
}

char **function_cd(char **array, char **env)
{
    int i;
    struct stat st;
    if (my_len_array(array) > 2) {
        write(STDOUT_FILENO, "cd: Too many arguments.\n", 24);
        return (env);
    }
    if (!array[1]) {
        if (env[find_variable_in_path("HOME", env)] || env[find_variable_in_path("USERNAME", env)]) {
            if (env[find_variable_in_path("HOME", env)]) {
                chdir(get_home(1, env));
            } else {
                chdir(get_home(0, env));
            }
            global()[0].oldpwd = global()[0].pwd;
            global()[0].pwd = the_pwd();
            env = change_pwd(env);
        } else
            write(STDERR_FILENO, "cd: No home directory.\n", 23);
    } else if (my_strcmp(array[1], "-")) {
        if (global()[0].oldpwd) {
            chdir(global()[0].oldpwd);
            switch_pwd();
            env = change_pwd(env);
        } else
            write(STDERR_FILENO, ": No such file or directory\n", 28);
    } else {
        i = chdir(array[1]);
        if (i) {
            if (stat(array[1], &st)) {
                write(STDERR_FILENO, array[1], my_strlen(array[1]));
                write(STDERR_FILENO, ": No such file or directory\n", 28);
            } else {
                write(STDERR_FILENO, array[1], my_strlen(array[1]));
                write(STDERR_FILENO, ": Not a directory.\n", 19);
            }
        } else {
            global()[0].oldpwd = global()[0].pwd;
            global()[0].pwd = the_pwd();
            env = change_pwd(env);
        }
    }
    return (env);
}