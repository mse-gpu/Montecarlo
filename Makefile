
# Executable name
TARGET = montecarlo

# Paths setup
BUILD_DIR ?= build
SRC_DIRS ?= src
INC_DIRS ?= include

# C compiler and flags
CC = gcc
CCFLAGS = -W -Wall -mtune=core2 -O3 -frerun-loop-opt -fgcse -fomit-frame-pointer -fopenmp

# C++ compiler and flags
CXX = g++
CXXFLAGS = $(CCFLAGS)

##################################################################

BUILD_DIR := $(or $(BUILD_DIR), .)

INCLUDES = $(addprefix -I, $(INC_DIRS))

TARGET_PATH = $(BUILD_DIR)/$(TARGET)

SRCS = $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c')
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
OBJS := $(OBJS:.c=.o)
DEPS = $(OBJS:.o=.d)

CFLAGS += $(INCLUDES)
CXXFLAGS += $(INCLUDES)

.PHONY: all info run $(TARGET) clean

# Make the default target
all: $(TARGET)

# Run the executable
run:
	./$(TARGET_PATH)

# Include automatically generated dependency file
-include $(DEPS)

# Compile .c files to objects in the build dir
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<
	$(CC) $(INCLUDES) -MQ $@ -MM $< -MF $(basename $@).d

# Compile .cpp files to objects in the build dir
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	$(CXX) $(INCLUDES) -MQ $@ -MM $< -MF $(basename $@).d

# Build the final binary
$(TARGET_PATH): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Shortcut to link the binary and save it to the build directory
$(TARGET): $(TARGET_PATH)

# Print out some info about the compilation environment
info:
	@echo "---------------------------------------------------"
	@echo " Target:               $(TARGET)"
	@echo " C compiler:           $(CC)"
	@echo " C++ compiler:         $(CXX)"
	@echo " User:                 $(USER)"
	@echo " Build directory:      $(abspath $(BUILD_DIR))"
	@echo " Include directories:  $(INC_DIRS)"
	@echo " Source files:         $(SRCS)"
	@echo "---------------------------------------------------"

# Cleanup object files, dependency files and linked binaries
clean:
	rm -f $(DEPS)
	rm -f $(OBJS)
	rm -f $(TARGET_PATH)
ifneq ($(realpath $(BUILD_DIR)), $(realpath .))
	find $(BUILD_DIR) -type d 2>/dev/null | sort -r | xargs rmdir
endif
