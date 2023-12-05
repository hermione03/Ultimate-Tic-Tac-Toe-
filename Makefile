CC = gcc
CFLAGS = -Wall -Wextra -Wfatal-errors
NAME = Ultimate_TicTacToe
DISTDIR = dist

SRCS = Local_grid.c Global_grid.c GAME.c AI.c main.c
OBJS = $(SRCS:.c=.o)
HEADERS =  Local_grid.h Global_grid.h GAME.h AI.h
DISTFILES = $(SRCS) $(HEADERS) Makefile 

.PHONY: all clean dist

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(NAME)

dist: clean
	mkdir -p $(DISTDIR)/$(NAME)
	cp -R $(DISTFILES) $(DISTDIR)/$(NAME)
	tar -cvzf $(DISTDIR)/$(NAME).tar.gz -C $(DISTDIR) $(NAME)
	rm -rf $(DISTDIR)/$(NAME)