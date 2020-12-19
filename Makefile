# all: SFML_file

# OpenGL_file: 
# 	clang++ Event.cpp Engine.cpp Engine_OpenGL.cpp App.cpp -std=c++17 -arch x86_64 -framework OpenGL -I/usr/local/include -L/usr/local/lib -o OpenGL_file main.cpp -lglfw.3 -lGLEW.2.1.0 -framework CoreVideo -framework IOKit -framework Cocoa -framework Carbon -framework GLUT && ./OpenGL_file

# SFML_file:
# 	clang++ Event.cpp Engine_protocol.cpp Engine.cpp Engine_SFML.cpp App.cpp Window.cpp Button.cpp Label.cpp Image.cpp Scroll_bar.cpp System_window.cpp Color.cpp File_manager.cpp dump.cpp Object.cpp help_classes.cpp Canvas.cpp Thickness.cpp Palette.cpp Tool.cpp Tool_manager.cpp Plugin.cpp ./ColorPanel/MyCPPClass.cpp ./ColorPanel/MyObject.mm -std=c++17 -arch x86_64 -F/Library/Frameworks -framework Cocoa -framework SFML -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o SFML_file main.cpp && ./SFML_file

# clear:
# 	rm SFML_file OpenGL_file

.PHONY: all clean

EXECUTABLE   := Paint
OBJ_D        := ./objects
HEADERS      := $(wildcard *.hpp)
SOURCEFILES  := $(wildcard *.cpp)
OBJFILES     := $(SOURCEFILES:%.cpp=$(OBJ_D)/%.o)
CFlags       := -std=c++17 -O3 -arch x86_64
Warnings     := -Wall -Wextra -Weffc++ -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wmissing-declarations -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wno-unused-result -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -fPIE
Flags_SFML   := -F/Library/Frameworks -framework Cocoa -framework SFML -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: $(SOURCEFILES) $(HEADERS) $(EXECUTABLE)
	@./$(EXECUTABLE)

$(EXECUTABLE): $(OBJFILES)
	@g++ $(OBJFILES) -o $@ $(Flags_SFML)

$(OBJ_D)/%.o: %.cpp
	@g++ $(CFlags) -c $< -o $@

clean:
	@rm -f $(OBJFILES) $(EXECUTABLE)