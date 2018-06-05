# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adzikovs <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 10:39:10 by adzikovs          #+#    #+#              #
#    Updated: 2018/01/20 15:29:11 by adzikovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SDIR = srcs
SRCS = ft_bzero.c\
		ft_memcpy.c\
		page_list.c\
		page_list_del.c\
		block_list.c\
		block_list_del.c\
		block_list_push.c\
		block_list_change.c\
		allocate.c\
		page_functions.c\
		block_data_functions.c\
		init.c\
		enlarge_free_block.c\
		change_free_list.c\
		malloc.c\
		free.c\
		check_last_reg_entry.c\
		realloc_enlarge.c\
		realloc_truncate.c\
		realloc.c\
		show_alloc_mem.c\

INC = Includes

ODIR = objects
OBJ = $(SRCS:.c=.o)

OUTFILES = random reg00 reg01 reg02 reg03 reg04 test small tiny
OUTFILES2 = reg00 reg01 tiny small

all : $(ODIR)/ $(NAME)

$(NAME) : $(OBJ:%.o=$(ODIR)/%.o)
	ar rc $(NAME) $(OBJ:%.o=$(ODIR)/%.o)
	make DST="../$(NAME)" add -C libft/
	ln -Ffs $(NAME) libft_malloc.so

debug : $(SRCS:%.c=$(SDIR)/%.c) dep
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS:%.c=$(SDIR)/%.c) $(LIBS) -I $(INC)

test : oclean $(NAME)
	./$(NAME)

drun: debug
	lldb ./$(NAME)

clean:
	rm -f $(OBJ:%.o=$(ODIR)/%.o)

oclean:
	rm -Rf $(OUTFILES)
	rm -Rf $(OUTFILES2)

fclean : clean
	make fclean -C libft/
	rm -f $(NAME)
	rm -f libft_malloc.so

dclean :
	rm -f $(NAME)
	rm -Rf $(NAME).dSYM

re : fclean all

.PHONY: tell

tell:
	echo $(LIB_OBJECTS)

$(ODIR)/ :
	mkdir -p $@

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)
