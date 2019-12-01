.PHONY: default
default: main util

ex1: ex1.c
	mpicc -lm -o main main.c

ex2: ex2.c
	mpicc -lm -o util util.c

.PHONY: clean
clean:
	-rm util
	-rm main
