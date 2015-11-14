CXX=g++
CXXFLAGS=--std=c++11 -g -O1

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(APPS)

