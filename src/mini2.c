/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mini2.c
*/

#include "../include/project.h"

in_env_t *global()
{
    static in_env_t glogal[1];
    return (glogal);
}

void setup_env()
{
    global()[0].path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
    global()[0].pwd = the_pwd();
    global()[0].oldpwd = NULL;
}

void my_exit(char *str, char **array)
{
    if (!str) {
        my_putstr("exit\n");
        exit(0);
    }
    if (array) {
        if (my_strcmp(array[0], "exit")) {
            (str) ? (str = destroy_str(str)) : (0);
            destroy_array(array);
            my_putstr("exit\n");
            exit(0);
        }
    }
}

void *destroy_array(char **array)
{
    for (int i = 0; array[i]; ++i)
        free(array[i]);
    free(array);
    return NULL;
}

void *destroy_str(char *str)
{
    free(str);
    return (NULL);
}