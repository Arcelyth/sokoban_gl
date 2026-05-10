all: sokobang

sokobang: main.cpp
	clang++ $< \
	-I../../glew-2.3.1/include \
	-I../../glfw-3.4/include \
	-I../../soil/inc/SOIL \
	-I../../glm \
	../../glew-2.3.1/lib/libGLEW.a \
	../../glfw-3.4/build/src/libglfw3.a \
	../../soil/build/libsoil.a \
	-framework OpenGL \
	-framework Cocoa \
	-framework IOKit \
	-framework CoreVideo \
	-o sokobang
