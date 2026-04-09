cc = gcc
CFLAGS = -g -Wall
TARGET = main
OBJS = $(SRCS:.c=.o)
SRCS = main.c Sequence.c Grid.c 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -lm

clean:
	rm -f $(TARGET) $(OBJS)
