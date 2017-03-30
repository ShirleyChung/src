include ../environment

CC=g++

SHARE_CLASS=../shareclass

TARGET=daemon

all: $(TARGET)

daemon: test.cpp
	$(CC) -o $@ test.cpp $(SHARE_CLASS)/daemon.cpp

clean:
	rm $(TARGET)
