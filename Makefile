# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 16:31:12 by jkosaka           #+#    #+#              #
#    Updated: 2022/05/29 00:40:56 by jkosaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

SRCROOT		:= src
SRCDIRS		:= $(shell find $(SRCROOT) -type d)
# SRCS		:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
SRCS		:= src/philosopher/action.c src/philosopher/deinit.c src/philosopher/fork.c src/philosopher/launcher.c src/philosopher/monitor.c src/philosopher/philo.c src/philosopher/print_log.c src/philosopher/solo_philo.c src/utils/error_handler.c src/utils/free.c src/utils/ft_num.c src/utils/ft_str.c src/utils/get_milliseconds.c src/main/main.c

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

atest:
	for i in `seq 1 2`; do make test; done | grep "died" | wc

test:
	make test1
	make test2
	make test3
	make test4
	make test5
	make test6
	make solo

test1:
	make
	./$(NAME) 4 410 200 200 5

test2:
	make
	./$(NAME) 4 310 200 100 3

test3:
	make
	./$(NAME) 10 410 200 100 5

test4:
	make
	./$(NAME) 200 430 200 200 5

test5:
	make
	./$(NAME) 5 520 200 200 5

test6:
	make
	./$(NAME) 199 420 200 200 4

solo:
	make
	./$(NAME) 1 310 200 100 3

-include $(DEPS)

.PHONY: all clean fclean re norm atest test test1 test2 test3 test4 test5 test6 solo
