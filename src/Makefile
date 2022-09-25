CXXFLAGS += -std=c++2a -O2 -Wall 

SRCS := main.cpp ../lib/mspp_base.cpp ../lib/mspp_logging.cpp ../lib/mspp_serial.cpp ../lib/mspp_reactor.cpp ../lib/mspp_config.cpp \
		  ../lib/mspp_exceptions.cpp ../lib/mspp_manager.cpp

#LIBS := -lnng

INCPATH := -I../include

BINARY = mspp_test

all: $(BINARY)


$(BINARY): $(SRCS)
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./mspp_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

clean:
	rm -f $(BINARY) mspp_version.h



