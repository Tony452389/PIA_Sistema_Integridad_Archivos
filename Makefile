CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/main.cpp \
      src/file_scanner.cpp \
      src/hash_engine.cpp \
      src/baseline_manager.cpp \
      src/risk_analyzer.cpp

TARGET = file_monitor

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

