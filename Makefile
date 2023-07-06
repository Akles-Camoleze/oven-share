CC = gcc
TARGET = oven-share
SRC = $(wildcard *.c) ADTs/list/list.c\
entities/student/student.c\
enums/level/level.enum.c\
services/services.c\
main.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)