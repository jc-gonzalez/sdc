##############################################################################
#
#
#
##############################################################################

CXX = g++
CXXFLAGS = -Wall -W -O -g3 -std=c++11

SRC_JSON := json/jsoncpp.cpp
SRC_SDC  := src/value.cpp src/array.cpp src/dict.cpp src/valueiojsoncpp.cpp
SRC_TEST := tests/main.cpp

OBJ_JSON := $(patsubst %.cpp,%.o,$(SRC_JSON))
OBJ_SDC  := $(patsubst %.cpp,%.o,$(SRC_SDC))
OBJ_TEST := $(patsubst %.cpp,%.o,$(SRC_TEST))

JSON = json
SDC  = sdc

DIR_JSON = json
DIR_SDC  = src

LIB_JSON = $(DIR_JSON)/lib$(JSON).a
LIB_SDC  = $(DIR_SDC)/lib$(SDC).a

LIBFLAGS = -L$(DIR_SDC) -L$(DIR_JSON)
LIBS = -l$(SDC) -l$(JSON)

INCPATH = -I$(DIR_JSON) -I$(DIR_JSON)/json -I$(DIR_SDC) -Itests

APP = testsdc

all : $(LIB_JSON) $(LIB_SDC) $(APP)

$(LIB_JSON) : $(OBJ_JSON)
	ar r $@ $?
	ranlib $@

$(LIB_SDC) : $(OBJ_SDC)
	ar r $@ $?
	ranlib $@

$(APP) : $(OBJ_TEST) $(LIB_JSON) $(LIB_SDC)
	$(CXX) $(LIBFLAGS) -o $@ $< $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

clean:
	-rm $(OBJ_JSON) $(OBJ_SDC) $(OBJ_TEST)

distclean: clean
	-rm $(LIB_JSON) $(LIB_SDC) $(APP) *~
