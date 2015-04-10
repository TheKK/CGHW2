# Check if pkg-config is installed, we need it for building CFLAGS/LIBS
ifeq ($(shell which pkg-config 2>/dev/null 1>/dev/null || echo 1),1)
$(error "pkg-config was not found")
endif

CXX = g++
CXXFLAGS += -std=c++11 -g ``
CXXFLAGS += -Wall -Wextra
CXXFLAGS += $(shell pkg-config --cflags sdl2 gl)
LIBS += $(shell pkg-config --libs sdl2 gl)

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

all: sre

sre: $(OBJS)
	@$(CXX) $^ $(LIBS) -o $@
	@echo "     LD     " $(notdir $@)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "     CXX    " $(notdir $@)

.PHONY: clean test
clean:
	@rm *.o $(OUT_EXE)
