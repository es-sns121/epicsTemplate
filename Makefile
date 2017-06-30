
SRC = template.cpp # Source file
EXE = template     # Executable

all: $(EXE)

CPPFLAGS = -Wall -g

INCLUDES = -I$(EPICS_V3_DIR)/include                    \
		   -I$(EPICS_V3_DIR)/include/compiler/gcc       \
		   -I$(EPICS_V3_DIR)/include/valgrind           \
		   -I$(EPICS_V3_DIR)/include/os/$(HOST_OS)      \
		   -I$(EPICS_V4_DIR)/pvAccessCPP/include        \
		   -I$(EPICS_V4_DIR)/pvDataCPP/include          \
		   -I$(EPICS_V4_DIR)/normativeTypesCPP/include  \
		   -I$(EPICS_V4_DIR)/pvaClientCPP/include       \
		   -I$(EPICS_V4_DIR)/pvCommonCPP/include

LIBS =  -L$(EPICS_V3_DIR)/lib/$(EPICS_HOST_ARCH) -lCom                     \
		-L$(EPICS_V4_DIR)/pvDataCPP/lib/$(EPICS_HOST_ARCH) -lpvData        \
		-L$(EPICS_V4_DIR)/pvAccessCPP/lib/$(EPICS_HOST_ARCH) -lpvAccess    \
		-L$(EPICS_V4_DIR)/pvCommonCPP/lib/$(EPICS_HOST_ARCH) -lpvMB        \
		-L$(EPICS_V4_DIR)/pvaClientCPP/lib/$(EPICS_HOST_ARCH) -lpvaClient  \
		-L$(EPICS_V4_DIR)/normativeTypesCPP/lib/$(EPICS_HOST_ARCH) -lnt    \
		-lpthread -lm

$(EXE) : $(SRC)
	g++  $(CPPFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(EXE)

clean:
	rm -f $(EXE)
