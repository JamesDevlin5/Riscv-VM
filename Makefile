CC := gcc
PROG := riscv-vm

$(PROG): vm.c
	$(CC) -Wall -o $@ $^

clean:
	$(RM) $(PROG)

.PHONY: clean
