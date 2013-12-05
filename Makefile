# Because i like it nice and tidy

CC_FLAGS=-std=c++11 -g #-I $(wildcard lib/*)
LD_FLAGS=-lboost_system

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,bin/%.o,$(CPP_FILES))

tsp.exe: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

bin/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ $(CC_FLAGS) -c -o $@ $<

#VectorTest.cpp: VectorTest.h
#	cxxtestgen --error-printer -o $@ $<



.PHONY: clean
clean:
	rm -rf bin
	rm -f *.exe

