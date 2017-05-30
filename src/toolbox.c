#include "toolbox.h"

void print_array(void *p, size_t bytes_to_print) {
  byte *memory = (byte *) p;
  for (size_t i = 0; i < bytes_to_print; i++) {
    printf("%i", memory[i]);

    // New line at every 4 bytes
    if (i % 16 == 15) {
      printf("\n");
    }
  }
  printf("\n");
}

word get_word(system_state *machine, address mem_address) {
  word value = 0;
  for (size_t i = 3; i >= 0; i--) {
    value = ((word) machine->memory[mem_address + i * 4]) | (value << 4);
  }
  return value;
}

word negate(word value) {
  return (~value) + 1;
}

bool is_negative(word value) {
  return value >> 31;
}

word absolute(word value) {
  if (is_negative(value)) {
    return negate(value);
  }
  return value;
}


void print_system_state(system_state *machine) {
  print_registers(machine);
  print_memory(machine);
}

void print_registers(system_state *machine) {
  printf("Register State:\n");
  for (int i = 0; i < NUM_REGISTERS; ++i) {
    printf("Register no: %d, has decimal value: %ld\n", i, twos_complement_to_long(machine->registers[i]));
    printf("Register no: %d, has binary value: ", i);
    print_binary_value(machine->registers[i]);
    printf("\n");
  }
}

void print_memory(system_state *machine) {
  printf("Memory state:\n");
  for (int i = 0; i < (NUM_ADDRESSES/4); i *= 4) {
    word word_to_print = get_word(machine, i);
    if (word_to_print) {
      printf("Memory adress: %d, has decimal value: %ld\n", i, twos_complement_to_long(word_to_print));
      printf("Memory adress: %d, has binary value: ", i);
      print_binary_value(word_to_print);
      printf("\n");
    }
  }
}

long twos_complement_to_long(word value) {
  long result = absolute(value);
  if (is_negative(value)) {
    result *= -1;
  }
  return result;
}

void print_binary_value(word value) {
  for (int i = 0; i < WORD_SIZE; ++i) {
    printf("%u", value >> (WORD_SIZE - 1));
    value <<= 1;
  }
}
