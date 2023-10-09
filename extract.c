#include "extract.h"

/*
 * Getter for the opcode of the instruction.
 *
 * Bits [6:0]
 */
uint8_t get_opcode(uint32_t instr) {
    return instr & 0x7F;
}

/*
 * Getter for the destination register of the instruction.
 *
 * Bits [11:7]
 */
uint8_t get_rd(uint32_t instr) {
    return (instr >> 7) & 0x1F;
}

/*
 * Getter for the first source register of the instruction.
 *
 * Bits [19:15]
 */
uint8_t get_rs1(uint32_t instr) {
    return (instr >> 15) & 0x1F;
}

/*
 * Getter for the second source register of the instruction.
 *
 * Bits [24:20]
 */
uint8_t get_rs2(uint32_t instr) {
    return (instr >> 20) & 0x1F;
}

/*
 * Getter for the funct3 field of an R/I/S/B-type instruction.
 *
 * Bits [14:12]
 */
uint8_t get_funct3(uint32_t instr) {
    return (instr >> 12) & 0x7;
}

/*
 * Getter for the funct7 field of an R-type instruction.
 *
 * Bits [31:25]
 */
uint8_t get_funct7(uint32_t instr) {
    return (instr >> 25) & 0x7F;
}

/*
 * Getter for the immediate of an I-type instruction.
 *
 * imm[11:0] = Bits [31:20]
 */
uint32_t get_i_imm(uint32_t instr) {
    return instr >> 20;
}

/*
 * Getter for the immediate of an S-type instruction.
 *
 * imm[11:5] = Bits [31:25]
 * imm[4:0]  = Bits [11:7]
 */
uint32_t get_s_imm(uint32_t instr) {
    uint32_t upper = instr >> 25;
    uint32_t lower = (instr >> 7) & 0x1F;
    return (upper << 5) | lower;
}

/*
 * Getter for the immediate of a B-type instruction.
 *
 * imm[12]   = Bit  [31]
 * imm[11]   = Bit  [7]
 * imm[10:5] = Bits [30:25]
 * imm[4:1]  = Bits [11:8]
 * imm[0]    = 0
 */
uint32_t get_b_imm(uint32_t instr) {
    // TODO
}

/*
 * Getter for the immediate of a U-type instruction.
 *
 * imm[31:12] = Bits [31:12]
 * imm[11:0]  = 0
 */
uint32_t get_u_imm(uint32_t instr) {
    // TODO
}

/*
 * Getter for the immediate of a J-type instruction.
 *
 * imm[20]    = Bit  [31]
 * imm[19:12] = Bits [19:12]
 * imm[11]    = Bit  [20]
 * imm[10:1]  = Bits [30:21]
 * imm[0]     = 0
 */
uint32_t get_j_imm(uint32_t instr) {
    // TODO
}
