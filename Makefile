######################################################################
# $URL: http://memo.prisma/svn/tm/IuhCsComba_Tm/tags/IuhCsComba_Tm-1.2.0/Makefile $
# 
# $Author: roger $
# $Date: 2012-09-19 16:38:39 +0200 (Wed, 19 Sep 2012) $
# 
# $Rev: 54444 $
######################################################################

# overwrite CC environment variable (it is visible recursively to all Makefiles)
CC := gcc44
LN := $(CC)

Main	:= iuhcs_comba_tm
Main_R8	:= iuhcs_comba_tm_r8

EXE_DIR := tgt/bin
SCRIPTS_DIR := tgt

# directory to host user interface documentation
DOC_DIR := $(SCRIPTS_DIR)/pub

# list of header file used to generate user interface documentation
doc_orig_files := protocols/RUA/src/tstmRUA.h protocols/HNBAP/src/tstmHNBAP.h

.DEFAULT_GOAL := all

##############################

MAKEFLAGS := -r
include   ./mkUtils/Make--

ifeq ($(strip $(VER)),)
#if executable name not defined
VER=trunk
endif

############################## CFLAGS

# fwPLATFORM_LINUX and fwPLATFORM_NTO are required by modules of src
ifeq ($(__make_os), linux)

CFLAGS += -DfwPLATFORM_LINUX

else
ifeq ($(__make_os), nto)

CFLAGS += -DfwPLATFORM_NTO

else

#if __make_os has a wrong value ----------------------------------------
$(error unexpected value for __make_os=$(__make_os) )

endif #nto
endif #linux

CFLAGS += -Dostype_$(__make_os)=1

##############################
# Directories with their own Makefile.
##############################

fw        := ./lib
fwincs    := $(fw)
libfw     := $(fw)/libfw.a
FW_DOC_DIR := ./doc

##############################

TCL_DIR := /usr/local/Tcl-8.5.9

##############################

tstmlib    := ./lib
libtstm    := $(tstmlib)/libtstm.a
libtstm_r8 := $(tstmlib)/libtstm_r8.a
libpvm     := $(tstmlib)/libpvm3.a

##############################

TCL_DIR := /usr/local/Tcl-8.5.9
export  Tcl := /usr/local/Tcl-8.5.9/include


##############################
# libraries created directly by this Makefile
##############################

##############################
# RUA
##############################

ruasrc_dir := ./protocols/RUA/src/
LibRUA := $(ruasrc_dir)/librua.a
ruaasn1_dir	:= $(ruasrc_dir)/asn1c/C
LibRUA_ASN1 := $(ruaasn1_dir)/libruaasn1.a

##############################
# HNBAP
##############################

hnbapsrc_dir := ./protocols/HNBAP/src/
LibHNBAP := $(hnbapsrc_dir)/libhnbap.a
hnbapasn1_dir	:= $(hnbapsrc_dir)/asn1c/C
LibHNBAP_ASN1 := $(hnbapasn1_dir)/libhnbapasn1.a

##############################


deps           := ./_deps

ASN1BASE=asn1c
asn1base_inc := $(ASN1BASE)
asn1base_inc += $(ASN1BASE)/rtbersrc
asn1base_inc += $(ASN1BASE)/rtpersrc
asn1base_inc += $(ASN1BASE)/rtsrc
asn1base_inc += $(ASN1BASE)/rtxsrc


###########################################################
# RUA ASN1
###########################################################

.PHONY: ruaAsn1 ruaAsn1_clean

#
# ruaAsn1: check dependences and create RUA ASN1 library
# ruaAsn1_clean: clean ruaAsn1
#

ruaAsn1srcs := $(wildcard $(ruaasn1_dir)/*.c)
ruaAsn1incs := + $(asn1base_inc) $(fwincs) $(TCL_DIR)/include

ruaAsn1 $(LibRUA_ASN1): $(ruaAsn1srcs)
		$(call __makeLib,$(LibRUA_ASN1),$(ruaAsn1srcs),$(ruaAsn1incs),$(deps))

ruaAsn1_clean:
		$(call __makeExec, rm -f,$(LibRUA_ASN1))


###########################################################
# RUA
###########################################################

.PHONY: rua rua_clean

#
# rua: check dependences and create RUA library
# rua_clean: clean rua
#

ruasrcs := $(wildcard $(ruasrc_dir)/*.c)
ruaincs := + $(ruaasn1_dir) $(asn1base_inc) $(fwincs) $(TCL_DIR)/include

rua $(LibRUA): $(ruasrcs)
		$(call __makeLib,$(LibRUA),$(ruasrcs),$(ruaincs),$(deps))

rua_clean:
		$(call __makeExec, rm -f,$(LibRUA))


###########################################################
# HNBAP ASN1
###########################################################

.PHONY: hnbapAsn1 hnbapAsn1_clean

#
# hnbapAsn1: check dependences and create HNBAP ASN1 library
# hnbapAsn1_clean: clean hnbapAsn1
#

hnbapAsn1srcs := $(wildcard $(hnbapasn1_dir)/*.c)
hnbapAsn1incs := + $(asn1base_inc) $(fwincs) $(TCL_DIR)/include

hnbapAsn1 $(LibHNBAP_ASN1): $(hnbapAsn1srcs)
		$(call __makeLib,$(LibHNBAP_ASN1),$(hnbapAsn1srcs),$(hnbapAsn1incs),$(deps))

hnbapAsn1_clean:
		$(call __makeExec, rm -f,$(LibHNBAP_ASN1))


###########################################################
# HNBAP
###########################################################

.PHONY: hnbap hnbap_clean

#
# hnbap: check dependences and create HNBAP library
# hnbap_clean: clean hnbap
#

hnbapsrcs := $(wildcard $(hnbapsrc_dir)/*.c)
hnbapincs := + $(hnbapasn1_dir) $(asn1base_inc) $(fwincs) $(TCL_DIR)/include

hnbap $(LibHNBAP): $(hnbapsrcs)
		$(call __makeLib,$(LibHNBAP),$(hnbapsrcs),$(hnbapincs),$(deps))

hnbap_clean:
		$(call __makeExec, rm -f,$(LibHNBAP))


###########################################################
# Rules to build the executable
###########################################################

###########################################################
# create executable
###########################################################

.PHONY: libs all rebuild link link_r8

ifeq ($(__make_os), linux)
ASN1BASE_LIB_DIR   := $(ASN1BASE)/c/lib
else
ifeq ($(__make_os), nto)
ASN1BASE_LIB_DIR   := $(ASN1BASE)/c/lib_nto
endif #nto
endif #linux

# list of all libraries used for the executable
# -lm for mathematical libraries
# libtstm is listed two times because LibRUA/LibHNBAP require libtstm and viceversa.
libs :=  $(LibRUA) $(LibHNBAP) $(libpvm) $(libfw) $(TCL_DIR)/lib/libtcl.a $(LibRUA_ASN1) $(LibHNBAP_ASN1) -lm -lrt -lpthread $(ASN1BASE_LIB_DIR)/libasn1ber.a $(ASN1BASE_LIB_DIR)/libasn1per.a $(ASN1BASE_LIB_DIR)/libasn1rt.a

libs: rua ruaAsn1 hnbap hnbapAsn1 $(libs)

$(Main):     libs link install
$(Main_R8):  libs link_r8 install_r8

all:        $(Main) $(Main_R8)

rebuild:    clean all

link:
	$(LN) -static -Wl,-Map,$(Main).map -o$(Main) $(libs)
link: libs := $(libtstm) $(libs) $(libtstm)

link_r8:
	$(LN) -static -Wl,-Map,$(Main_R8).map -o$(Main_R8) $(libs)
link_r8: libs := $(libtstm_r8) $(libs) $(libtstm_r8)

###########################################################
# create executable for debugging (UE side)
###########################################################

.PHONY: gdb gdb_rebuild
 
GDB_OPT := -O0 -g2 -fno-omit-frame-pointer

# overwrite optimization options
gdb: CFLAGS += $(GDB_OPT)
gdb: all
gdb_rebuild: clean gdb


###########################################################
# TCL profiler
###########################################################

.PHONY: profiler

profiler: LN := g++44
profiler: srcs += $(wildcard ./tclProfiler/*.c ./tclProfiler/*.cpp)
profiler: CFLAGS += -DTCL_PROFILER_ON
profiler: all


###########################################################
# Clean
###########################################################

.PHONY: clean semiclean

clean:  rua_clean ruaAsn1_clean hnbap_clean hnbapAsn1_clean
		$(call __makeExec, rm -f,$(Main))
		$(call __makeExec, rm -f,$(Main_R8))
		$(call __makeExec, rm -f,$(EXE_DIR)/$(Main))
		$(call __makeExec, rm -f,$(EXE_DIR)/$(Main_R8))
		$(call __makeExec, rm -f,$(Main).map)
		$(call __makeExec, rm -f,$(Main_R8).map)
		$(call __makeExec, rm -rf,$(doc_txt_files) $(doc_h_files))
		$(call __makeExec, rm -rf,$(deps))


###########################################################
# Rules to install executable and documentation
###########################################################

.PHONY: install install_r8 updatedoc

# For every header file listed in doc_orig_files, a .txt file will be created.
doc_h_files := $(addprefix $(DOC_DIR)/,$(notdir $(doc_orig_files)))
doc_txt_files := $(doc_h_files:%.h=%.txt)

install: updatedoc $(doc_txt_files)
	$(call __makeInst, $(EXE_DIR), $(Main))

install_r8: updatedoc $(doc_txt_files)
	$(call __makeInst, $(EXE_DIR), $(Main_R8))

fwdoc_scripts := tstmh2WSN hdr.txt
fwdoc_scripts_full_path := $(fwdoc_scripts:%=$(FW_DOC_DIR)/%)

# rule to create .txt files
$(doc_txt_files): %.txt: %.h $(fwdoc_scripts_full_path)
	tclsh $(FW_DOC_DIR)/tstmh2WSN $(FW_DOC_DIR)/hdr.txt $< $@ ""

# Copy to DOC_DIR all header files used to create user interface documentation.
# They are copied to simplify rule for .txt files creation.
# Only modified header files are copied and DOC_DIR is created if absent.
updatedoc:
	$(call __makeInst, $(DOC_DIR), $(doc_orig_files))


###########################################################
# help
###########################################################

.PHONY:     help h

help h: ; @echo -en "\
\n\
    <h>,<help>   this help\n\
\n\
 Executable targets:\n\
\n\
    <all>            build one executable with BSSAP R4 and one with BSSAP R8\n\
    <clean>          remove $(Main), $(Main_R8) and $(DOC_DIR)\n\
    <rebuild>        <clean> <all>\n\
    <gdb>            build executable compatible with debugger\n\
    <gdb_rebuild>    <clean> <gdb>\n\
\n\
 Default target: <$(.DEFAULT_GOAL)>\n\
\n\
 Dependancies:   $(deps)\n\
\n"
