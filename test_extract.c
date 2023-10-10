/*
 * Testing suite for `extract.h` and `extract.c` files
 */

#include <assert.h>

#include "extract.h"

void test_opcode(void) {
    assert(get_opcode(0xAAAAADB7) == 0x37);
}

void test_rd(void) {
    assert(get_rd(0xAAAAADB7) == 0x1B);
}

void test_rs1(void) {
    // TODO
}

void test_rs2(void) {
    // TODO
}

void test_funct3(void) {
    // TODO
}

void test_funct7(void) {
    // TODO
}

void test_i_imm(void) {
    // TODO
}

void test_s_imm(void) {
    // TODO
}

void test_b_imm(void) {
    // TODO
}

void test_u_imm(void) {
    // TODO
}

void test_j_imm(void) {
    // TODO
}

int main(void) {
    test_opcode();

    test_rd();
    test_rs1();
    test_rs2();

    test_funct3();
    test_funct7();

    test_i_imm();
    test_s_imm();
    test_b_imm();
    test_u_imm();
    test_j_imm();

    return 0;
}
