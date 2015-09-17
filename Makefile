main: main.c yaml.c deps/hash/hash.c
	$(CC) $^ $(CFLAGS) -std=c99 -o $@
	./main

clean:
	rm main
