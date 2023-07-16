CXXFLAGS += -std=c++17 -O2 -Wall 

TEST_SRCS := main.cpp \
		  ../base_classes/src/mspp_base_service.cpp \
		  ../base_classes/src/mspp_base_element.cpp \
		  ../base_classes/src/mspp_base_pad.cpp \
		  ../lib/src/mspp_exceptions.cpp \
		  ../services/src/mspp_service_configuration.cpp \
		  ../services/src/mspp_service_logger.cpp \
		  ../services/src/mspp_service_manager.cpp

#LIBS := -lnng

INCPATH := -I../json/single_include \
         -I../base_classes/include \
			-I../lib/include \
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



