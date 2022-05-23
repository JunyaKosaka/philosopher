# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 16:31:12 by jkosaka           #+#    #+#              #
#    Updated: 2022/05/23 13:09:46 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

SRCROOT		:= src
SRCDIRS		:= $(shell find $(SRCROOT) -type d)
# SRCS		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
SRCS		:= src/philosopher/action.c src/philosopher/fork.c src/philosopher/launcher.c src/philosopher/philo.c src/philosopher/print_log.c src/utils/error_handler.c src/utils/free.c src/utils/ft_num.c src/utils/ft_str.c src/utils/get_milliseconds.c src/main/main.c

OBJROOT		:= obj
OBJDIRS		:= $(patsubst $(SRCROOT)/%, $(OBJROOT)/%, $(SRCDIRS))
OBJS		:= $(patsubst $(SRCROOT)/%, $(OBJROOT)/%, $(SRCS:.c=.o))

DEPS		:= $(OBJS:.o=.d)

INCDIRS		:= includes
INCLUDE		:= $(addprefix -I, $(INCDIRS))

CC			:= cc -pthread
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP # -fsanitize=address

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
# make test4
	make solo

test1:
	make
	./$(NAME) 4 600 200 200 5

test2:
	make
	./$(NAME) 4 310 200 100 3

test3:
	make
	./$(NAME) 10 410 200 100 5

test4:
	make
	./$(NAME) 3 800 200 200 10

solo:
	make
	./$(NAME) 1 310 200 100 3

-include $(DEPS)

.PHONY: all clean fclean re norm test test1 test2 test3 solo
