# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 09:56:55 by mchardin          #+#    #+#              #
#    Updated: 2021/11/19 22:30:48 by mchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX			=	./srcs/

SRCS_METHOD		=	$(addprefix $(PREFIX)methods/, \
					AMethod.cpp \
					MethodDelete.cpp \
					MethodGet.cpp \
					MethodPost.cpp \
					MethodLibrary.cpp \
					)

SRCS_UTILS		=	$(addprefix $(PREFIX)utils/, \
					Info.cpp \
					StringPP.cpp \
					Array.cpp \
					)

SRCS_REQUEST	=	$(addprefix $(PREFIX)request/, \
					Request.cpp \
					BuilderRequest.cpp \
					HandlerRequest.cpp \
					URI.cpp \
					)

SRCS_RESPONSE	=	$(addprefix $(PREFIX)response/, \
					Response.cpp \
					HandlerResponse.cpp \
					)

SRCS_CGI		=	$(addprefix $(PREFIX)cgi/, \
					CGI.cpp \
					RequestCGI.cpp \
					HandlerResponseCGI.cpp \
					Pipe.cpp \
					)

SRCS_CORE		=	$(addprefix $(PREFIX)core/, \
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
					Redirection.cpp \
					)

SRCS_READER		=	$(addprefix $(PREFIX)reader/, \
					Reader.cpp \
					Extension.cpp \
					CsvReader.cpp \
					AReaderFileDescriptor.cpp \
					ReaderFileDescriptor.cpp \
					ReaderSocket.cpp \
					Upload.cpp \
					)

SRCS_STRATEGY	=	$(addprefix $(PREFIX)strategy/, \
					IResponseStrategy.cpp \
					StrategyAccept.cpp \
					StrategyError.cpp \
					StrategyIndex.cpp \
					StrategyCGI.cpp \
					StrategyReturn.cpp \
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

INCLUDE_DIR		=	./includes

INCLUDE_FLAG	=	-I$(INCLUDE_DIR)/methods \
					-I$(INCLUDE_DIR)/utils \
					-I$(INCLUDE_DIR)/request \
					-I$(INCLUDE_DIR)/response \
					-I$(INCLUDE_DIR)/cgi \
					-I$(INCLUDE_DIR)/core \
					-I$(INCLUDE_DIR)/reader \
					-I$(INCLUDE_DIR)/strategy

OBJS			=	${SRCS:.cpp=.o}

DEPS			=	${OBJS:.o=.d}

CXX				=	clang++

CXXFLAGS		=	-Werror -Wextra -Wall -MMD -std=c++98 -g $(INCLUDE_FLAG)

NAME 			=	webserv

RM				=	rm -f

all:
				${MAKE} ${NAME}

${NAME}:		${OBJS}
				${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

run:			all
				./$(NAME)

vg:				all
				valgrind ./$(NAME)

vgf:			all
				valgrind --leak-check=full ./$(NAME)

vga:			all
				valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

clean:
				${RM} ${OBJS}
				${RM} ${DEPS}

fclean:
				${RM} ${OBJS}
				${RM} ${DEPS}
				${RM} ${NAME}

re:				fclean all

test:			all
				./$(NAME)

valgrind:		all
				valgrind ./$(NAME)

.PHONY: 		all re run clean fclean vg vgf vga test

-include		${DEPS}
