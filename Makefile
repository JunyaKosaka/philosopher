# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 16:31:12 by jkosaka           #+#    #+#              #
#    Updated: 2022/05/22 16:12:09 by jkosaka          ###   ########.fr        #
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

CC			:= cc -g -O0 -pthread
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP # -fsanitize=address
# LFLAGS		:= -L$(LIBFTDIR) -lft -L$(READLINEDIR)/lib -lreadline -lhistory

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

test:
	make test1
	make test2
	make solo

test1:
	make
#		num_of_phils die eat sleep (number_of_times_each_philosopher_must_eat)
	./$(NAME) 4 600 200 200 5

test2:
	make
	./$(NAME) 4 310 200 100 3

solo:
	make
	./$(NAME) 1 310 200 100 3


-include $(DEPS)

.PHONY: all clean fclean re test test2 solo

echo:
	echo $(SRCS) >> Makefile
