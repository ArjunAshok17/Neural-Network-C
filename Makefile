CC = gcc
CFLAGS = -g -Wall -Werror -c
OBJ: main.o propagation.o neural_network.o user_interaction.o

neural_network.out: $(OBJ)
	$(CC) -g -Wall -Werror $(OBJ) -o neural_network.out

main.o: main.c
	$(CC) $(CFLAGS) main.c

propagation.o: propagation.c propagation.h
	$(CC) $(CFLAGS) propagation.c

neural_network.o: neural_network.c neural_network.h
	$(CC) $(CFLAGS) neural_network.c

user_interaction.o: user_interaction.c user_interaction.h
	$(CC) $(CFLAGS) user_interaction.c

clean:
	rm -fr *.o *.out