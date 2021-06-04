NAME		= a.out

SRCS		= \
			  main.c \

HEADER		= \

RM			= rm -f

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -pthread

OBJS		=	$(SRCS:.c=.o)

.c.o:
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME):	$(SRCS) $(OBJS) $(HEADER)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I.

clean:
			$(RM) -r $(OBJS)

fclean:		clean
			$(RM) -r $(NAME)

re:			fclean all


config:
	git config --global user.email "cdai@student.42.fr";
	git config --global user.name "cdai";
	git clone https://github.com/42paris/42header;
	mkdir -p ~/.vim/plugin;
	sed 's/marvin/cdai/' 42header/vim/stdheader.vim | sed 's/42.fr/student.42.fr/' > ~/.vim/plugin/stdheader.vim;
	git config --global core.editor vim;
	rm -rf 42header;
	echo '*.log' > .gitignore
	echo '.*.swp' >> .gitignore
	echo .gitignore >> .gitignore
	echo test >> .gitignore
	echo '*.o' >> .gitignore

test: all
	./$(NAME)


valgrind: all
	valgrind ./$(NAME)

norm:
	norminette $(SRCS) $(HEADER)

