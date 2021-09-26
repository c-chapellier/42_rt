SRCS =	srcs/main.cpp \
		srcs/parser/Parser.cpp \
		srcs/objects/Object.cpp \

NAME = rt

CFLAGS		= -Wall -Wextra -Werror

all :
			g++ -o ${NAME} ${SRCS}

clean :
			rm -f ${NAME}

re :		clean all