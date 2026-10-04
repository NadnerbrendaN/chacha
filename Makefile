chacha : main.o chacha.o
	cc main.o chacha.o -o chacha

main.o : src/main.c src/chacha.h
	cc -c src/main.c -o main.o

chacha.o : src/chacha.c src/chacha.h
	cc -c src/chacha.c -o chacha.o

debug : main-debug.o chacha-debug.o
	cc main-debug.o chacha-debug.o -o debug -fsanitize=address,undefined

main-debug.o : src/main.c src/chacha.h
	cc -c src/main.c -o main-debug.o -Wall -Wextra -Wpedantic -fsanitize=address,undefined

chacha-debug.o : src/chacha.c src/chacha.h
	cc -c src/chacha.c -o chacha-debug.o -Wall -Wextra -Wpedantic -fsanitize=address,undefined

clean :
	rm -f main.o chacha.o chacha main-debug.o chacha-debug.o debug
