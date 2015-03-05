CFLAGS = -std=c++0x -g -I./inc `pkg-config --cflags sdl2 gl`
LIBS = `pkg-config --libs sdl2 gl`

HW2.exe: main.o hw2.o glwrapper.o
	g++ -o HW2.exe main.o hw2.o glwrapper.o $(LIBS)

main.o: main.cpp hw2.h
	g++ $(CFLAGS) -c main.cpp

hw2.o: hw2.h
	g++ $(CFLAGS) -c hw2.cpp

glwrapper.o: glwrapper.h
	g++ $(CFLAGS) -c glwrapper.cpp

clean:
	del *.o *.exe
