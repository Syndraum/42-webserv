# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 09:56:55 by mchardin          #+#    #+#              #
#    Updated: 2021/06/30 18:32:13 by mchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX		=	./

SRCS		=	$(addprefix $(PREFIX), \
								main.cpp \
								Server.cpp \
								ASocket.cpp \
								DevSocket.cpp \
								ServerSocket.cpp \
								ClientSocket.cpp \
								Core.cpp \
								Response.cpp \
								Reader.cpp \
								Request.cpp \
								BuilderRequest.cpp \
								BuilderCore.cpp \
								AMethod.cpp \
								MethodGet.cpp \
								MethodDelete.cpp \
								MethodLibrary.cpp \
								)

OBJS		=	${SRCS:.cpp=.o}

DEPS		=	${OBJS:.o=.d}

CXX			=	clang++

CXXFLAGS	=	-Werror -Wextra -Wall -MMD -std=c++98

NAME 		=	webserv

RM			=	rm -f

all:
			${MAKE} ${NAME}

${NAME}:	${OBJS}
			${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

run:		all
			cat test.conf | ./$(NAME)

clean:
			${RM} ${OBJS}
			${RM} ${DEPS}

fclean:
			${RM} ${OBJS}
			${RM} ${DEPS}
			${RM} ${NAME}

re:			fclean all

test:		all
			$(PREFIX)$(NAME)

.PHONY: 	all re run clean fclean

-include	${DEPS}
