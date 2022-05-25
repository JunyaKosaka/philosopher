# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 16:31:12 by jkosaka           #+#    #+#              #
#    Updated: 2022/05/25 17:00:31 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

SRCROOT		:= src
SRCDIRS		:= $(shell find $(SRCROOT) -type d)
SRCS		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
# SRCS		:= 

OBJROOT		:= obj
OBJDIRS		:= $(patsubst $(SRCROOT)/%, $(OBJROOT)/%, $(SRCDIRS))
OBJS		:= $(patsubst $(SRCROOT)/%, $(OBJROOT)/%, $(SRCS:.c=.o))

DEPS		:= $(OBJS:.o=.d)

INCDIRS		:= includes
INCLUDE		:= $(addprefix -I, $(INCDIRS))

CC			:= cc -pthread
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP # -g -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

$(OBJROOT)/%.o: $(SRCROOT)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) -r $(OBJROOT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	norminette $(SRCROOT) $(INCDIRS)

test:
	make test1
	make test2
	make test3
	make test4
	make test5
	make solo

test1:
	make
	./$(NAME) 4 600 200 200 5

test2: # should die
	make
	./$(NAME) 4 310 200 100 3

test3:
	make
	./$(NAME) 10 410 200 100 5

test4:
	make
	./$(NAME) 200 420 200 200 10

test5:
	make
	./$(NAME) 5 800 200 200 7

solo: # should die
	make
	./$(NAME) 1 310 200 100 3

-include $(DEPS)

.PHONY: all clean fclean re norm test test1 test2 test3 test4 solo
