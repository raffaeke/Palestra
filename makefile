CC = gcc
CFLAGS = -Wall -std=c11
TARGET = Palestra
SRC = main.c utils.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

run_TC1: TC1
	./TC1

TC1: TC1.c utils.c
	$(CC) $(CFLAGS) -o TC1 TC1.c utils.c

run_TC2: TC2
	./TC2

TC2: TC2.c utils.c
	$(CC) $(CFLAGS) -o TC2 TC2.c utils.c

run_TC3: TC3
	./TC3

TC3: TC3.c utils.c
	$(CC) $(CFLAGS) -o TC3 TC3.c utils.c