CXX = g++
CXXFLAGS = -Wall -Wextra
LDFLAGS = -lbcrypt
SRCS = test-speed.cpp
TARGET = test-speed.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
