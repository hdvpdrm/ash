# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -lncurses

# Source files
SRCS = main.c interface.c command_invoker.c util.c state.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HDRS = defs.h interface.h command_invoker.h util.h state.h

# Executable name
TARGET = ash

# Default rule
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilation rule
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $<

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
