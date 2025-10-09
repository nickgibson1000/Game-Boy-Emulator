CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
BIN_DIR = bin

all: $(BIN_DIR)/main $(BIN_DIR)/boot

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/main: main.c boot.c | $(BIN_DIR)
	$(CC) $(CFLAGS) main.c boot.c -o $(BIN_DIR)/main

$(BIN_DIR)/boot: boot.c | $(BIN_DIR)
	$(CC) $(CFLAGS) boot.c -o $(BIN_DIR)/boot

clean:
	rm -f $(BIN_DIR)/main $(BIN_DIR)/boot
	rm -rf $(BIN_DIR)