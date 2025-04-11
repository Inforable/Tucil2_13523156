CXX = g++
MINGW =  x86_64-w64-mingw32
CXXFLAGS = -std=c++17
LDFLAGS = -lfreeimage 
LWINDOWS = -I./src/header -L./src/library
SRC = ./src/*.cpp
BIN = ./bin

WIN = win_compressor
LINUX = linux_compressor

windows:
	mkdir -p $(BIN)	
	$(MINGW)-$(CXX) $(CXXFLAGS) -o $(BIN)/$(WIN) $(SRC) $(LWINDOWS) $(LDFLAGS)

linux: 
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/$(LINUX) $(SRC) $(LDFLAGS)

build: windows linux

clean:
	find $(BIN) -type f ! -name 'FreeImage.dll' -delete

all: build