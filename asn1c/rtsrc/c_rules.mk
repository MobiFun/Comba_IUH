asn1CEvtHndlr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(RTSRCDIR)/asn1CEvtHndlr.c \
    $(RTSRCDIR)/asn1CEvtHndlr.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/asn1CEvtHndlr.c

rt16BitChars$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(RTSRCDIR)/rt16BitChars.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rt16BitChars.c

rt32BitChars$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(RTSRCDIR)/rt32BitChars.c \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rt32BitChars.c

rtBCD$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/rtBCD.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(RTSRCDIR)/rtBCD.c
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtBCD.c

rtContext$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtsrc/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(RTSRCDIR)/rtContext.c \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintStream.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeap.hh \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtContext.c

rtError$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(RTSRCDIR)/rtError.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtsrc/rtContext.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtError.c

rtGetLibInfo$(OBJ): \
    $(RTSRCDIR)/asn1version.h \
    $(RTSRCDIR)/rtGetLibInfo.c
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtGetLibInfo.c

rtHelper$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(RTSRCDIR)/rtHelper.c \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(RTSRCDIR)/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(RTSRCDIR)/asn1compat.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtHelper.c

rtInfinity$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(RTSRCDIR)/rtInfinity.c \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(RTSRCDIR)/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtInfinity.c

rtMakeGeneralizedTime$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(RTSRCDIR)/rtMakeGeneralizedTime.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtsrc/asn1intl.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtMakeGeneralizedTime.c

rtMakeUTCTime$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(RTSRCDIR)/rtMakeUTCTime.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtsrc/asn1intl.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtMakeUTCTime.c

rtMemNucleusDefs$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(RTSRCDIR)/rtMemNucleusDefs.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeap.hh
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtMemNucleusDefs.c

rtNewContext$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(RTSRCDIR)/rtNewContext.c \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtNewContext.c

rtOID$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(RTSRCDIR)/rtOID.c \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtOID.c

rtParseGeneralizedTime$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtsrc/asn1intl.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(RTSRCDIR)/rtParseGeneralizedTime.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtParseGeneralizedTime.c

rtParseUTCTime$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtsrc/asn1intl.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(RTSRCDIR)/rtParseUTCTime.c \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtParseUTCTime.c

rtPrint$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(RTSRCDIR)/rtPrint.c \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtsrc/rtPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtPrint.c

rtPrintToStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(RTSRCDIR)/rtPrintToStream.c \
    $(OSROOTDIR)/rtsrc/rtPrintToStream.h \
    $(OSROOTDIR)/rtsrc/rtPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtPrintToStream.c

rtPrintToString$(OBJ): \
    $(OSROOTDIR)/rtsrc/rtPrintToString.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(RTSRCDIR)/rtPrintToString.c \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtPrintToString.c

rtReadNextByte$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(RTSRCDIR)/rtReadNextByte.c \
    $(RTSRCDIR)/asn1type.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(RTSRCDIR)/asn1compat.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtReadNextByte.c

rtRealHelper$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(RTSRCDIR)/rtRealHelper.c \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(RTSRCDIR)/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(RTSRCDIR)/asn1compat.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtRealHelper.c

rtSetLocalTime$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(RTSRCDIR)/rtSetLocalTime.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtsrc/checklic.hhh \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(RTSRCDIR)/asn1intl.h \
    $(RTSRCDIR)/rt_common.hh \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtSetLocalTime.c

rtStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1compat.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamFile.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxSocket.h \
    $(RTSRCDIR)/rtStream.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(RTSRCDIR)/rtStream.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamMemory.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtStream.c

rtTable$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(RTSRCDIR)/rtTable.c \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtsrc/rtTable.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtTable.c

rtUTF8StrToDynBitStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(RTSRCDIR)/rtUTF8StrToDynBitStr.c \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtUTF8StrToDynBitStr.c

rtValidateStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(RTSRCDIR)/asn1CharSet.h \
    $(RTSRCDIR)/rtValidateStr.c \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(RTSRCDIR)/asn1type.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtValidateStr.c

rtbench$(OBJ): \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/wceAddon.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(RTSRCDIR)/rtbench.h \
    $(RTSRCDIR)/rtbench.c
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtbench.c

rtcompare$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(RTSRCDIR)/rtCompare.h \
    $(RTSRCDIR)/rtPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(RTSRCDIR)/rtconv.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(RTSRCDIR)/rtPrintToString.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(RTSRCDIR)/asn1type.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(RTSRCDIR)/rtcompare.c
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtcompare.c

rtconv$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(RTSRCDIR)/rtconv.c \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtsrc/rtconv.h \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtconv.c

rtcopy$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtsrc/asn1version.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtsrc/asn1ErrCodes.h \
    $(OSROOTDIR)/rtsrc/rtCopy.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtsrc/asn1type.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtsrc/rtExternDefs.h \
    $(OSROOTDIR)/rtsrc/asn1tag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(RTSRCDIR)/rtcopy.c \
    $(OSROOTDIR)/rtsrc/rtContext.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtcopy.c

rtevalstub$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(RTSRCDIR)/checklic.hhh \
    $(RTSRCDIR)/rtevalstub.c
	$(CC) $(RTCFLAGS) -c -I$(OSROOTDIR) $(IPATHS_) $(RTSRCDIR)/rtevalstub.c

