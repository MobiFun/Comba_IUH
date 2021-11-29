# Build static run-time libraries

include ../../../fw/Make--
include ../platform.mk--

OSROOTDIR = ..$(PS)..
RTSRCDIR  = $(OSROOTDIR)$(PS)rtsrc
RTXSRCDIR = $(OSROOTDIR)$(PS)rtxsrc
BERSRCDIR = $(OSROOTDIR)$(PS)rtbersrc
PERSRCDIR = $(OSROOTDIR)$(PS)rtpersrc
XERSRCDIR = $(OSROOTDIR)$(PS)rtxersrc
XMLSRCDIR = $(OSROOTDIR)$(PS)rtxmlsrc
ifeq ($(__make_ccver),300)
DESTDIR_linux  = ..$(PS)libgcc3
else
DESTDIR_linux  = ..$(PS)libgcc4
endif
DESTDIR_nto  = ..$(PS)lib_nto

DESTDIR = $(DESTDIR_$(__make_os))

COMFLAGS = $(CVARS_) $(MCFLAGS) $(CDEV_)  -D_NO_LICENSE_CHECK
CFLAGS	 = $(COMFLAGS) $(CFLAGS_)
IPATHS	 = -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(RTXSRCDIR) $(IPATHS_)
LPATHS	 = $(LPATHS_)
XMLIFOBJ = _a$(OBJ)

RTCFLAGS = $(CFLAGS)
RTXCFLAGS = $(CFLAGS)
RTXCCFLAGS = $(CFLAGS)
RTXCPPFLAGS = $(CFLAGS)
BERCFLAGS = $(CFLAGS) -I$(BERSRCDIR)
PERCFLAGS = $(CFLAGS) -I$(PERSRCDIR)
XERCFLAGS = $(CFLAGS) $(XMLDEFS) $(XMLINC) -I$(XERSRCDIR) 
XMLCFLAGS = $(CFLAGS) $(XMLDEFS) -I$(XMLSRCDIR) -I$(LIBXML2INC)

tstm_all: RTCFLAGS += -DTMLOG
tstm_all: all
	@echo "made tstm version"

all : \
$(DESTDIR)$(PS)$(LIBPFX)asn1rt$(A) \
$(DESTDIR)$(PS)$(LIBPFX)asn1ber$(A) \
$(DESTDIR)$(PS)$(LIBPFX)asn1per$(A) \
$(DESTDIR)$(PS)$(LIBPFX)asn1xer$(A) \
$(DESTDIR)$(PS)$(LIBPFX)asn1xml$(A) \
$(DESTDIR)$(PS)rtXmlExpatIF$(XMLIFOBJ) \
$(DESTDIR)$(PS)rtXmlLibxml2IF$(XMLIFOBJ)

include ../../rtsrc/objects.mk
include ../../rtxsrc/objects.mk
include ../../rtxersrc/objects.mk
include ../../rtxmlsrc/objects.mk
include ../../rtxmlsrc/asn1Objects.mk

$(DESTDIR)$(PS)$(LIBPFX)asn1rt$(A) : \
$(OSRT_C_RTOBJECTS) $(ASN1RT_C_OBJECTS) $(STUB_OBJECTS_RT)
	$(LIBCMD) $(OSRT_C_RTOBJECTS) $(ASN1RT_C_OBJECTS) $(STUB_OBJECTS_RT)

$(DESTDIR)$(PS)$(LIBPFX)asn1ber$(A) : \
$(ONLY_BER_C_RTOBJECTS) $(STUB_OBJECTS_BER)
	$(LIBCMD) $(ONLY_BER_C_RTOBJECTS) $(STUB_OBJECTS_BER)

$(DESTDIR)$(PS)$(LIBPFX)asn1per$(A) : \
$(ONLY_PER_C_RTOBJECTS) $(STUB_OBJECTS_PER)
	$(LIBCMD) $(ONLY_PER_C_RTOBJECTS) $(STUB_OBJECTS_PER)

$(DESTDIR)$(PS)$(LIBPFX)asn1xer$(A) : \
$(XER_C_RTOBJECTS) $(STUB_OBJECTS_XER)
	$(LIBCMD) $(XER_C_RTOBJECTS) $(STUB_OBJECTS_XER)


include ../../rtsrc/c_rules.mk
include ../../rtxsrc/c_rules.mk
include ../../rtbersrc/c_rules.mk
include ../../rtpersrc/c_rules.mk
include ../../rtxersrc/c_rules.mk
include ../../rtxmlsrc/c_rules.mk

EXPATINC = $(OSROOTDIR)/expatsrc
CFLAGSIF = -I. -I$(OSROOTDIR) $(IPATHS_) $(CFLAGS) -DXML_STATIC $(OBJOUT)

include ../../rtxmlsrc/cif_rules.mk

clean :
	$(RM) *.c
	$(RM) *$(OBJ) 
	$(RM) *.pdb 
	$(RM) *~ 

realclean :
	$(RM) *.c
	$(RM) *$(OBJ) 
	$(RM) $(SRCDIR)$(PS)*.h 
	$(RM) $(SRCDIR)$(PS)*.c 
	$(RM) $(DESTDIR)$(PS)*$(A) 
	$(RM) $(DESTDIR)$(PS)rtXmlExpatIF$(XMLIFOBJ)
	$(RM) $(DESTDIR)$(PS)rtXmlLibxml2IF$(XMLIFOBJ)
	$(RM) *.pdb 
	$(RM) *~ 

