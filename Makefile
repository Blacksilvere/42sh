NAME	= 42sh

CC	= gcc

RM	= rm -f

SRCS	=	src/main.c		\
			src/mini2.c		\
			src/mini3.c		\
			src/mini4.c		\
			src/mini5.c		\
			src/mini6.c		\
		src/getline.c		\
		src/str_to_word_array.c		\
		src/str_to_word_token.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I
CFLAGS += -Wall -Wextra -g3

all: $(NAME)

$(NAME): $(OBJS)
	 make re -C lib/my
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -L./lib -lmy -g3

clean:
	make clean -C lib/my
	$(RM) $(OBJS)
	$(RM) lib/libmy.a

fclean: clean
	make fclean -C lib/my
	$(RM) $(NAME)
	cd lib/my/; make fclean

re: fclean all

.PHONY: all clean fclean re
