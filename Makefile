CC := g++

CFLAGS = -Wall -Wextra -std=c++17 -I./$(INCLUDE_DIR)

OUTPUT_DIR = output

SRC_DIR = src

INCLUDE_DIR = include


TARGET = battleship

SOURCES  := $(wildcard $(SRC_DIR)/*.cpp)

OBJECTS  := $(patsubst $(SRC_DIR)/%.cpp, $(OUTPUT_DIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

clean:
	rm -rf $(OUTPUT_DIR) $(TARGET)
