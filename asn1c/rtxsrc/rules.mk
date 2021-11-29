rtxArrayList$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxArrayList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxArrayList.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxArrayList.c

rtxBase64$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxBase64.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBase64.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxBase64.c

rtxBigIntArithmetic$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxBigIntArithmetic.c \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxBigIntArithmetic.c

rtxBigInt$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxBigInt.c

rtxBigIntCommon$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigIntCommon.c \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxBigIntCommon.c

rtxBitDecode$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxStreamCtxtBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxBitDecode.c \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitDecode.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxBitDecode.c

rtxBitEncode$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxBitEncode.c \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxBitEncode.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxBitEncode.c

rtxBitString$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxBitString.c

rtxCharStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxCharStr.c

rtxCheckBuffer$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamDirectBuf.hh \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCheckBuffer.c \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxCheckBuffer.c

rtxContext$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxContext.c \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.hh \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.hh \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxContext.c

rtxCopyAsciiText$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCopyAsciiText.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxCopyAsciiText.c

rtxCopyUTF8Text$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCopyUTF8Text.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxCopyUTF8Text.c

rtxDatesParse$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxDatesParse.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDatesParse.c

rtxDatesPrint$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxDatesPrint.c \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDatesPrint.c

rtxDatesToString$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDatesToString.c \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDatesToString.c

rtxDateTime$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDateTime.c

rtxDateTimeCompare2$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTimeCompare2.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDateTimeCompare2.c

rtxDateTimeCompare$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTimeCompare.c \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDateTimeCompare.c

rtxDateTimeParse$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTimeParse.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDateTimeParse.c

rtxDateTimeParseCommon$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTimeParseCommon.c \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDateTimeParseCommon.c

rtxDateTimePrint$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTimePrint.c \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDateTimePrint.c

rtxDateTimeToString$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTimeToString.c \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDateTimeToString.c

rtxDateTimeToStringCommon$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.hh \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTimeToStringCommon.c \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDateTimeToStringCommon.c

rtxDecimalHelper$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxDecimal.h \
    $(OSROOTDIR)/rtxsrc/rtxDecimalHelper.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDecimalHelper.c

rtxDiagBitTrace$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxDiagBitTrace.h \
    $(OSROOTDIR)/rtxsrc/rtxDiagBitTrace.c \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDiagBitTrace.c

rtxDiagBitTraceHTML$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiagBitTrace.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxDiagBitTraceHTML.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDiagBitTraceHTML.c

rtxDiagBitTracePrint$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxDiagBitTracePrint.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiagBitTrace.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDiagBitTracePrint.c

rtxDiag$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintStream.h \
    $(OSROOTDIR)/rtxsrc/rtxUnicode.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDiag.c

rtxDList$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDList.c

rtxDuration$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDuration.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDuration.c

rtxDynBitSet$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDynBitSet.c \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxDynBitSet.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDynBitSet.c

rtxDynPtrArray$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDynPtrArray.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxDynPtrArray.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxDynPtrArray.c

rtxError$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxError.c \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUnicode.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxError.c

rtxFile$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxFile.c

rtxFloat$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h \
    $(OSROOTDIR)/rtxsrc/rtxFloat.h \
    $(OSROOTDIR)/rtxsrc/rtxFloat.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxFloat.c

rtxHashMap$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMap.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMap.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxHashMap.c

rtxHashMapStr2Int$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMapStr2Int.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMap.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMap.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMapStr2Int.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxHashMapStr2Int.c

rtxHashMapStr2UInt$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMap.c \
    $(OSROOTDIR)/rtxsrc/rtxHashMapStr2UInt.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMap.h \
    $(OSROOTDIR)/rtxsrc/rtxHashMapStr2UInt.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxHashMapStr2UInt.c

rtxHexCharsToBin$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxHexCharsToBin.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxHexCharsToBin.c

rtxHexDump$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxHexDump.c \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxHexDump.c

rtxInt64ToCharStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxIntToCharStr.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxInt64ToCharStr.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxInt64ToCharStr.c

rtxIntToCharStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxIntToCharStr.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxIntToCharStr.c

rtxLookupEnum$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxLookupEnum.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxLookupEnum.c

rtxMemBuf$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxMemBuf.c

rtxMemDefs$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemDefs.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeap.hh \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxMemDefs.c

rtxMemFreeOpenSeqExt$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxMemFreeOpenSeqExt.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxMemFreeOpenSeqExt.c

rtxMemFuncs$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeap.hh \
    $(OSROOTDIR)/rtxsrc/rtxMemFuncs.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxMemFuncs.c

rtxMemHeap$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeap.hh \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeap.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxMemHeap.c

rtxMemHeapCreate$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeapCreate.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeap.hh \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxMemHeapCreate.c

rtxMemory$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemHeap.hh \
    $(OSROOTDIR)/rtxsrc/rtxMemory.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxMemory.c

rtxPattern$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxRegExp.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.c \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxPattern.c

rtxPrint$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.c \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxPrint.c

rtxPrintStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintStream.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxPrintStream.c

rtxPrintToStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxPrintToStream.c

rtxRealHelper$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxRealHelper.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxRealHelper.c

rtxRegExp2$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxRegExp.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUnicode.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxRegExp.hh \
    $(OSROOTDIR)/rtxsrc/rtxRegExp2.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxRegExp2.c

rtxRegExp$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxRegExp.h \
    $(OSROOTDIR)/rtxsrc/rtxRegExp.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUnicode.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxRegExp.hh \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxRegExp.c

rtxRegExpPrint$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxRegExp.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUnicode.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxRegExp.hh \
    $(OSROOTDIR)/rtxsrc/rtxRegExpPrint.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxRegExpPrint.c

rtxScalarDList$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxScalarDList.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxScalarDList.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxScalarDList.c

rtxSList$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxSList.c \
    $(OSROOTDIR)/rtxsrc/rtxSList.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxSList.c

rtxSocket$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxSocket.c \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxSocket.c

rtxStack$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.h \
    $(OSROOTDIR)/rtxsrc/rtxStack.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStack.c

rtxStreamBuffered$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamBuffered.c \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamBuffered.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStreamBuffered.c

rtxStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStream.c

rtxStreamCtxtBuf$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxStreamCtxtBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamFile.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamCtxtBuf.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStreamCtxtBuf.c

rtxStreamDirectBuf$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamDirectBuf.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamDirectBuf.hh \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStreamDirectBuf.c

rtxStreamFile$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamFile.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamFile.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStreamFile.c

rtxStreamMemory$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamMemory.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStreamMemory.c

rtxStreamRelease$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamRelease.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStreamRelease.c

rtxStreamSocket$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamSocket.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStreamSocket.c

rtxStreamZlib$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamZlib.c \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxStreamZlib.c

rtxTestNumericEnum64$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxTestNumericEnum64.c \
    $(OSROOTDIR)/rtxsrc/rtxTestNumericEnum.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxTestNumericEnum64.c

rtxTestNumericEnum$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxTestNumericEnum.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxTestNumericEnum.c

rtxTestNumericEnumU32$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxTestNumericEnumU32.c \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxTestNumericEnum.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxTestNumericEnumU32.c

rtxTestNumericEnumU64$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxTestNumericEnumU64.c \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxTestNumericEnum.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxTestNumericEnumU64.c

rtxToken$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxToken.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxToken.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxToken.c

rtxTokenConst$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxTokenConst.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxTokenConst.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxTokenConst.c

rtxUInt64ToCharStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxUInt64ToCharStr.c \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxIntToCharStr.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUInt64ToCharStr.c

rtxUIntToCharStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxUIntToCharStr.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxIntToCharStr.c \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUIntToCharStr.c

rtxUnicode$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUnicode.c \
    $(OSROOTDIR)/rtxsrc/rtxUnicode.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUnicode.c

rtxUTF8$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8.c

rtxUTF8StrToBool$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToBool.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8StrToBool.c

rtxUTF8StrToDouble$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToDouble.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8StrToDouble.c

rtxUTF8StrToDynHexStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToDynHexStr.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8StrToDynHexStr.c

rtxUTF8StrToInt64$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToInt.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToInt64.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8StrToInt64.c

rtxUTF8StrToInt$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToInt.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8StrToInt.c

rtxUTF8StrToNamedBits$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToNamedBits.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8StrToNamedBits.c

rtxUTF8StrToUInt64$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToUInt64.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToInt.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8StrToUInt64.c

rtxUTF8StrToUInt$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCtype.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToInt.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8StrToUInt.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8StrToUInt.c

rtxUTF8ToDynUniStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8ToDynUniStr.c \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUTF8ToDynUniStr.c

rtxUtil64$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxUtil64.c \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUtil64.c

rtxUtil$(OBJ): \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxUtil.c

rtxWriteBytes$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxWriteBytes.c \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamDirectBuf.hh \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxWriteBytes.c

rtxXmlQName$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxXmlQName.c \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxXmlQName.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxXmlQName.c

rtxXmlStr$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxXmlStr.h \
    $(OSROOTDIR)/rtxsrc/rtxXmlStr.c \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/rtxXmlStr.c

wceAddon$(OBJ): \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/wceAddon.c \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/wceAddon.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/wceAddon.c

OSRTBaseType$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/OSRTBaseType.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/OSRTBaseType.cpp \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTBaseType.cpp

OSRTContext$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.cpp \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTContext.cpp

OSRTCtxtHolder$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.cpp \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.cpp

OSRTFileInputStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamFile.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/OSRTFileInputStream.cpp \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTFileInputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTFileInputStream.cpp

OSRTFileOutputStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamFile.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/OSRTFileOutputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/OSRTFileOutputStream.cpp \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTFileOutputStream.cpp

OSRTInputStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStreamIF.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStream.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStream.cpp \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTInputStream.cpp

OSRTMemBuf$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/OSRTMemBuf.cpp
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTMemBuf.cpp

OSRTMemoryInputStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStreamIF.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/OSRTMemoryInputStream.cpp \
    $(OSROOTDIR)/rtxsrc/OSRTMemoryInputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTMemoryInputStream.cpp

OSRTMemoryOutputStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/OSRTMemoryOutputStream.cpp \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/OSRTMemoryOutputStream.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTMemoryOutputStream.cpp

OSRTMsgBuf$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/OSRTMsgBuf.h \
    $(OSROOTDIR)/rtxsrc/OSRTMsgBuf.cpp \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/OSRTMsgBufIF.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTMsgBuf.cpp

OSRTOutputStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStream.cpp \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTOutputStream.cpp

OSRTSocket$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/OSRTSocket.cpp \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/OSRTSocket.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTSocket.cpp

OSRTSocketInputStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStreamIF.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/OSRTInputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/OSRTSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/OSRTSocketInputStream.h \
    $(OSROOTDIR)/rtxsrc/OSRTSocketInputStream.cpp \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTSocketInputStream.cpp

OSRTSocketOutputStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/OSRTSocketOutputStream.h \
    $(OSROOTDIR)/rtxsrc/OSRTSocketOutputStream.cpp \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxStreamSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxSocket.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/OSRTSocket.h \
    $(OSROOTDIR)/rtxsrc/OSRTOutputStream.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTSocketOutputStream.cpp

OSRTStream$(OBJ): \
    $(OSROOTDIR)/rtxsrc/OSRTStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/OSRTStream.cpp \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxMemBuf.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxStream.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/OSRTContext.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolderIF.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/OSRTStreamIF.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/OSRTCtxtHolder.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTStream.cpp

OSRTString$(OBJ): \
    $(OSROOTDIR)/rtxsrc/rtxDList.h \
    $(OSROOTDIR)/rtxsrc/OSRTString.cpp \
    $(OSROOTDIR)/rtxsrc/rtxCommonDefs.h \
    $(OSROOTDIR)/rtxsrc/osMacros.h \
    $(OSROOTDIR)/rtxsrc/rtxMemory.h \
    $(OSROOTDIR)/rtxsrc/rtxBigInt.h \
    $(OSROOTDIR)/rtxsrc/osSysTypes.h \
    $(OSROOTDIR)/rtxsrc/rtxCommon.h \
    $(OSROOTDIR)/rtxsrc/rtxError.h \
    $(OSROOTDIR)/rtxsrc/rtxPattern.h \
    $(OSROOTDIR)/rtxsrc/OSRTStringIF.h \
    $(OSROOTDIR)/rtxsrc/rtxContext.h \
    $(OSROOTDIR)/rtxsrc/rtxFile.h \
    $(OSROOTDIR)/rtxsrc/rtxReal.h \
    $(OSROOTDIR)/rtxsrc/rtxDiag.h \
    $(OSROOTDIR)/rtxsrc/rtxBitString.h \
    $(OSROOTDIR)/rtxsrc/rtxExternDefs.h \
    $(OSROOTDIR)/rtxsrc/rtxPrintToStream.h \
    $(OSROOTDIR)/rtxsrc/rtxCharStr.h \
    $(OSROOTDIR)/rtxsrc/rtxErrCodes.h \
    $(OSROOTDIR)/rtxsrc/OSRTString.h \
    $(OSROOTDIR)/rtxsrc/rtxUtil.h \
    $(OSROOTDIR)/rtxsrc/rtxPrint.h \
    $(OSROOTDIR)/rtxsrc/rtxEnum.h \
    $(OSROOTDIR)/rtxsrc/rtxDateTime.h \
    $(OSROOTDIR)/rtxsrc/rtxUTF8.h \
    $(OSROOTDIR)/rtxsrc/rtxBuffer.h
	$(CCC) $(RTXCCFLAGS) $(RTCPPFLAGS) -c $(IPATHS) $(OSROOTDIR)/rtxsrc/OSRTString.cpp

