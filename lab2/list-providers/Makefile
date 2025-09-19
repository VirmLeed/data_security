CXX = g++
CXXFLAGS = -Wall -Wextra
LDFLAGS = -lbcrypt
SRCS = list-providers.cpp
TARGET = list-providers.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
