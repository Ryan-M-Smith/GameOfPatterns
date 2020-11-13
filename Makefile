# The Makefile for GameOfPatterns

CC = g++
CFLAGS = -Wall

TARGET = gameofpatterns
SOURCE = main
INSTALL_LOC = /usr/bin

USER := $(shell whoami)

# Some aliases and defaults
default: $(TARGET)
all: $(TARGET)
uninstall: clean

# `make`
$(TARGET): src/$(SOURCE).cpp
	$(CC) $(CFLAGS) -o $(TARGET) src/$(SOURCE).cpp

# `make clean`
clean:
	sudo $(RM) --verbose $(TARGET) $(INSTALL_LOC)/$(TARGET)

# `make install`
install:
	sudo install --verbose --owner $(USER) $(TARGET) --target-directory $(INSTALL_LOC)
