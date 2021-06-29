# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 09:56:55 by mchardin          #+#    #+#              #
#    Updated: 2021/06/24 22:11:23 by syndraum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX		=	./

SRCS		=	$(addprefix $(PREFIX), \
								Server.cpp \
								ServerSocket.cpp \
								ClientSocket.cpp \
								Core.cpp \
								Response.cpp \
								Reader.cpp \
								main_to_test_request.cpp \
								Request.cpp \
								BuilderRequest.cpp \
								AMethod.cpp \
								MethodGet.cpp \
								MethodDelete.cpp \
								)

OBJS		=	${SRCS:.cpp=.o}

DEPS		=	${OBJS:.o=.d}

CXX			=	clang++

CXXFLAGS	=	-Werror -Wextra -Wall -MMD

NAME 		=	webserv

RM			=	rm -f

all:
			${MAKE} ${NAME}

${NAME}:	${OBJS}
			${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

run:		all
			./$(NAME)

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
