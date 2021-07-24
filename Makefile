# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 09:56:55 by mchardin          #+#    #+#              #
#    Updated: 2021/07/19 16:54:33 by roalvare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX		=	./srcs/

SRCS_METHOD		= $(addprefix $(PREFIX)methods/, \
								AMethod.cpp \
								MethodDelete.cpp \
								MethodGet.cpp \
								MethodLibrary.cpp \
								)

SRCS_UTILS		= $(addprefix $(PREFIX)utils/, \
								Info.cpp \
								StringPP.cpp \
								)

SRCS_REQUEST	= $(addprefix $(PREFIX)request/, \
								Request.cpp \
								BuilderRequest.cpp \
								HandlerRequest.cpp \
								URI.cpp \
								)

SRCS_RESPONSE	= $(addprefix $(PREFIX)response/, \
								Response.cpp \
								HandlerResponse.cpp \
								)

SRCS_CGI		= $(addprefix $(PREFIX)cgi/, \
								CGI.cpp \
								RequestCGI.cpp \
								)

SRCS_CORE		= $(addprefix $(PREFIX)core/, \
								Core.cpp \
								BuilderCore.cpp \
								Server.cpp \
								ASocket.cpp \
								ServerSocket.cpp \
								ClientSocket.cpp \
								Client.cpp \
								Message.cpp \
								HandlerPollFD.cpp \
								BuilderMessage.cpp \
								)

SRCS_READER		= $(addprefix $(PREFIX)reader/, \
								Reader.cpp \
								Extension.cpp \
								CsvReader.cpp \
								)

SRCS_STRATEGY	= $(addprefix $(PREFIX)strategy/, \
								StrategyAccept.cpp \
								StrategyError.cpp \
								StrategyIndex.cpp \
								StrategyCGI.cpp \
								)

SRCS			=	$(SRCS_METHOD) \
					$(SRCS_UTILS) \
					$(SRCS_REQUEST) \
					$(SRCS_RESPONSE) \
					$(SRCS_CGI) \
					$(SRCS_CORE) \
					$(SRCS_READER) \
					$(SRCS_STRATEGY) \
					$(addprefix $(PREFIX), \
								main.cpp \
								)

INCLUDE_DIR = ./includes

INCLUDE_FLAG	=	-I$(INCLUDE_DIR)/methods \
					-I$(INCLUDE_DIR)/utils \
					-I$(INCLUDE_DIR)/request \
					-I$(INCLUDE_DIR)/response \
					-I$(INCLUDE_DIR)/cgi \
					-I$(INCLUDE_DIR)/core \
					-I$(INCLUDE_DIR)/reader \
					-I$(INCLUDE_DIR)/strategy

OBJS		=	${SRCS:.cpp=.o}

DEPS		=	${OBJS:.o=.d}

CXX			=	clang++

CXXFLAGS	=	-Werror -Wextra -Wall -MMD -std=c++98 -g $(INCLUDE_FLAG)

NAME 		=	webserv

RM			=	rm -f

all:
			${MAKE} ${NAME}

${NAME}:	${OBJS}
			${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

run:		all
			./$(NAME)

vg:	all
			valgrind ./$(NAME)

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

valgrind:	all
			valgrind $(PREFIX)$(NAME)

.PHONY: 	all re run clean fclean

-include	${DEPS}
