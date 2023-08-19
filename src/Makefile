CXXFLAGS += -std=c++17 -O2 -Wall

COMMON_SRCS := \
	../exceptions/src/mspp_exceptions.cpp \
	../agents/src/Logging_Agent.cpp \
	../agents/src/Configuration_Agent.cpp 


GPS_SRCS := \
	../sections/src/Serial_port_section.cpp \
	../sections/src/Push_port_section.cpp \
	../sections/src/NMEA_0183_filters_section.cpp \
	../library/src/Serial.cpp \
	../services/src/GPS.cpp

CONFIG_SRCS := ../services/src/Configuration_Service.cpp

LOGGING_SRCS := ../services/src/Logging_Service.cpp

LIBPATH := -L../nng/build/
LIBS := -lstdc++fs -lpthread -lnng

INCPATH := \
	-I. \
	-I../json/single_include \
	-I../nng/include/ \
	-I../base_classes/include \
	-I../exceptions/include \
	-I../library/include \
	-I../pipelines/include \
	-I../sections/include \
	-I../services/include \
	-I../agents/include \
	-I../spdlog/include 

GPS_BIN = gps_service
LOGGING_BIN = logging_service
CONFIG_BIN = configuration_service


#all: $(LOGGING_BIN) $(CONFIG_BIN) $(GPS_BIN)
all: $(GPS_BIN)


$(GPS_BIN): $(GPS_SRCS) $(COMMON_SRCS)
	@echo 'const char *git_build_details = "' `git describe --dirty --always --long` '";' > ./FPCM_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

$(CONFIG_BIN): $(CONFIG_SRCS) $(COMMON_SRCS)
	@echo 'const char *git_build_details = "' `git describe --dirty --always --long` '";' > ./FPCM_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

$(LOGGING_BIN): $(LOGGING_SRCS) $(COMMON_SRCS)
	@echo 'const char *git_build_details = "' `git describe --dirty --always --long` '";' > ./FPCM_version.h
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@ $(LIBPATH) $(LIBS)

clean:
	rm -f $(GPS_BIN) $(CONFIG_BIN) $(LOGGING_BIN) FPCM_version.h




