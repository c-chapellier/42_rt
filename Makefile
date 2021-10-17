SRCS =	srcs/main.cpp \
		srcs/window/Window.cpp \
		srcs/loadingBar/LoadingBar.cpp \
		srcs/pixel/Pixel.cpp \
		srcs/image/Image.cpp \
		srcs/parser/Parser.cpp \
		srcs/visuals/Camera.cpp \
		srcs/color/Color.cpp \
		srcs/config/Config.cpp \
		srcs/objects/components/Point.cpp \
		srcs/objects/components/Vector.cpp \
		srcs/objects/components/Triangle.cpp \
		srcs/objects/factories/AlphaFactory.cpp \
		srcs/objects/factories/PolygoneFactory.cpp \
		srcs/objects/factories/ShapeFactory.cpp \
		srcs/objects/transformer/Transformer.cpp \
		srcs/objects/Object.cpp \
		srcs/objects/Line.cpp \
		srcs/objects/Plane.cpp \
		srcs/objects/Polygone.cpp \
		srcs/objects/Quadratic.cpp \
		srcs/headers/define.cpp \
		srcs/saver/Saver.cpp \

NAME = rt

FLAGS		= -Wall -Wextra -Werror

all :
			g++ -std=c++11 ${FLAGS} -o ${NAME} ${SRCS} -lSDL2

run :		all
			./${NAME} configs/test.json

clean :
			rm -f ${NAME}

re :		clean all