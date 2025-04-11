CXX = g++
MINGW =  x86_64-w64-mingw32
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
	sudo apt-get install libfreeimage3 libfreeimageplus3 libfreeimage-dev mingw-w64

clean:
	rm -f $(BIN)/$(LINUX)

all: build