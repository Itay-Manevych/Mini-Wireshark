SRCS := $(shell find . -name '*.cpp')

all:
	g++ -std=c++17 -pthread -I. $(SRCS) -o miniwireshark

clean:
	rm -f miniwireshark