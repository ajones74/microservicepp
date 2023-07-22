CXXFLAGS += -std=c++17 -O2 -Wall 

GPS_SRCS := gps_service.cpp \
		  ../exceptions/src/mspp_exceptions.cpp \

LIBPATH := -L../nng/build/
LIBS := -lpthread -lnng

INCPATH := -I../json/single_include \
			  -I../nng/include/ \
         -I../base_classes/include \
			-I../exceptions/include \
         -I../services/include \
		   -I../sections/include \
		   -I../pools/include \
		   -I../pumps/include

GPS_BIN = gps_service
LOGGING_BIN = logging_service
CONFIG_BIN = configuration_service


all: $(GPS_BIN) 


$(GPS_BIN): $(GPS_SRCS)
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./gps_service_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

$(CONFIG_BIN): $(CONFIG_SRCS)
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./configuration_service_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

$(LOGGING_BIN): $(LOGGING_SRCS)
	@echo 'const char *bVer = "' `git describe --dirty --always --long` '";' > ./logging_service_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

clean:
	rm -f $(GPS_BIN) $(CONFIG_BIN) $(LOGGING_BIN) *_service_version.h




