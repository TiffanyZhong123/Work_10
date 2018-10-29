all: main.c
	gcc main.c
run:
	./a.out
clean:
	rm out
	rm *.o
