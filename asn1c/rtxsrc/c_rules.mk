# C to object file compilation rules

rtxArrayList$(OBJ): $(RTXSRCDIR)/rtxArrayList.c $(RTXSRCDIR)/rtxArrayList.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/osMacros.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxArrayList.c

rtxBase64$(OBJ): $(RTXSRCDIR)/rtxBase64.c $(RTXSRCDIR)/rtxBase64.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxBase64.c

rtxBigInt$(OBJ): $(RTXSRCDIR)/rtxBigInt.c $(RTXSRCDIR)/rtxBigInt.hh \
  $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxBigInt.c

rtxBigIntArithmetic$(OBJ): $(RTXSRCDIR)/rtxBigIntArithmetic.c \
  $(RTXSRCDIR)/rtxBigInt.hh $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxBigIntArithmetic.c

rtxBigIntCommon$(OBJ): $(RTXSRCDIR)/rtxBigIntCommon.c $(RTXSRCDIR)/rtxBigInt.hh \
  $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxBigIntCommon.c

rtxBitDecode$(OBJ): $(RTXSRCDIR)/rtxBitDecode.c $(RTXSRCDIR)/rtxBitDecode.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxDiag.h $(RTXSRCDIR)/rtxPrintToStream.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxStreamCtxtBuf.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxBitDecode.c

rtxBitEncode$(OBJ): $(RTXSRCDIR)/rtxBitEncode.c $(RTXSRCDIR)/rtxBitEncode.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxBitEncode.c

rtxBitString$(OBJ): $(RTXSRCDIR)/rtxBitString.c $(RTXSRCDIR)/rtxBitString.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxBitString.c

rtxCharStr$(OBJ): $(RTXSRCDIR)/rtxCharStr.c $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxCharStr.c

rtxCheckBuffer$(OBJ): $(RTXSRCDIR)/rtxCheckBuffer.c $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxStreamDirectBuf.hh $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxCheckBuffer.c

rtxContext$(OBJ): $(RTXSRCDIR)/rtxContext.c $(RTXSRCDIR)/rtxCommon.hh \
  $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxBitString.h \
  $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxDateTime.h \
  $(RTXSRCDIR)/rtxDiag.h $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h \
  $(RTXSRCDIR)/rtxUTF8.h $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/rtxContext.hh \
  $(RTXSRCDIR)/rtxStream.h $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxContext.c

rtxCopyAsciiText$(OBJ): $(RTXSRCDIR)/rtxCopyAsciiText.c $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxCopyAsciiText.c

rtxCopyUTF8Text$(OBJ): $(RTXSRCDIR)/rtxCopyUTF8Text.c $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxCopyUTF8Text.c

rtxDList$(OBJ): $(RTXSRCDIR)/rtxDList.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxContext.hh $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDList.c

rtxDateTime$(OBJ): $(RTXSRCDIR)/rtxDateTime.c $(RTXSRCDIR)/rtxDateTime.hh \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDateTime.c

rtxDateTimeCompare$(OBJ): $(RTXSRCDIR)/rtxDateTimeCompare.c \
  $(RTXSRCDIR)/rtxDateTime.hh $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDateTimeCompare.c

rtxDateTimeCompare2$(OBJ): $(RTXSRCDIR)/rtxDateTimeCompare2.c \
  $(RTXSRCDIR)/rtxDateTime.hh $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDateTimeCompare2.c

rtxDateTimeParse$(OBJ): $(RTXSRCDIR)/rtxDateTimeParse.c $(RTXSRCDIR)/rtxDateTime.hh \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDateTimeParse.c

rtxDateTimeParseCommon$(OBJ): $(RTXSRCDIR)/rtxDateTimeParseCommon.c \
  $(RTXSRCDIR)/rtxDateTime.hh $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDateTimeParseCommon.c

rtxDateTimePrint$(OBJ): $(RTXSRCDIR)/rtxDateTimePrint.c $(RTXSRCDIR)/rtxDateTime.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxPrint.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDateTimePrint.c

rtxDateTimeToString$(OBJ): $(RTXSRCDIR)/rtxDateTimeToString.c \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxDateTime.hh \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h \
  $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDateTimeToString.c

rtxDateTimeToStringCommon$(OBJ): $(RTXSRCDIR)/rtxDateTimeToStringCommon.c \
  $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxDateTime.hh \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDateTimeToStringCommon.c

rtxDatesParse$(OBJ): $(RTXSRCDIR)/rtxDatesParse.c $(RTXSRCDIR)/rtxDateTime.hh \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDatesParse.c

rtxDatesPrint$(OBJ): $(RTXSRCDIR)/rtxDatesPrint.c $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxPrint.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDatesPrint.c

rtxDatesToString$(OBJ): $(RTXSRCDIR)/rtxDatesToString.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxDateTime.hh \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDatesToString.c

rtxDecimalHelper$(OBJ): $(RTXSRCDIR)/rtxDecimalHelper.c $(RTXSRCDIR)/rtxDecimal.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDecimalHelper.c

rtxDiag$(OBJ): $(RTXSRCDIR)/rtxDiag.c $(RTXSRCDIR)/rtxDiag.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxPrintToStream.h \
  $(RTXSRCDIR)/rtxUnicode.h $(RTXSRCDIR)/rtxPrint.h $(RTXSRCDIR)/rtxPrintStream.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDiag.c

rtxDiagBitTrace$(OBJ): $(RTXSRCDIR)/rtxDiagBitTrace.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxDiagBitTrace.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxSList.h $(RTXSRCDIR)/rtxPrintToStream.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxStream.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDiagBitTrace.c

rtxDiagBitTraceHTML$(OBJ): $(RTXSRCDIR)/rtxDiagBitTraceHTML.c \
  $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxDiagBitTrace.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxSList.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPrint.h $(RTXSRCDIR)/rtxPrintStream.h $(RTXSRCDIR)/rtxStream.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDiagBitTraceHTML.c

rtxDiagBitTracePrint$(OBJ): $(RTXSRCDIR)/rtxDiagBitTracePrint.c \
  $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxDiagBitTrace.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxSList.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPrint.h $(RTXSRCDIR)/rtxPrintStream.h $(RTXSRCDIR)/rtxStream.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDiagBitTracePrint.c

rtxDuration$(OBJ): $(RTXSRCDIR)/rtxDuration.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxCtype.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDuration.c

rtxDynBitSet$(OBJ): $(RTXSRCDIR)/rtxDynBitSet.c $(RTXSRCDIR)/rtxDynBitSet.h \
  $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDynBitSet.c

rtxDynPtrArray$(OBJ): $(RTXSRCDIR)/rtxDynPtrArray.c $(RTXSRCDIR)/rtxDynPtrArray.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxDynPtrArray.c

rtxError$(OBJ): $(RTXSRCDIR)/rtxError.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxUnicode.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxError.c

rtxFile$(OBJ): $(RTXSRCDIR)/rtxFile.c $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxFile.c

rtxFloat$(OBJ): $(RTXSRCDIR)/rtxFloat.c $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxFloat.h $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxBigInt.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxFloat.c

rtxHashMap$(OBJ): $(RTXSRCDIR)/rtxHashMap.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxHashMap.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxHashMap.c

rtxHashMapStr2Int$(OBJ): $(RTXSRCDIR)/rtxHashMapStr2Int.c \
  $(RTXSRCDIR)/rtxHashMapStr2Int.h $(RTXSRCDIR)/rtxHashMap.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxHashMap.c $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxHashMapStr2Int.c

rtxHashMapStr2UInt$(OBJ): $(RTXSRCDIR)/rtxHashMapStr2UInt.c \
  $(RTXSRCDIR)/rtxHashMapStr2UInt.h $(RTXSRCDIR)/rtxHashMap.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxHashMap.c $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxHashMapStr2UInt.c

rtxHexCharsToBin$(OBJ): $(RTXSRCDIR)/rtxHexCharsToBin.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxHexCharsToBin.c

rtxHexDump$(OBJ): $(RTXSRCDIR)/rtxHexDump.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxPrint.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxHexDump.c

rtxInt64ToCharStr$(OBJ): $(RTXSRCDIR)/rtxInt64ToCharStr.c \
  $(RTXSRCDIR)/rtxIntToCharStr.c $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxInt64ToCharStr.c

rtxIntToCharStr$(OBJ): $(RTXSRCDIR)/rtxIntToCharStr.c $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxIntToCharStr.c

rtxLookupEnum$(OBJ): $(RTXSRCDIR)/rtxLookupEnum.c $(RTXSRCDIR)/rtxEnum.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxLookupEnum.c

rtxMemBuf$(OBJ): $(RTXSRCDIR)/rtxMemBuf.c $(RTXSRCDIR)/rtxCtype.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxMemBuf.c

rtxMemDefs$(OBJ): $(RTXSRCDIR)/rtxMemDefs.c $(RTXSRCDIR)/rtxMemHeap.hh \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxMemDefs.c

rtxMemFreeOpenSeqExt$(OBJ): $(RTXSRCDIR)/rtxMemFreeOpenSeqExt.c \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxMemFreeOpenSeqExt.c

rtxMemFuncs$(OBJ): $(RTXSRCDIR)/rtxMemFuncs.c $(RTXSRCDIR)/rtxMemHeap.hh \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxMemFuncs.c

rtxMemHeap$(OBJ): $(RTXSRCDIR)/rtxMemHeap.c $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemHeap.hh $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxMemHeap.c

rtxMemHeapCreate$(OBJ): $(RTXSRCDIR)/rtxMemHeapCreate.c $(RTXSRCDIR)/rtxMemHeap.hh \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxMemHeapCreate.c

rtxMemory$(OBJ): $(RTXSRCDIR)/rtxMemory.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxMemory.c

rtxPattern$(OBJ): $(RTXSRCDIR)/rtxPattern.c $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxDiag.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxRegExp.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxPattern.c

rtxPrint$(OBJ): $(RTXSRCDIR)/rtxPrint.c $(RTXSRCDIR)/rtxCtype.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxPrint.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/osMacros.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxPrint.c

rtxPrintStream$(OBJ): $(RTXSRCDIR)/rtxPrintStream.c $(RTXSRCDIR)/rtxPrintStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxPrintStream.c

rtxPrintToStream$(OBJ): $(RTXSRCDIR)/rtxPrintToStream.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxPrintStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxPrintToStream.c

rtxRealHelper$(OBJ): $(RTXSRCDIR)/rtxRealHelper.c $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxRealHelper.c

rtxRegExp$(OBJ): $(RTXSRCDIR)/rtxRegExp.c $(RTXSRCDIR)/rtxRegExp.hh \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxRegExp.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxUnicode.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxRegExp.c

rtxRegExp2$(OBJ): $(RTXSRCDIR)/rtxRegExp2.c $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxRegExp.hh \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxRegExp.h $(RTXSRCDIR)/rtxUnicode.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxRegExp2.c

rtxRegExpPrint$(OBJ): $(RTXSRCDIR)/rtxRegExpPrint.c $(RTXSRCDIR)/rtxRegExp.hh \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxRegExp.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxUnicode.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxRegExpPrint.c

rtxSList$(OBJ): $(RTXSRCDIR)/rtxSList.c $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxSList.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxSList.c

rtxScalarDList$(OBJ): $(RTXSRCDIR)/rtxScalarDList.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxScalarDList.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxScalarDList.c

rtxSocket$(OBJ): $(RTXSRCDIR)/rtxSocket.c $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxSocket.h $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxSocket.c

rtxStack$(OBJ): $(RTXSRCDIR)/rtxStack.c $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxStack.h $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStack.c

rtxStream$(OBJ): $(RTXSRCDIR)/rtxStream.c $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxContext.hh
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStream.c

rtxStreamBuffered$(OBJ): $(RTXSRCDIR)/rtxStreamBuffered.c \
  $(RTXSRCDIR)/rtxStreamBuffered.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxMemory.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStreamBuffered.c

rtxStreamCtxtBuf$(OBJ): $(RTXSRCDIR)/rtxStreamCtxtBuf.c $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxStreamCtxtBuf.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStreamCtxtBuf.c

rtxStreamDirectBuf$(OBJ): $(RTXSRCDIR)/rtxStreamDirectBuf.c $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxStreamDirectBuf.hh $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStreamDirectBuf.c

rtxStreamFile$(OBJ): $(RTXSRCDIR)/rtxStreamFile.c $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxStreamFile.h \
  $(RTXSRCDIR)/rtxStream.h $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStreamFile.c

rtxStreamMemory$(OBJ): $(RTXSRCDIR)/rtxStreamMemory.c $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxStreamMemory.h $(RTXSRCDIR)/rtxStream.h $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStreamMemory.c

rtxStreamRelease$(OBJ): $(RTXSRCDIR)/rtxStreamRelease.c $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStreamRelease.c

rtxStreamSocket$(OBJ): $(RTXSRCDIR)/rtxStreamSocket.c $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxSocket.h \
  $(RTXSRCDIR)/rtxStreamSocket.h $(RTXSRCDIR)/rtxStream.h $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStreamSocket.c

rtxStreamZlib$(OBJ): $(RTXSRCDIR)/rtxStreamZlib.c $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxStreamZlib.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxStreamZlib.c

rtxTestNumericEnum$(OBJ): $(RTXSRCDIR)/rtxTestNumericEnum.c $(RTXSRCDIR)/rtxEnum.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxTestNumericEnum.c

rtxTestNumericEnum64$(OBJ): $(RTXSRCDIR)/rtxTestNumericEnum64.c \
  $(RTXSRCDIR)/rtxTestNumericEnum.c $(RTXSRCDIR)/rtxEnum.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxTestNumericEnum64.c

rtxTestNumericEnumU32$(OBJ): $(RTXSRCDIR)/rtxTestNumericEnumU32.c \
  $(RTXSRCDIR)/rtxTestNumericEnum.c $(RTXSRCDIR)/rtxEnum.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxTestNumericEnumU32.c

rtxTestNumericEnumU64$(OBJ): $(RTXSRCDIR)/rtxTestNumericEnumU64.c \
  $(RTXSRCDIR)/rtxTestNumericEnum.c $(RTXSRCDIR)/rtxEnum.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxTestNumericEnumU64.c

rtxToken$(OBJ): $(RTXSRCDIR)/rtxToken.c $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxToken.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxToken.c

rtxTokenConst$(OBJ): $(RTXSRCDIR)/rtxTokenConst.c $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxTokenConst.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxTokenConst.c

rtxUInt64ToCharStr$(OBJ): $(RTXSRCDIR)/rtxUInt64ToCharStr.c \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxIntToCharStr.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUInt64ToCharStr.c

rtxUIntToCharStr$(OBJ): $(RTXSRCDIR)/rtxUIntToCharStr.c $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxIntToCharStr.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUIntToCharStr.c

rtxUTF8$(OBJ): $(RTXSRCDIR)/rtxUTF8.c $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8.c

rtxUTF8StrToBool$(OBJ): $(RTXSRCDIR)/rtxUTF8StrToBool.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8StrToBool.c

rtxUTF8StrToDouble$(OBJ): $(RTXSRCDIR)/rtxUTF8StrToDouble.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxCtype.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxReal.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8StrToDouble.c

rtxUTF8StrToDynHexStr$(OBJ): $(RTXSRCDIR)/rtxUTF8StrToDynHexStr.c \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8StrToDynHexStr.c

rtxUTF8StrToInt$(OBJ): $(RTXSRCDIR)/rtxUTF8StrToInt.c $(RTXSRCDIR)/rtxCtype.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxUTF8.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8StrToInt.c

rtxUTF8StrToInt64$(OBJ): $(RTXSRCDIR)/rtxUTF8StrToInt64.c \
  $(RTXSRCDIR)/rtxUTF8StrToInt.c $(RTXSRCDIR)/rtxCtype.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxUTF8.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8StrToInt64.c

rtxUTF8StrToNamedBits$(OBJ): $(RTXSRCDIR)/rtxUTF8StrToNamedBits.c \
  $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8StrToNamedBits.c

rtxUTF8StrToUInt$(OBJ): $(RTXSRCDIR)/rtxUTF8StrToUInt.c \
  $(RTXSRCDIR)/rtxUTF8StrToInt.c $(RTXSRCDIR)/rtxCtype.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxUTF8.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8StrToUInt.c

rtxUTF8StrToUInt64$(OBJ): $(RTXSRCDIR)/rtxUTF8StrToUInt64.c \
  $(RTXSRCDIR)/rtxUTF8StrToInt.c $(RTXSRCDIR)/rtxCtype.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxUTF8.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8StrToUInt64.c

rtxUTF8ToDynUniStr$(OBJ): $(RTXSRCDIR)/rtxUTF8ToDynUniStr.c \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUTF8ToDynUniStr.c

rtxUnicode$(OBJ): $(RTXSRCDIR)/rtxUnicode.c $(RTXSRCDIR)/rtxCtype.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxUnicode.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUnicode.c

rtxUtil$(OBJ): $(RTXSRCDIR)/rtxUtil.c $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxUtil.h \
  $(RTXSRCDIR)/rtxExternDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUtil.c

rtxUtil64$(OBJ): $(RTXSRCDIR)/rtxUtil64.c $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/rtxExternDefs.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxUtil64.c

rtxWriteBytes$(OBJ): $(RTXSRCDIR)/rtxWriteBytes.c $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxContext.hh \
  $(RTXSRCDIR)/rtxStreamDirectBuf.hh $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxMemBuf.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxWriteBytes.c

rtxXmlQName$(OBJ): $(RTXSRCDIR)/rtxXmlQName.c $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxXmlQName.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxXmlQName.c

rtxXmlStr$(OBJ): $(RTXSRCDIR)/rtxXmlStr.c $(RTXSRCDIR)/rtxXmlStr.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxUTF8.h
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/rtxXmlStr.c

wceAddon$(OBJ): $(RTXSRCDIR)/wceAddon.c
	$(CC) $(RTXCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/wceAddon.c
