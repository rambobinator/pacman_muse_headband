ENDIANESS=OSC_DETECT_ENDIANESS #source code will detect using preprocessor
#ENDIANESS=OSC_HOST_LITTLE_ENDIAN

UNAME := $(shell uname)

CXX := g++
INCLUDES := -I.
COPTS  := -Wall -Wextra -O3
CDEBUG := -Wall -Wextra -g 
CXXFLAGS := $(COPTS) $(INCLUDES) -D$(ENDIANESS)

BINDIR := bin
PREFIX := /usr/local
INSTALL := install -c

RECEIVETEST := $(BINDIR)/OscReceiveTest

INCLUDEDIR := oscpack
LIBNAME := liboscpack
LIBSONAME := $(LIBNAME).so
LIBFILENAME := $(LIBSONAME).1.1.0

# Common source groups

RECEIVESOURCES := osc/OscReceivedElements.cpp osc/OscPrintReceivedElements.cpp
NETSOURCES := ip/posix/UdpSocket.cpp ip/IpEndpointName.cpp ip/posix/NetworkingUtils.cpp
COMMONSOURCES := osc/OscTypes.cpp

RECEIVEOBJECTS := $(RECEIVESOURCES:.cpp=.o)
NETOBJECTS := $(NETSOURCES:.cpp=.o)
COMMONOBJECTS := $(COMMONSOURCES:.cpp=.o)

RECEIVETESTSOURCES := tests/OscReceiveTest.cpp
RECEIVETESTOBJECTS := $(RECEIVETESTSOURCES:.cpp=.o)

LIBOBJECTS := $(RECEIVEOBJECTS) $(COMMONOBJECTS) $(NETOBJECTS) #$(SENDOBJECTS)

.PHONY: all unittests sendtests receivetest simplesend simplereceive dump library clean install install-local


all: receivetest dump 

receivetest : $(RECEIVETEST)

$(UNITTESTS) $(SENDTESTS) $(RECEIVETEST) $(SIMPLESEND) $(SIMPLERECEIVE) $(DUMP) : $(COMMONOBJECTS) | $(BINDIR)
	$(CXX) -o $@ $^

$(RECEIVETEST) : $(RECEIVETESTOBJECTS) $(RECEIVEOBJECTS) $(NETOBJECTS)

$(BINDIR):
	mkdir $@

clean:
	rm -rf $(BINDIR) $(UNITTESTOBJECTS) $(SENDTESTSOBJECTS) $(RECEIVETESTOBJECTS) $(DUMPOBJECTS) $(LIBOBJECTS) $(SIMPLESENDOBJECTS) $(SIMPLERECEIVEOBJECTS) $(LIBFILENAME) include lib oscpack &> /dev/null

$(LIBFILENAME): $(LIBOBJECTS)
ifeq ($(UNAME), Darwin)
	#Mac OS X case
	$(CXX) -dynamiclib -Wl,-install_name,$(LIBSONAME) -o $(LIBFILENAME) $(LIBOBJECTS) -lc
else
	#GNU/Linux case
	$(CXX) -shared -Wl,-soname,$(LIBSONAME) -o $(LIBFILENAME) $(LIBOBJECTS) -lc
endif

lib: $(LIBFILENAME)
