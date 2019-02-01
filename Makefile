SRCS = parser/parser.c \
	parser/get_info.c \
	parser/get_info2.c \
	parser/check_func1.c \
	parser/check_func2.c \
	parser/check_util.c \
	adjacency_list/adjacency_list.c \
	adjacency_list/node_util.c \
	adjacency_list/edge_util.c \
	priority_queue/priority_queue.c \
	algorithm/algorithm_util.c \
	algorithm/transform_graph.c \
	algorithm/path.c \
	algorithm/max_flow.c \
	algorithm/program.c \
	error.c \
	lem-in.c
INCLUDES = libft/includes/libft.h \
		ft_printf/includes/ft_printf.h \
		includes/adjacency_list.h \
		includes/algorithm.h \
		includes/lem-in.h \
		includes/parser.h \
		includes/priority_queue.h \
		includes/visualizer.h
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))
VISUALIZER_SRCS = visualizer/drawing.c \
	visualizer/init_context.c \
	visualizer/init_shaders.c \
	visualizer/init_textures.c \
	visualizer/matrix.c \
	visualizer/visualizer.c \
	visualizer/math.c \
	algorithm/algorithm_util.c \
	parser/parser.c \
	parser/get_info.c \
	parser/get_info2.c \
	parser/check_func1.c \
	parser/check_func2.c \
	parser/check_util.c \
	adjacency_list/adjacency_list.c \
	adjacency_list/node_util.c \
	adjacency_list/edge_util.c \
	error.c
VISUALIZER_OBJS = $(patsubst %.c,obj/%.o,$(VISUALIZER_SRCS))

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
VISUALIZER = visualizer

.PHONY: clean fclean re all

all: $(NAME) $(TESTS) $(VISUALIZER)

LIBFT_PREFIX = ../libft
FTPRINTF_PREFIX = ft_printf
include ft_printf/Makefile.mk
LIBFT_PREFIX = libft
include libft/Makefile.mk

$(VISUALIZER): $(VISUALIZER_OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(VISUALIZER_OBJS) -o $@ $(LIBRARY_PATHS) -lftprintf -lft `pkg-config --libs glew sdl2` -framework OpenGL

$(NAME): $(OBJS) $(LIBFT_NAME) $(FTPRINTF_NAME)
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) -o $@ $(LIBRARY_PATHS) -lftprintf -lft

obj:
	mkdir -p obj
	mkdir -p obj/parser
	mkdir -p obj/adjacency_list
	mkdir -p obj/visualizer
	mkdir -p obj/priority_queue
	mkdir -p obj/algorithm

obj/visualizer/%.o: src/visualizer/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) `pkg-config --cflags glew sdl2` $(INCLUDE_FOLDERS) -o $@ -c $<

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -o $@ -c $<

tests/%.test: tests/%.c $(NAME) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATHS) -o $@ $< -lft

clean:
	rm -rf $(TESTS_DBG_FOLDERS)
	rm -f $(TESTS)
	rm -f $(OBJS)
	rm -f $(VISUALIZER_OBJS)
	rm -rf obj
	rm -f $(LIBFT_OBJS)
	rm -rf libft/obj
	rm -f $(FTPRINTF_OBJS)
	rm -rf ft_printf/obj

fclean: clean
	rm -f $(LIBFT_NAME)
	rm -f $(FTPRINTF_NAME)
	rm -f $(VISUALIZER)
	rm -f $(NAME)

re: fclean
	$(MAKE) all
