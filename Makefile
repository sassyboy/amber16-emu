all: amber16
	@echo "Done!"

amber16: main.o libamber16.a
	gcc -o $@ $^

libamber16.a: alu.o cu.o regfile.o mem.o
	ar rs $@ $^
%.o: %.c
	gcc -c -o $@ $^

clean:
	rm -rf *.o amber16 libamber16.a
	
