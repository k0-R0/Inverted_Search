CC = gcc
CFLAGS = -Wall -g -Isrc
LDFLAGS = 

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/inverted_index

# Default rule
all: $(TARGET)

# Link the binary
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Create directories if they don't exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
