CXX = g++
CXXFLAGS = -Wall -Wextra
LDFLAGS =
SRCS = test-speed.cpp
TARGET = test-speed.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET) ./test_file

clean:
	rm -f $(TARGET)
