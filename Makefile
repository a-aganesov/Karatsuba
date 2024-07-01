CC = g++
CFLAGS = -Wall -std=c++11
TARGET = karatsuba

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).cpp
	$(CC) $(CFLAGS) -c $(TARGET).cpp
	
deps:
	sudo apt-get update
	sudo apt-get install build-essential


clean:
	rm -f $(TARGET) $(TARGET).o

