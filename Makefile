CXX = g++
CXXFLAGS = -Wall -Wextra -O2
TARGETS = lru fifo
all: $(TARGETS)
lru: lru.cpp
	$(CXX) $(CXXFLAGS) -o lru lru.cpp
fifo: fifo.cpp
	$(CXX) $(CXXFLAGS) -o fifo fifo.cpp
clean:
	del lru.exe fifo.exe
