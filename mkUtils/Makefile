# ---------------------------------------------------------------------
#
#               Esempio di Makefile che usa Make--
#
# ---------------------------------------------------------------------


.DEFAULT_GOAL := lib

##############################

FW := $(HOME)/FRAMEWORK



MAKEFLAGS := -r
include   $(FW)/utils/Make--

#
# La piattaforma (linux o nto) viene ricavata automaticamente
# in base al sistema operativo, a meno che non sia gia' impostata
# dall'esterno
#
export Platform := $(or $(Platform),$(__make_os))
export CFLAGS 	+= -DfwPlatform_$(Platform)


ifeq (,$(filter $(Platform),linux nto))
$(error Platform must be 'linux' or 'nto')
endif


__make_os := $(Platform)


export CFLAGS += -Dostype_$(__make_os)=1

##############################

fw      := $(FW)/fw-3
fwsrc   := $(fw)/fwsrc
fwlib   := $(fw)/fwlib.$(__make_os)
libfw   := $(fwlib)/libfw.a

libtrc  := $(fw)/libtrc/libtrc.a

tcl   	:= $(or $(Tcl),/usr/local/tcl)
tclinc 	:= $(tcl)/include
tcllib	:= $(tcl)/lib

tclinc_ := # $(tclinc)	# se serve
tcllib_ := # $(tcllib)	# se serve

xlibs_linux :=
xlibs_nto   := $(libtrc)

xlibs := $(xlibs_$(__make_os)) $(tcllib_)

##############################

lib     := ./_lib.a
deps    := ./_deps

dirs	:= .

srcs    := $(wildcard $(dirs:%=%/*.c) $(dirs:%=%/*.cc))
incs    := $(dirs) $(fwlib) $(tclinc_)

special := $(srcs:.c=.s) $(srcs:.c=.lst) $(srcs:.c=.o) $(srcs:.c=.)
special := $(notdir $(special))


quiet := @:


###########################################################
# Pulizia
###########################################################

.PHONY: clean semiclean


clean:  semiclean
		$(call __makeExec, rm -rf,_*)

semiclean:
		$(call __makeExec, rm -rf,$(special) $(lib) $(deps))



###########################################################
# La libreria del framework
###########################################################

.PHONY: libfw

libfw: ; @$(MAKE) -C$(fwsrc) --no-print-directory all

$(libfw): libfw



###########################################################
# La libreria utente
###########################################################

.PHONY: all lib rebuild


rebuild:   clean  all

all lib:   $(lib)

$(lib):    libfw
	$(call __makeLib,$(lib),$(srcs),$(incs),$(deps))



###########################################################
# Creazione dell'eseguibile: _nome (inizia con undescore)
###########################################################

libs := $(lib) $(libfw) $(xlibs) $(__make_syslibs)

_%:     $(lib) $(libfw)
		$(CC) $(call __makeMain,$@) $(libs) -o$@



###########################################################
# I target speciali: nome.s  nome.lst  nome.o  nome.
###########################################################

.PHONY: $(special)

$(special): libfw
	$(call __makeTgt,$@,$(srcs),$(incs))



###########################################################
# help
###########################################################

.PHONY:     help h

help h: ; @echo -en "\
\n\
    <h>,<help>   this help\n\
\n\
    <lib>        <libfw> <$(lib)>\n\
    <libfw>      <$(libfw)>\n\
    <fwlib>      <libfw> with full deps check\n\
\n\
    <all>        <fwlib> <lib>\n\
    <rebuild>    <clean> <all>\n\
\n\
    <clean>      <semiclean> and remove _*\n\
    <semiclean>  remove special, deps and <$(lib)>\n\
\n\
 Executable targets:\n\
\n\
    <_file>      file.c  <lib>\n\
\n\
 Special targets:\n\
\n\
    <file>       same as <file.o>\n\
    <file.o>,\n\
    <file.s>,\n\
    <file.lst>   file.c  <libfw>\n\
\n\
 Default target: <$(.DEFAULT_GOAL)>\n\
 Dependancies:   $(deps)\n\
\n"
