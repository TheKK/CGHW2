TEST_SRC_DIR := test

TEST_SRCS := $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJS := $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.cpp=.o))
TEST_DEPS := $(OBJS:.o=.d)

TEST_RUNNER := $(BUILD_DIR)/$(BIN_DIR)/testRunner

test: $(TEST_RUNNER)

build/bin/testRunner: $(TEST_OBJS) $(filter-out %main.o, $(OBJS))
	@mkdir -p $(dir $@)
	@$(CXX) $^ $(LIBS) -o $@
	@echo "     LD     " $(notdir $@)

.PHONY: runTest
runTest: $(TEST_RUNNER)
	@$<
