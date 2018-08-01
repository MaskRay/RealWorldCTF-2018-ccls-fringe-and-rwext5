CCLS := $(HOME)/Dev/Util/ccls
LLVM := $(HOME)/Dev/llvm

LDFLAGS := -shared
CXXFLAGS := -std=c++17 -fPIC -g
CXXFLAGS += -I$(CCLS)/src -I$(CCLS)/third_party -I$(CCLS)/third_party/rapidjson/include
CXXFLAGS += -I$(LLVM)/include -I$(LLVM)/Release/include
CXXFLAGS += -I$(LLVM)/tools/clang/include -I$(LLVM)/Release/tools/clang/include

solve.so: solve.cc
	$(LINK.cc) $^ -o $@
