CXX = g++

CXXFLAGS = -std=c++11 -g `pkg-config --cflags sdl2 gl`
LIBS = `pkg-config --libs sdl2 gl` -lgtest

OUT_EXE = HW2

all: $(OUT_EXE)

$(OUT_EXE): main.o renderer.o glwrapper.o objLoader.o
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
	@./$<
