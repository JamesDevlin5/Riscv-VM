/*
 * Functions for extracting information from an instruction.
 */

#include <stdint.h>

uint8_t get_opcode(uint32_t instr);

uint8_t get_rd(uint32_t instr);
uint8_t get_rs1(uint32_t instr);
uint8_t get_rs2(uint32_t instr);

uint8_t get_funct3(uint32_t instr);
uint8_t get_funct7(uint32_t instr);

uint32_t get_i_imm(uint32_t instr);
uint32_t get_s_imm(uint32_t instr);
uint32_t get_b_imm(uint32_t instr);
uint32_t get_u_imm(uint32_t instr);
uint32_t get_j_imm(uint32_t instr);
