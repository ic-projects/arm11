#include <stdbool.h>
#include "instruction.h"
#include "constants.h"
#include "system_state.c"
#include "toolbox.c"

void execute(system_state machine, instruction operation) {
  if (condition(operation.cond)) {
    switch (operation.code) {
      case DPI:
        execute_dpi(machine, operation);
        break;
      case MUL:
        break;
      case SDT:
        break;
      case BRA:
        break;

    }
  }
}

void execute_dpi(system_state machine, instruction operation) {
  unsigned long op2;
  unsigned char shifter_carry = 0;
  unsigned long shift_ammount;

  if (operation.flag_0) {
    op2 = machine.registers[operation.rm];
    if (operation.rs == -1) {
      shift_ammount = operation.immediate_value;
    } else {
      shift_ammount = machine.registers[operation.rs];
    }
  } else {
    op2 = operation.immediate_value;
    shift_ammount = operation.shift_amount;
  }
  shift shifter_out = shifter(op2, operation.shift_type, shift_ammount);
  op2 = shifter_out.value;
  shifter_carry = shifter_out.carry;

  unsigned long flags = 0;
  unsigned char N = 0x8;
  unsigned char Z = 0x4;
  unsigned char C = 0x2;
  unsigned long result;
  switch (operation.operation) {
    case AND:
    case TST:
      result = machine.registers[operation.rn] & op2;
      flags = C * shifter_carry;
      break;
    case EOR:
    case TEQ:
      result = machine.registers[operation.rn] ^ op2;
      flags = C * shifter_carry;
      break;
    case SUB:
    case CMP:
      result = machine.registers[operation.rn] + negate(op2);
      flags = C * !is_negative(result);
      break;
    case RSB:
      result = op2 + negate(machine.registers[operation.rn]);
      flags = C * !is_negative(result);
      break;
    case ADD:
      result = machine.registers[operation.rn] + op2;
      flags = C * (result < op2);
      break;
    case ORR:
      result = machine.registers[operation.rn] | op2;
      flags = C * shifter_carry;
      break;
    case MOV:
      result = op2;
      flags = C * shifter_carry;
      break;
    default:
      fprintf(stderr, "Unknown opcode at PC: %u", machine.registers[PC] - 0x40); // Is this our error message?
      exit_program();
      break;
  }
  flags = flags | (N * is_negative(result));
  flags = flags | (Z * (result == 0));
  if (!(operation.operation == TST || operation.operation == TEQ || operation.operation == CMP)) {
    machine.registers[operation.rd] = result;
  }
  if (operation.flag_1) {//If set flags
    machine.registers[CPSR] = flags << 28;
  }
}

unsigned long negate(unsigned long value) {
  return (~value) + 1;
}

unsigned long absolute(unsigned long value) {
  if (is_negative(value)) {
    return negate(value);
  }
  return value;
}

bool is_negative(unsigned long value) {
  return value >> 31;
}