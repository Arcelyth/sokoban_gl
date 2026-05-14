SRC := ${wildcard src/*.cpp}
OUT := sokobang

all: ${OUT}

${OUT}: 
	clang++ ${SRC} \
	-I../../glew-2.3.1/include \
	-I../../glfw-3.4/include \
	-I./vendor/stb \
	-I../../glm \
	../../glew-2.3.1/lib/libGLEW.a \
	../../glfw-3.4/build/src/libglfw3.a \
	-framework OpenGL \
	-framework Cocoa \
	-framework IOKit \
	-framework CoreVideo \
	-o ${OUT}
	
	./${OUT}
