TARGET = programm
CC = gcc

SRC = $(wildcard *.c)

$(TARGET) : $(SRC)
	$(CC) -g $(SRC) -o $(TARGET) -pthread -lpthread

clean :
	rm $(TARGET)