TARGET  	:= libfbc
SRC_DIR 	:= ./src
INC_DIR 	:= ./include
BLD_DIR 	:= ./build
BIN_DIR		:= ./build/bin
DEP_DIR		:= ./build/dep
CPP_STD 	:= c++2a
DBG_OPT		:= -O0 -Wall -g
REL_OPT		:= -O2 -s -DNDEBGU

ifeq ($(BUILD),release)
CXXFLAGS	+= $(REL_OPT)
else
CXXFLAGS	+= $(DBG_OPT)
endif

CXX       	:= g++
CXXFLAGS  	+= -I$(INC_DIR) -std=$(CPP_STD)
LDFLAGS   	+= 
LDLIBS    	+= 
DEPFLAGS 	:= -MMD -MP -MF

SRCFILES	:= $(wildcard $(SRC_DIR)/%.cpp)
OBJFILES 	:= $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
DEPFILES 	:= $(patsubst $(SRC_DIR)/%.cpp, $(DEP_DIR)/%.d, $(wildcard $(SRC_DIR)/*.cpp))

$(BLD_DIR)/$(TARGET): $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEP_DIR)/%.d | $(BLD_DIR)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(DEP_DIR)/$*.d -c -o $@ $<

$(BLD_DIR):
	mkdir $(BLD_DIR)
	mkdir $(BIN_DIR)
	mkdir $(DEP_DIR)

$(DEPFILES):

.PHONY: clean
clean:
	rm -f -r $(BLD_DIR)

include $(wildcard $(DEPFILES))
