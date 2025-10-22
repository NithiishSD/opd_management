# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ialgorithms

# Source files
SRC = src/patients.cpp \
      src/heap.cpp \
      src/hash_table.cpp \
      modules/opd_module.cpp \
      modules/admission_module.cpp \
      modules/discharge_module.cpp \
      modules/city_integration_module.cpp \
	  src/bed_manager.cpp\
	  src/city_graph.cpp\
	  src/hospital.cpp\
	  src/opd_queue.cpp\
      src/main.cpp\
	  src/utils.cpp\

# Object files
OBJ = $(SRC:.cpp=.o)

# Target executable
TARGET = opd_management.exe

# Default rule
all: $(TARGET)

# Link the objects to create executable
$(TARGET): $(OBJ) 
	$(CXX) $(OBJ) -o $(TARGET)

# Compile each .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
