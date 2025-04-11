CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lfreeimage 
LWINDOWS = -Isrc/header -Lsrc/library
SRC = ./src/*.cpp
BIN = ./bin

LINUX = linux_compressor

linux: 
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/$(LINUX) $(SRC) $(LDFLAGS)

build: linux

install:
	sudo apt-get install libfreeimage3 libfreeimage-dev

clean:
	rm -f $(BIN)/$(LINUX)

all: build