CXXFLAGS += -std=c++17 -O2 -Wall 

SRCS := main.cpp \
		  ../services/lib/mspp_base.cpp \
		  ../services/lib/mspp_exceptions.cpp \
		  ../services/lib/mspp_logger.cpp \
		  ../services/lib/mspp_manager.cpp \
		  ../services/lib/mspp_pad.cpp

#LIBS := -lnng

INCPATH := -I../services/include

BINARY = mspp_test

all: $(BINARY)


$(BINARY): $(SRCS)
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./mspp_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

clean:
	rm -f $(BINARY) mspp_version.h



