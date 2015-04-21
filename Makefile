# Check if pkg-config is installed, we need it for building CFLAGS/LIBS
ifeq ($(shell which pkg-config 2>/dev/null 1>/dev/null || echo 1), 1)
$(error "pkg-config was not found")
endif

CXX := g++
CXXFLAGS += -std=c++11 -g
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -MMD -MP
CXXFLAGS += $(shell pkg-config --cflags sdl2 gl glew)
LIBS += $(shell pkg-config --libs sdl2 gl glew) -lgtest

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
DEPS := $(OBJS:.o=.d)

OUT_EXE := $(BUILD_DIR)/$(BIN_DIR)/sre

all: $(OUT_EXE)

include $(wildcard mk/*.mk)

$(OUT_EXE): $(OBJS)
	@mkdir -p $(dir $@)
	@$(CXX) $^ $(LIBS) -o $@
	@echo "     LD     " $(notdir $@)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@
	@echo "     CXX    " $(notdir $@)

.PHONY: clean
clean:
	@rm -frv $(BUILD_DIR)

-include $(DEPS)
