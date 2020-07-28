/*
** EPITECH PROJECT, 2019
** project fuction
** File description:
** project.h
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include "my.h"

#define ALPANUME(c) (((c >= 21 && c <= 127) && c != ' ') || ((unsigned char)c) >= 0xC0)
#define ALPANUME_TOKEN(c, token) ((c >= 21 && c <= 127) && c != token && c != ' ')
#define SEPARATOR(c) (c == '|' || c == '&' || c == ';' || c == '!')

typedef struct in_env_s {
    char *path;
    char *pwd;
    char *oldpwd;
}in_env_t;

typedef struct list_s {
    char **av;
    char separator;
    struct list_s *next;
    struct list_s *prev;
}list_t;

int count_long_array(char *str);
char *my_getline(void);
void *destroy_array(char **array);
void *destroy_str(char *str);
char **str_to_word_array(char *str);
char **str_to_word_token(char *str, char token);
char **function_setenv(char **array, char **env);
char *the_pwd(void);
in_env_t *global();
int find_variable_in_path(char *variable, char **env);
char *get_home(int bool, char **env);
char **function_cd(char **array, char **env);
void setup_env();
void my_exit(char *str, char **array);
char **system_fuction(char **array, char **env);
list_t *my_separator(char **av, char **env);
char **delete_variable(char **env, int pos);
int binary_exe(char **array, char **env);