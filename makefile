all:
	gcc -o work13 work13.c
clean:
	rm *~
run: work13
	./work13
