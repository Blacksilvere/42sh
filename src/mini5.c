/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mini5.c
*/

#include "../include/project.h"

char **mix_the_path_and_env(char *comande)
{
    char **result;
    char *cpypath = my_strcpy((global()[0].path));
    char **cpy;
    char **keep;
    int i;

    if (!cpypath)
        return (NULL);
    result = str_to_word_token(cpypath, ':');
    cpy = malloc(sizeof(char*) * (my_len_array(result) + 3));
    keep = cpy;
    for (i = 0; result[i]; ++i, *++cpy) {
        *cpy = my_strcat(result[i], my_strcat("/", comande));
    }
    *cpy++ = comande;
    *cpy = NULL;
    return (keep);
}

char **arraycat(char *path, char **argument)
{
    char **mix = malloc(sizeof(char*) * (my_len_array(argument) + 2));
    int i = 1;

    mix[0] = path;
    if (argument[1]) {
        for (i = 2; argument[i - 1]; ++i) {
            mix[i - 1] = argument[i - 1];
        }
    }
    mix[i] = NULL;
    return (mix);
}

int binary_exe(char **array, char **env)
{
    int i;
    char **pathMix = mix_the_path_and_env(array[0]);
    int waitvalue = 0;
    pid_t pid;

    if (!pathMix)
        return (1);
    for (i = 0; access(pathMix[i], F_OK | X_OK); ++i) {
        if (!pathMix[i + 1])
            break;
    }
    if(!pathMix[i + 1] && access(pathMix[i], F_OK | X_OK)) {
        write(2, array[0], my_strlen(array[0]));
        write(2, ": Command not found.\n", 21);
        return (1);
    }
    pathMix = arraycat(pathMix[i], array);
    if (!(pid = fork()))
        execve(pathMix[0], pathMix, env);
    else
        waitpid(pid, &waitvalue, 0);
    if (waitvalue) {
        if (WIFSIGNALED(waitvalue)) {

        int terminate_signal = WTERMSIG(waitvalue);

        if (terminate_signal == 11)
            write(STDERR_FILENO, "Segmentation fault\n", 19);

        if (terminate_signal == 8)
            write(STDERR_FILENO, "Floating exception\n", 19);
        }
    }
    return (0);
}

char **delete_variable(char **env, int pos)
{
    char **newenv = malloc(sizeof(char*) * (my_len_array(env) + 3));
    char **keep = newenv;

    for (int i = 0; env[i]; ++i) {
        if (i != pos) {
            newenv[0] = env[i];
            ++newenv;
        }
    }
    newenv[0] = NULL;
    return (keep);
}

char **function_setenv(char **array, char **env)
{
    int i = 0;
    char *keep;
    if (my_len_array(array) > 3) {
        write(STDOUT_FILENO, "setenv: Too many arguments.\n", 28);
        return (env);
    }
    if ((array[1][0] < 'a' || array[1][0] > 'z') && (array[1][0] > 'Z' || array[1][0] < 'A') && array[1][0] != '_') {
        write(STDOUT_FILENO, "setenv: Variable name must begin with a letter.\n", 48);
        return (env);
    }
    if (my_len_array(array) == 1) {
        for (int j = 0; env[j]; ++j) {
            my_putstr(env[j]);
            write(STDOUT_FILENO, "\n", 1);
        }
        return (env);
    }
    i = find_variable_in_path(array[1], env);
    if (!env[i]) {
        env = delete_variable(env, -1);
        (array[2]) ? (env[i] = my_strcat(my_strcat(array[1], "="), array[2])) : (env[i] = my_strcat(array[1], "="));
        env[i + 1] = NULL;
    } else {
        keep = env[i];
        while (*keep++ != '=');
        (*keep = '\0');
        if (array[2])
            env[i] = my_strcat(env[i], array[2]);
    }
    return (env);
}