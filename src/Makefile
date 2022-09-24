CXXFLAGS += -std=c++2a -02 -Wall 

SRCS := main.cpp mspp_base.cpp mspp_logging.cpp mspp_serial.cpp mspp_reactor.cpp mspp_config.cpp

LIBS := -lnng

INCPATH := -I../include

BINARY = mspp_test

all: $(BINARY)


$(BINARY): main.cpp
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./mspp_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)





