/*
 * 32-bit RISC-V Virtual Machine
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int debug = true;

/*** RAM ***/
// {{{

#define MEMORY_MAX (1UL << 16)

uint32_t memory[MEMORY_MAX];

// }}}

/*** Registers ***/
// {{{

enum Register_E {
    R_ZERO = 0,
    R_RA   = 1,
    R_SP   = 2,
    R_GP   = 3,
    R_TP   = 4,
    R_T0   = 5,
    R_T1   = 6,
    R_T2   = 7,
    R_S0   = 8,
    R_FP   = 8, // Same as s0
    R_S1   = 9,
    R_A0   = 10,
    R_A1   = 11,
    R_A2   = 12,
    R_A3   = 13,
    R_A4   = 14,
    R_A5   = 15,
    R_A6   = 16,
    R_A7   = 17,
    R_S2   = 18,
    R_S3   = 19,
    R_S4   = 20,
    R_S5   = 21,
    R_S6   = 22,
    R_S7   = 23,
    R_S8   = 24,
    R_S9   = 25,
    R_S10  = 26,
    R_S11  = 27,
    R_T3   = 28,
    R_T4   = 29,
    R_T5   = 30,
    R_T6   = 31
};

uint32_t reg[32];

// }}}

/*** Op Codes ***/
// {{{

/*
 * Op Codes, derived from bits [6:0] of instruction
 */
enum OpCode_E {
    OP_LUI    = 0b0110111,
    OP_AUIPC  = 0b0010111,
    OP_JAL    = 0b1101111,
    OP_JALR   = 0b1100111,
    OP_BRANCH = 0b1100011,
    OP_LOAD   = 0b0000011,
    OP_STORE  = 0b0100011,
    OP_I_TYPE = 0b0010011,
    OP_R_TYPE = 0b0110011,
    OP_ECALL  = 0b1110011
};

/*
 * Different types of branches (B-type), derived from bits [14:12] of instruction
 */
enum BranchCode_E {
    OP_BEQ  = 0b000,
    OP_BNE  = 0b001,
    OP_BLT  = 0b100,
    OP_BGE  = 0b101,
    OP_BLTU = 0b110,
    OP_BGEU = 0b111
};

/*
 * Different types of loads (I-type), derived from bits [14:12] of instruction
 */
enum LoadCode_E {
    OP_LB  = 0b000,
    OP_LH  = 0b001,
    OP_LW  = 0b010,
    OP_LBU = 0b100,
    OP_LHU = 0b101
};

/*
 * Different types of stores (S-type), derived from bits [14:12] of instruction
 */
enum StoreCode_E {
    OP_SB = 0b000,
    OP_SH = 0b001,
    OP_SW = 0b010
};

/*
 * Different types of immediate (I-type) operations, derived from bits [14:12] of instruction
 */
enum ImmCode_E {
    OP_ADDI  = 0b000,
    OP_SLTI  = 0b010,
    OP_SLTIU = 0b011,
    OP_XORI  = 0b100,
    OP_ORI   = 0b110,
    OP_ANDI  = 0b111,
    OP_SLLI  = 0b001,
    OP_I_SR  = 0b101 // Can be arithmetic or logical
};

/*
 * Different types of shift right operations (I-type and R-type), derived from bits [31:25] of instruction
 */
enum ShiftRightCode_E {
    OP_LOGICAL    = 0,
    OP_ARITHMETIC = 0b0100000
};

/*
 * Different types of register (R-type) operations, derived from bits [14:12] of instruction
 */
enum RegCode_E {
    OP_ADD_SUB = 0,
    OP_SLL     = 0b001,
    OP_SLT     = 0b010,
    OP_SLTU    = 0b011,
    OP_XOR     = 0b100,
    OP_R_SR    = 0b101,
    OP_OR      = 0b110,
    OP_AND     = 0b111
};

/*
 * Differentiates add and sub R-type operations, derived from bits [31:25] of instruction
 */
enum AddSubCode_E {
    OP_ADD = 0,
    OP_SUB = 0b0100000
};

// }}}

/*** Helper Functions ***/

/*
 * Reads an assembled RISC-V file in and populates memory for future calls to `mem_read`
 */
int read_file(char *file) {
    // TODO
    return 0;
}

/*
 * Reads the instruction at the address specified by `PC`
 */
uint32_t mem_read(uint32_t PC) {
    if (PC % 4 != 0) {
        printf("Invalid Program Counter (%d), doesn't point to start of an instruction! Exiting...\n", PC);
    }
    // TODO
    return 0;
}

void branch_instr(uint8_t branch_type, uint32_t rs1_val, uint32_t rs2_val, uint32_t branch_target, uint32_t *PC) {

    bool take_branch = false;

    // Debug info, name of branch type
    char *branch_name;

    switch (branch_type) {
        case OP_BEQ:
            if (rs1_val == rs2_val) {
                take_branch = true;
            }
            if (debug) {
                branch_name = "BEQ";
            }
            break;
        case OP_BNE:
            if (rs1_val != rs2_val) {
                take_branch = true;
            }
            if (debug) {
                branch_name = "BNE";
            }
            break;
        case OP_BLT:
            if (((int32_t) rs1_val) < ((int32_t) rs2_val)) {
                take_branch = true;
            }
            if (debug) {
                branch_name = "BLT";
            }
            break;
        case OP_BGE:
            if (((int32_t) rs1_val) >= ((int32_t) rs2_val)) {
                take_branch = true;
            }
            if (debug) {
                branch_name = "BGE";
            }
            break;
        case OP_BLTU:
            if (rs1_val < rs2_val) {
                take_branch = true;
            }
            if (debug) {
                branch_name = "BLTU";
            }
            break;
        case OP_BGEU:
            if (rs1_val >= rs2_val) {
                take_branch = true;
            }
            if (debug) {
                branch_name = "BGEU";
            }
            break;
        default:
            printf("Unknown branch opcode (%d)! Exiting...\n", branch_type);
            exit(1);
            break;
    }

    // Check if we should take the branch & make sure PC pointer is non-null
    if (take_branch && PC) {
        *PC = branch_target;
    }

    if (debug) {
        if (take_branch) {
            printf("%s [true] branching to: %d\n", branch_name, branch_target);
        }
        else {
            printf("%s [false]\n", branch_name);
        }
    }
}

/*** Program Driver ***/

#define INITIAL_PC 0

int main(int argc, char **argv) {

    // Input file
    if (argc < 2) {
        printf("Usage: riscv-vm [asm-file] ...\n");
        exit(2);
    }

    for (int i = 1; i < argc; i++) {
        if (!read_file(argv[i])) {
            printf("Failed to load file: %s\n", argv[i]);
            exit(1);
        }
    }

    // Set up PC
    uint32_t PC = INITIAL_PC;

    // Main loop
    int running = 1;
    while (running) {
        uint32_t instr = mem_read(PC);
        PC += 4;
        // Extract op code (last seven bits)
        uint8_t opcode = instr & 0b01111111;

        switch (opcode) {
            case OP_LUI:
                // Extract immediate from instruction (upper 20 bits)
                uint32_t imm = instr & 0xFFFFF000;
                // Extract destination register
                int rd = (instr & 0xF80) >> 7;
                reg[rd] = imm;
                if (debug) printf("r[%d] := %d\n", rd, imm);
                break;
            case OP_AUIPC:
                // TODO
                break;
            case OP_JAL:
                // TODO
                break;
            case OP_JALR:
                // TODO
                break;
            case OP_BRANCH:
                // Extract information from instruction
                // Get source registers
                int rs1 = (instr & 0xF8000) >> 15;
                int rs2 = (instr & 0x1F00000) >> 20;
                // Get address to branch to
                // TODO
                uint32_t branch_target = 0;
                // Determine which type of branch instruction this is
                uint8_t branch_type = (instr & 0x7000) >> 12;

                branch_instr(branch_type, reg[rs1], reg[rs2], branch_target, &PC);
                break;
            case OP_LOAD:
                // TODO
                break;
            case OP_STORE:
                // TODO
                break;
            case OP_I_TYPE:
                // TODO
                break;
            case OP_R_TYPE:
                // TODO
                break;
            case OP_ECALL:
                // TODO
                break;
            default:
                // Unknown opcode
                printf("(PC = %d) Unkown OpCode. Exiting...\n", opcode);
                running = 0;
                break;
        }
    }
}


// vim:fdm=marker
