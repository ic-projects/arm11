#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdint.h>

#define NUM_REGISTERS 17
#define NUM_ADDRESSES 65536
#define WORD_SIZE 32
#define PC 15
#define CPSR 16
#define MASK_FIRST_4 0xFFFFFFF
#define MASK_FIRST_6 0x3FFFFFF
#define MASK_FIRST_8 0xFFFFFF
#define COMPLIANT_MODE true

typedef enum {
  EQ = 0,
  NE = 1,
  GE = 0xA,
  LT = 0xB,
  GT = 0xC,
  LE = 0xD,
  AL = 0xE,
} condition_t;

/**
 * @brief An enum that identifies the format of the instruction
 */
typedef enum {
  /** Data processing instruction */
  DPI,
  /** Multiply instruction */
  MUL,
  /** Single data transfer instruction */
  SDT,
  /** Branch instruction */
  BRA,
  /** All zero (STOP) instruction */
  ZER,
  /** NULL (not present) instruction */
  NUL,
} instruction_type_t;

/**
 * @brief An enum used for defining the the type of shift for the shifter to use
 */
typedef enum {
  /** LSL = logical shift left */
  LSL = 0,
  /** LSR = logical shift right */
  LSR = 1,
  /** ASR = arithmetic shift right */
  ASR = 2,
  /** ROR = rotate right */
  ROR = 3,
} shift_t;

typedef enum {
  AND = 0x0,
  EOR = 0x1,
  SUB = 0x2,
  RSB = 0x3,
  ADD = 0x4,
  TST = 0x8,
  TEQ = 0x9,
  CMP = 0xA,
  ORR = 0xC,
  MOV = 0xD,
} opcode_t;

/**
 * @brief An enum used for retrieving individual flag bits from CPSR register
 */
typedef enum {
  /** N (bit 4): the last result was negative */
  N = 0x8,
  /** Z (bit 3): the last result was zero */
  Z = 0x4,
  /** C (bit 2): the last result caused a bit to be carried out */
  C = 0x2,
  /** V (bit 1): the last result overflowed */
  V = 0x1,
} cpsr_flags_t;

typedef enum {
  ADD_M,
  SUB_M,
  RSB_M,
  AND_M,
  EOR_M,
  ORR_M,
  MOV_M,
  TST_M,
  TEQ_M,
  CMP_M,
  MUL_M,
  MLA_M,
  LDR_M,
  STR_M,
  BEQ_M,
  BNE_M,
  BGE_M,
  BLT_M,
  BGT_M,
  BLE_M,
  B_M,
  ANDEQ_M,
} mnemonic_t;

typedef uint8_t byte_t;
typedef int8_t reg_address_t;
typedef uint16_t address_t;
typedef uint32_t word_t;

#endif
