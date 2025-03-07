# Makefile for building fate.cpp into either a Windows or Linux program

# Compiler and linker settings
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
LDFLAGS :=

# Source files
SRCS := fate.cpp
OBJS := $(SRCS:.cpp=.o)

# Target executable
TARGET := fate

# Detect the OS
ifeq ($(OS),Windows_NT)
	TARGET := fate.exe
	CXX := x86_64-w64-mingw32-g++
	LDFLAGS += -static
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
	endif
endif

# Source files
SRCS := fate.cpp helpers/gamestate.cpp targets/target.cpp helpers/directory.cpp
OBJS := $(SRCS:.cpp=.o)

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean