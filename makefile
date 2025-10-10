CC = gcc
CFLAGS = -g #-Wall -Wextra -Werror
BIN_DIR = bin

all: $(BIN_DIR)/main

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/main: src/main.c src/cpu.c src/audio.c src/cartridge.c | $(BIN_DIR)
	$(CC) $(CFLAGS) src/main.c src/cpu.c src/audio.c src/cartridge.c -o $(BIN_DIR)/main

clean:
	rm -f $(BIN_DIR)/main
	rm -rf $(BIN_DIR)