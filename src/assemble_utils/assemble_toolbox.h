/**
 * @file assemble_toolbox.h
 * @brief Header file for assemble_toolbox.c.
 */

#ifndef ASSEMBLE_TOOLBOX_H
#define ASSEMBLE_TOOLBOX_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../global.h"

char **create_2d_array(unsigned int rows, unsigned int cols);
void free_2d_array(char **arr, int rows);

int lines_in_file(char *file_name);
char **load_source_file(char *load_filename, int lines);

void save_file(word_t *data, char *file_name, int ile_size);

#endif
