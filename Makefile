SRC := ${wildcard src/*.cpp}
OUT := sokoban

all: ${OUT}

${OUT}: 
	clang++ ${SRC} \
	-I../../glew-2.3.1/include \
	-I../../glfw-3.4/include \
	-I./vendor/stb \
	-I../../glm \
	-I../../freetype-2.10.0/include \
	../../glew-2.3.1/lib/libGLEW.a \
	../../glfw-3.4/build/src/libglfw3.a \
	../../freetype-2.10.0/objs/.libs/libfreetype.a \
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
