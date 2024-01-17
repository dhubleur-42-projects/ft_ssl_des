NAME		=	ft_ssl
TEST_NAME 	=	ft_ssl_test

SRCS		= 	\
				main.c \
				parser.c \
				utils.c \
				$(addprefix algorithms/, \
					pbkdf1.c \
					$(addprefix hash/, \
						runner.c \
						parser.c \
						printer.c \
						$(addprefix md5/, \
							md5_intern.c \
							md5_extern.c \
						) \
						$(addprefix sha256/, \
							sha256_intern.c \
							sha256_extern.c \
						) \
					) \
					$(addprefix cipher/, \
						$(addprefix basic/, \
							base64.c \
							parser.c \
							runner.c \
						) \
					) \
				)

TEST_SRCS	= 	\
				main.test.c \
				md5.test.c

_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix build/, $(_OBJS))
OBJS_DEPEND	=	${OBJS:.o=.d}

_TEST_OBJS		=	${TEST_SRCS:.c=.o}
TEST_OBJS		=	$(addprefix test_build/, $(_TEST_OBJS))
TEST_TO_LINK = $(filter-out build/main.o, $(OBJS)) $(TEST_OBJS)
TEST_LINK_ARG = -L /home/dhubleur/fake_bin/lib -lcheck -lm -lpthread -lrt

CC			=	clang
CFLAGS		=   -Wall -Wextra -Werror -g3
INCLUDE		=	-I includes/ -I libft

TEST_INCLUDE	=	$(INCLUDE) -I /home/dhubleur/fake_bin/include

LIBFT		=	libft/libft.a

exec: $(NAME)

test: $(TEST_NAME)

all		:	exec test

$(LIBFT): FORCE
	make -C libft

build/%.o	:	srcs/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${CFLAGS} -MMD -MF $(@:.o=.d) ${INCLUDE} -c $< -o $@

test_build/%.o	:	tests/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${TEST_INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

-include $(OBJS_DEPEND)

$(TEST_NAME)	:	$(TEST_TO_LINK) $(LIBFT)
	$(CC) ${TEST_LINK_ARG} $(TEST_TO_LINK) $(LIBFT) -o $(TEST_NAME)

clean	:	
	rm -Rf build/ test_build/


fclean	:	clean
	rm -f ${NAME} ${TEST_NAME}

fcleanlib: fclean
	make -C libft fclean

re		:	fclean
			make ${NAME}

relib	:	fcleanlib
			make ${NAME}

FORCE:

.PHONY	:	all clean fclean re FORCE fcleanlib relib exec test