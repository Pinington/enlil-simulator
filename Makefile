# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src

# Output
TARGET = bin/enlil.exe

# Find all sources
SOURCES = main.cpp

# Default build
all: $(TARGET)

# Link
$(TARGET):
	@if not exist bin mkdir bin
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Clean (safe)
clean:
	@if exist bin del /f /s /q bin\*

# Rebuild
re: clean all

.PHONY: all clean re