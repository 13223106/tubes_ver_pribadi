# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
DATA_DIR = data

# Files
SRCS = main.c \
       $(SRC_DIR)/file_handling.c \
       $(SRC_DIR)/memory_handling.c \
       $(SRC_DIR)/utility.c \
       $(SRC_DIR)/showSchedule.c \
       $(SRC_DIR)/penjadwalan.c

OBJS = main.o \
       $(OBJ_DIR)/file_handling.o \
       $(OBJ_DIR)/memory_handling.o \
       $(OBJ_DIR)/utility.o \
       $(OBJ_DIR)/showSchedule.o \
       $(OBJ_DIR)/penjadwalan.o

HEADERS = $(SRC_DIR)/data.h \
          $(SRC_DIR)/file_handling.h \
          $(SRC_DIR)/memory_handling.h \
          $(SRC_DIR)/utility.h \
          $(SRC_DIR)/showSchedule.h \
          $(SRC_DIR)/penjadwalan.h

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c -o main.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) *.o $(TARGET)
