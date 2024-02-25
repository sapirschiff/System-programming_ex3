CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99

SRCS = Main.c StrList.c
OBJS = $(SRCS:.c=.o)

TARGET = StrList

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
