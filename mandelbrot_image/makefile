CXX = g++

CXXFLAGS = -Wall
LDFLAGS = -I include -L lib -l SDL2
OBJECTS = main.o mandel.o

mendel_image:$(OBJECTS) mandel.h
	$(CXX) -g $(OBJECTS) -o mandel_image $(LDFLAGS)

main.o:main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

mendel.o:mandel.cpp
	$(CXX) $(CXXFLAGS) -c mandel.cpp -o mendel.o

clean:
	rm *.o
