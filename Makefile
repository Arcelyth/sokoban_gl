SRC := ${wildcard src/*.cpp}
OUT := sokoban
CC := clang++

GLEW_H := ../../glew-2.3.1/include 
GLFW_H := ../../glfw-3.4/include 
GLM_H := ../../glm
FT_H := ../../freetype-2.10.0/include

GLEW_LIB := ../../glew-2.3.1/lib/libGLEW.a
GLFW_LIB := ../../glfw-3.4/build/src/libglfw3.a
FT_LIB := ../../freetype-2.10.0/objs/.libs/libfreetype.a

all: ${OUT}

${OUT}: 
	${CC} ${SRC} \
	-I${GLEW_H} \
	-I${GLFW_H} \
	-I${GLM_H} \
	-I${FT_H} \
	-I./vendor/stb \
	${GLEW_LIB} \
	${GLFW_LIB} \
	${FT_LIB} \
	-framework OpenGL \
	-framework Cocoa \
	-framework IOKit \
	-framework CoreVideo \
	-lbz2 \
	-lharfbuzz \
	-lfreetype \
	-lz \
	-lpng \
	-o ${OUT}
	
	./${OUT}
