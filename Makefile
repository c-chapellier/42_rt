SRCS =	srcs/main.cpp \
		srcs/window/Window.cpp \
		srcs/pixel/Pixel.cpp \
		srcs/image/Image.cpp \
		srcs/parser/Parser.cpp \
		srcs/visuals/Camera.cpp \
		srcs/color/Color.cpp \
		srcs/objects/components/Point.cpp \
		srcs/objects/components/Vector.cpp \
		srcs/objects/Object.cpp \
		srcs/objects/Sphere.cpp \
		srcs/objects/Plane.cpp \
		srcs/objects/Cylinder.cpp \
		srcs/objects/MobiusTape.cpp \
		srcs/objects/Line.cpp \
		srcs/objects/Quadratic.cpp \
		srcs/headers/define.cpp \

NAME = rt

FLAGS		= -Wall -Wextra -Werror

all :
			g++ ${FLAGS} -o ${NAME} ${SRCS} -lSDL2

run :		all
			./${NAME}

clean :
			rm -f ${NAME}

re :		clean all