execute:
	g++ main.cpp -std=c++11 -o executable -lpthread -lGL -lGLU -lglut -lglui
debug:
	g++ main.cpp -g -o debug -std=c++11 -lGL -lGLU -lglut -lpthread -lglui