
all:
	g++ Engine.cpp Engine_OpenGL.cpp App.cpp -std=c++17 -arch x86_64 -framework OpenGL -I/usr/local/include -L/usr/local/lib -o main main.cpp -lglfw.3 -lGLEW.2.1.0 -framework CoreVideo -framework IOKit -framework Cocoa -framework Carbon -framework GLUT
