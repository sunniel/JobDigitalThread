#
# OMNeT++/OMNEST Makefile for JobDigitalThread_IoT_Push
#
# This file was generated with the command:
#  opp_makemake -f --deep -IC:/Users/sunni/Workspace/boost_1_66_0 -IC:/Users/sunni/omnetpp-5.6.2/include/omnetpp -IC:/Users/sunni/Workspace/JSON_for_Modern_C++
#

# Name of target to be created (-o option)
TARGET = JobDigitalThread_IoT_Push$(D)$(EXE_SUFFIX)
TARGET_DIR = .

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = -IC:/Users/sunni/Workspace/boost_1_66_0 -IC:/Users/sunni/omnetpp-5.6.2/include/omnetpp -IC:/Users/sunni/Workspace/JSON_for_Modern_C++

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/common/Constants.o \
    $O/common/HostBase.o \
    $O/common/sdbm.o \
    $O/common/Util.o \
    $O/ctrl/cDACtrl.o \
    $O/ctrl/cTACtrl.o \
    $O/ctrl/eDACtrl.o \
    $O/ctrl/eTACtrl.o \
    $O/ctrl/IIoTCtrl.o \
    $O/ctrl/KnowledgeBase.o \
    $O/global/GlobalNodeList.o \
    $O/global/GlobalParameters.o \
    $O/global/GlobalStatistics.o \
    $O/global/UnderlayConfigurator.o \
    $O/objects/IPAddress.o \
    $O/objects/IPv4InterfaceData.o \
    $O/objects/IPvXAddress.o \
    $O/objects/PeerInfo.o \
    $O/objects/PeerStorage.o \
    $O/objects/SimpleInfo.o \
    $O/objects/SimpleNodeEntry.o \
    $O/objects/TransportAddress.o \
    $O/transport/InterfaceEntry.o \
    $O/transport/InterfaceTable.o \
    $O/transport/ReliableUDP.o \
    $O/transport/SimpleUDP.o \
    $O/messages/cDTLastUpdate_m.o \
    $O/messages/cDTUpdate_m.o \
    $O/messages/DTCommit_m.o \
    $O/messages/eDTUpdate_m.o \
    $O/messages/Failure_m.o \
    $O/messages/GranularityType_m.o \
    $O/messages/LastUpdate_m.o \
    $O/messages/PullRequest_m.o \
    $O/messages/Read_m.o \
    $O/messages/RemoteUpdate_m.o \
    $O/messages/SimPull_m.o \
    $O/messages/UDPControlInfo_m.o

# Message files
MSGFILES = \
    messages/cDTLastUpdate.msg \
    messages/cDTUpdate.msg \
    messages/DTCommit.msg \
    messages/eDTUpdate.msg \
    messages/Failure.msg \
    messages/GranularityType.msg \
    messages/LastUpdate.msg \
    messages/PullRequest.msg \
    messages/Read.msg \
    messages/RemoteUpdate.msg \
    messages/SimPull.msg \
    messages/UDPControlInfo.msg

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIBS = $(OPPMAIN_LIB) $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) $(IMPORT_DEFINES)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/% :: $O/%
	@mkdir -p $(TARGET_DIR)
	$(Q)$(LN) $< $@
ifeq ($(TOOLCHAIN_NAME),clangc2)
	$(Q)-$(LN) $(<:%.dll=%.lib) $(@:%.dll=%.lib)
endif

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile $(CONFIGFILE)
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET) $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE) | msgheaders smheaders
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc -MD -MP -MF $O/$(basename $<)_m.h.d $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning $(TARGET)
	$(Q)-rm -rf $O
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET)
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET:%.dll=%.lib)
	$(Q)-rm -f $(call opp_rwildcard, . , *_m.cc *_m.h *_sm.cc *_sm.h)

cleanall:
	$(Q)$(MAKE) -s clean MODE=release
	$(Q)$(MAKE) -s clean MODE=debug
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

# include all dependencies
-include $(OBJS:%=%.d) $(MSGFILES:%.msg=$O/%_m.h.d)
