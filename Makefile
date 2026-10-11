SRCS := $(wildcard *.cpp)

all:
	g++ -std=c++17 -pthread $(SRCS) -o miniwireshark

clean:
	rm -f miniwireshark