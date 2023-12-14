CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = src
MODULES_DIR = modules
COMMON_DIR = common
HEADERS_DIR = headers

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(MODULES_DIR)/*.c) $(wildcard $(COMMON_DIR)/*.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRC_FILES))
HEADER_FILES = $(wildcard $(HEADERS_DIR)/*.h)

TARGET = inventory

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(TARGET)