CC = gcc
CFLAGS = -Wall -Wextra
TARGET = ip_router

all: $(TARGET)

$(TARGET): main.o ip_router.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o ip_router.o

main.o: main.c ip_router.h
	$(CC) $(CFLAGS) -c main.c

ip_router.o: ip_router.c ip_router.h
	$(CC) $(CFLAGS) -c ip_router.c

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
