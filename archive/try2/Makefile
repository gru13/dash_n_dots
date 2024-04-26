# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -lm

# Target executables
TARGETS = Game

# Output directory
OUT_DIR = out

# Source files
SRCS = main.c
# Object files
OBJS = $(SRCS:.c=.o)

# Default target: build all executables
all: $(addprefix $(OUT_DIR)/,$(TARGETS))

# Build executable with its dependencies and place it in the output directory
$(OUT_DIR)/$(TARGETS): $(addprefix $(OUT_DIR)/,$(OBJS))
	$(CC) $^ -o $@ -lncurses -lm

# Rule to build object files
$(OUT_DIR)/%.o: %.c dash_n_dots.h
	$(CC) $(CFLAGS) -c $< -o $@

# Target for running the executable
run: $(OUT_DIR)/$(TARGETS)
	$(OUT_DIR)/$(TARGETS)

# Clean up target (removes executables and object files from the output directory)
clean:
	@echo Cleaning up...
	@if exist $(OUT_DIR) (rmdir /s /q $(OUT_DIR)) else (echo $(OUT_DIR) does not exist.)
	@mkdir $(OUT_DIR)

# Phony targets
.PHONY: all run clean
