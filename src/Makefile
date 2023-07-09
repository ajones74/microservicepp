CXXFLAGS += -std=c++17 -O2 -Wall 

SRCS := main.cpp \
		  ../lib/mspp_exceptions.cpp \
		  ../lib/mspp_pad.cpp

#LIBS := -lnng

INCPATH := -I../include

BINARY = mspp_test

all: $(BINARY)


$(BINARY): $(SRCS)
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./mspp_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

clean:
	rm -f $(BINARY) mspp_version.h



