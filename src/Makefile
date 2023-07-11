CXXFLAGS += -std=c++17 -O2 -Wall 

SRCS := main.cpp \
		  ../lib/src/mspp_base_service.cpp \
		  ../lib/src/mspp_base_element.cpp \
		  ../lib/src/mspp_base_pad.cpp \
		  ../services/src/mspp_configuration.cpp \
		  ../services/src/mspp_exceptions.cpp \
		  ../services/src/mspp_logger.cpp \
		  ../services/src/mspp_manager.cpp

#LIBS := -lnng

INCPATH := -I../lib/include \
         -I../services/include \
		   -I../elements/include \
		   -I../pads/include


BINARY = mspp_test

all: $(BINARY)


$(BINARY): $(SRCS)
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./mspp_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

clean:
	rm -f $(BINARY) mspp_version.h



