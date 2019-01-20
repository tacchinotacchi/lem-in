SRCS =
INCLUDES = libft/includes/libft.h \
		ft_printf/includes/ft_printf.h
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))

TESTS_SRCS =
TESTS = $(patsubst %.c,tests/%.test,$(TESTS_SRCS))
TESTS_DBG_FOLDERS = $(TESTS:.test=.test.dSYM)

CC = gcc
ifndef CFLAGS_WARNINGS
export CFLAGS_WARNINGS = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror -std=c89
endif
INCLUDE_FOLDERS = -Iincludes/ -Ilibft/includes -Ift_printf/includes
LIBRARY_PATHS = -L. -Llibft -Lft_printf
NAME = lem-in

.PHONY: clean fclean re all

all: $(NAME) $(TESTS)

LIBFT_PREFIX = ../libft
FTPRINTF_PREFIX = ft_printf
include ft_printf/Makefile.mk
LIBFT_PREFIX = libft
include libft/Makefile.mk

$(GENERATOR): $(OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) -o $@ $(LIBRARY_PATHS) -lftprintf -lft

$(CHECKER): $(OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) -o $@ $(LIBRARY_PATHS) -lftprintf -lft

obj:
	mkdir -p obj

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -o $@ -c $<

tests/%.test: tests/%.c $(NAME) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATHS) -o $@ $< -lft

clean:
	rm -rf $(TESTS_DBG_FOLDERS)
	rm -f $(TESTS)
	rm -f $(OBJS)
	rm -rf obj
	rm -f $(LIBFT_OBJS)
	rm -rf libft/obj
	rm -f $(FTPRINTF_OBJS)
	rm -rf ft_printf/obj

fclean: clean
	rm -f $(LIBFT_NAME)
	rm -f $(FTPRINTF_NAME)
	rm -f $(NAME)

re: fclean
	$(MAKE) all
