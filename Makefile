CC = gcc
CFLAGS = -Wall -Wextra -Wfatal-errors
NAME = Ultimate_TicTacToe
DISTDIR = dist

SRCS = main.c game.c global_grid.c local_grid.c ai.c tree.c players/c_files/alpha_beta.c players/c_files/minimax.c players/c_files/random.c
OBJS = $(SRCS:.c=.o)
HEADERS =  game.h global_grid.h local_grid.h ai.h tree.h players/headers/alpha_beta.h players/headers/minimax.h players/headers/random.h
DISTFILES = $(SRCS) $(HEADERS) Makefile 

.PHONY: all clean dist

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(NAME)
	rm -rf $(DISTDIR)

dist: clean
	mkdir -p $(DISTDIR)/$(NAME)
	cp --parents -R $(DISTFILES) $(DISTDIR)/$(NAME)
	tar -cvzf $(DISTDIR)/$(NAME).tar.gz -C $(DISTDIR) $(NAME)
	rm -rf $(DISTDIR)/$(NAME)