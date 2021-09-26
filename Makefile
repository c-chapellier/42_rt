SRCS =	srcs/main.cpp \
		srcs/parser/Parser.cpp \
		srcs/objects/Object.cpp \

OBJS = ${SRCS:.cpp=.o}

NAME = rt

CFLAGS		= -Wall -Wextra -Werror

all :		${NAME}

${NAME} :	${OBJS}
			g++ -o ${NAME} ${OBJS}

clean :
			rm -f ${OBJS}

fclean :	clean
			rm -f ${NAME}

re :		fclean all