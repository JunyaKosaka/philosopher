# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 16:31:12 by jkosaka           #+#    #+#              #
#    Updated: 2022/04/19 19:59:45 by jkosaka          ###   ########.fr        #
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

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP
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
	make
#		num_of_phils die eat sleep
	./$(NAME) 2 2000 3000 2000

-include $(DEPS)

.PHONY: all clean fclean re test

echo:
	echo $(SRCS) >> Makefile
