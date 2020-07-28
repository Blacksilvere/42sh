/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** main file
*/

#include "../include/project.h"

void print_list(list_t *list)
{
    while (list) {
        list = list->next;
    }
}

void my_pipe(char **av1, char **av2, char ***env)
{
    pid_t pid_fils;
    int val;
    int descripteurTube[] = {STDIN_FILENO, STDOUT_FILENO};
    if (!av1 || !av2) {
        write(STDERR_FILENO, "Invalid null command.\n", 22);
        return;
    }
    if (pipe(descripteurTube) != 0)
        exit(84);
    pid_fils = fork();
    if (pid_fils == -1)
        exit(84);
    if (pid_fils == 0) {
        close(descripteurTube[1]);
        *env = system_fuction(av2, *env);
        exit(0);
    } else {
        close(descripteurTube[0]);
        *env = system_fuction(av1, *env);
        waitpid(pid_fils, &val, 0);
    }
}

int main(int ac, char **av, char **env)
{
    char **array = NULL;
    char *enter;
    char cwd[512];
    char **cpyenv = my_array_cpy(env);
    list_t *list;

    setup_env();
    if (ac != 1)
        return (84);
    while (1) {
        do {
            my_putstr(getcwd(cwd, sizeof(cwd)));
            my_putstr("\033[1;34m$>\033[0m");
            my_exit(enter = my_getline(), array);
        } while (!(array = str_to_word_array(enter)));
        my_exit(enter, array);
        list = my_separator(array, cpyenv);
        print_list(list);
        while (list) {
            if (!list->av) {
                write(STDERR_FILENO, "Invalid null command.\n", 22);
                break;
            }
            if (list->next) {
                if (list->next->separator == '|') {
                    my_pipe(list->av, list->next->av, &env);
                    break;
                }
            }
            cpyenv = system_fuction(list->av, cpyenv);
            list = list->next;
        }
        array = destroy_array(array);
        enter = destroy_str(enter);
    }
    return (0);
}
