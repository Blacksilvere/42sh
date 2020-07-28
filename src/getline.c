/*
** EPITECH PROJECT, 2020
** matchsticks
** File description:
** take the standar input
*/

#include "../include/project.h"

char *my_getline(void)
{
    char *buffer;
    size_t bufsize = 32;
    int rd;

    buffer = malloc(bufsize * sizeof(char));
    if(!buffer) {
        return (NULL);
    }
    if ((rd = getline(&buffer,&bufsize,stdin)) < 0) {
        free(buffer);
        return (NULL);
    }
    buffer[rd - 1] = '\0';
    return (buffer);
}
