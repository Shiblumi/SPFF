CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
INCLUDE = -I include

TARGET = SPFF
SRCS = main.cpp file_data.cpp file_manip.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
