all: p_thread

clean: 
	rm -f p_threads

p_thread: p_threads.c
	gcc -Wall -g -pthread -o p_threads p_threads.c
