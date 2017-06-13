/**
 * @file symbol_table.c
 * @brief File for functions for using and making symbol tables
 */
#include "symbol_table.h"

symbol_table_t *create_table(uint16_t row_number) {
  symbol_table_t *table = malloc(sizeof(symbol_table_t));
  if (!table) {
    perror("Unable to allocate memory for symbol table");
    exit(EXIT_FAILURE);
  }
  table->rows = malloc(sizeof(symbol_table_row_t) * row_number);
  if (!table->rows) {
    perror("Unable to allocate memory for symbol table");
    exit(EXIT_FAILURE);
  }
  table->max_size = row_number;
  table->size = 0;
  return table;
}

void add_row(symbol_table_t *table, char *label, address_t address) {
  if (is_label_in_table(table, label)) {
    fprintf(stderr, "Label already in symbol table");
    exit(EXIT_FAILURE);
  }
  symbol_table_row_t row = {
    .address = address,
  };
  memcpy(row.label, label, 15);
  if (table->size >= table->max_size) {
    table->max_size *= 2;
    table->rows = realloc(table->rows, table->max_size * sizeof(symbol_table_row_t));
    if (!table->rows) {
      perror("Unable to expand size of symbol table");
      exit(EXIT_FAILURE);
    }
  }
  table->rows[table->size] = row;
  ++table->size;
}

address_t get_address(symbol_table_t *table, char *label) {
  for (uint32_t i = 0; i < table->size; ++i) {
    if (!strcmp(table->rows[i].label, label)) {
      return table->rows[i].address;
    }
  }
  fprintf(stderr, "Label not in symbol table");
  exit(EXIT_FAILURE);
}

bool is_label_in_table(symbol_table_t *table, char *label) {
  for (uint32_t i = 0; i < table->size; ++i) {
    if (!strcmp(table->rows[i].label, label)) {
      return true;
    }
  }
  return false;
}

symbol_table_t *generate_symbol_table(string_arrays_t *tokens) {
  symbol_table_t *table = create_table(100);
  address_t address = 0;

  for (int i = 0; i < tokens->size; i++) {
    if (tokens->arrays[i]->size != 1) {
      address += 4;
    } else {
      for (int j = 0; tokens->arrays[i]->array[0][j]; j++) {
        if (tokens->arrays[i]->array[0][j] == ':') {
          tokens->arrays[i]->array[0][j] = '\0';
        }
      }
      add_row(table, tokens->arrays[i]->array[0], address);
      tokens->arrays[i]->array[0] = '\0';
    }
  }

  return table;
}

void free_table(symbol_table_t *table) {
  free(table->rows);
  free(table);
}
