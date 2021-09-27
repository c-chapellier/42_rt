SRCS =	srcs/main.cpp \
		srcs/parser/Parser.cpp \
		srcs/objects/components/Point.cpp \
		srcs/objects/components/Vector.cpp \
		srcs/objects/Object.cpp \
		srcs/objects/Sphere.cpp \
		srcs/objects/Plane.cpp \

NAME = rt

FLAGS		= -Wall -Wextra -Werror

all :
			g++ ${FLAGS} -o ${NAME} ${SRCS} -lSDL2

clean :
			rm -f ${NAME}

re :		clean all