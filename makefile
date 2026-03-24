cc = gcc
CFLAGS = -g -Wall
TARGET = main
OBJS = $(SRCS:.c=.o)
SRCS = main.c 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
