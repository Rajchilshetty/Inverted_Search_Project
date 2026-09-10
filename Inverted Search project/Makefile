OBJ := $(patsubst %.c, %.o, $(wildcard *.c))
raj.out: $(OBJ)
	gcc -o $@ $^
clean:
	rm *.out *.o