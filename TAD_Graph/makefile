CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = programa
OBJ = main.o graph.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c graph.h
	$(CC) $(CFLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./$(TARGET)