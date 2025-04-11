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

clean:
	find $(BIN) -type f ! -name 'FreeImage.dll' -delete

all: build