# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++2a

# Executable names
EXE_SERVER = main_server.o
EXE_CLIENT = main_client.o

# Source files
SERVER_SRC = server.hpp
CLIENT_SRC = client.hpp

# Header files
SERVER_HEADERS = server.h
CLIENT_HEADERS = client.h

all: $(EXE_SERVER) $(EXE_CLIENT)

$(EXE_SERVER): main_server.cpp $(SERVER_SRC) $(SERVER_HEADERS)
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXE_CLIENT): main_client.cpp $(CLIENT_SRC) $(CLIENT_HEADERS)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXE_SERVER) $(EXE_CLIENT)
