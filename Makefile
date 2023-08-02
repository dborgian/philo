# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 15:00:37 by dborgian          #+#    #+#              #
#    Updated: 2023/08/02 13:06:01 by dborgian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

MAKEFLAGS += --silent

SRC = main.c \
	  init.c \
	  general_utils.c \
	  philo_utils.c \
	  routine.c \

OBJ = ${SRC:.c=.o}

CC = gcc -g

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g -pthread

.o:.c
		${CC} ${CFLAGS} -c $< -o $@

all: ${NAME} 

${NAME}: ${OBJ} 
		${CC} ${OBJ} -o ${NAME} -pthread

		

clean:
		${RM} ${OBJ}
		
		
fclean: clean
		${RM} ${NAME}

re: fclean all
		
