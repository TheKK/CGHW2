CXX = g++

CXXFLAGS = -std=c++0x -g `pkg-config --cflags sdl2 gl`
LIBS = `pkg-config --libs sdl2 gl` -lgtest

OUT_EXE = HW2

all: $(OUT_EXE)

$(OUT_EXE): main.o hw2.o glwrapper.o
	@$(CXX) $^ $(LIBS) -o $@
	@echo "     LD     " $(notdir $@)

testRunner: test/testRunner.o test/objLoader_test.o objLoader.o
	@$(CXX) $^ $(LIBS) -o $@
	@echo "     LD     " $(notdir $@)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "     CXX    " $(notdir $@)

.PHONY: clean test
clean:
	@rm *.o $(OUT_EXE)

test: testRunner
