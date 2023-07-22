CXXFLAGS += -std=c++17 -O2 -Wall 

TEST_SRCS := main.cpp \
		  ../exceptions/src/mspp_exceptions.cpp \

LIBPATH := -L../nng/build/
LIBS := -lpthread -lnng

INCPATH := -I../json/single_include \
			  -I../nng/include/ \
         -I../base_classes/include \
			-I../exceptions/include \
         -I../services/include \
		   -I../elements/include \
		   -I../pads/include


TEST_BIN = mspp_test

all: $(TEST_BIN) $(GPS_BIN) 


$(TEST_BIN): $(TEST_SRCS)
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./mspp_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

$(GPS_BIN): 

clean:
	rm -f $(TEST_BIN) mspp_version.h



