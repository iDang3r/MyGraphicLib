all: SFML_file

OpenGL_file: 
	clang++ Event.cpp Engine.cpp Engine_OpenGL.cpp App.cpp -std=c++17 -arch x86_64 -framework OpenGL -I/usr/local/include -L/usr/local/lib -o OpenGL_file main.cpp -lglfw.3 -lGLEW.2.1.0 -framework CoreVideo -framework IOKit -framework Cocoa -framework Carbon -framework GLUT && ./OpenGL_file

SFML_file:
	clang++ Event.cpp Engine.cpp Engine_OpenGL.cpp App.cpp Color.cpp ./ColorPanel/MyCPPClass.cpp ./ColorPanel/MyObject.mm -std=c++17 -arch x86_64 -F/Library/Frameworks -framework Cocoa -framework SFML -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o SFML_file main.cpp && ./SFML_file

clear:
	rm SFML_file OpenGL_file