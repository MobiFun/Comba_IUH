# C++ to object file compilation rules

OSRTBaseType$(OBJ): $(RTXSRCDIR)/OSRTBaseType.cpp $(RTXSRCDIR)/OSRTBaseType.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTBaseType.cpp

OSRTContext$(OBJ): $(RTXSRCDIR)/OSRTContext.cpp $(RTXSRCDIR)/OSRTContext.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxCharStr.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTContext.cpp

OSRTCtxtHolder$(OBJ): $(RTXSRCDIR)/OSRTCtxtHolder.cpp $(RTXSRCDIR)/OSRTCtxtHolder.h \
  $(RTXSRCDIR)/OSRTCtxtHolderIF.h $(RTXSRCDIR)/OSRTContext.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTCtxtHolder.cpp

OSRTFileInputStream$(OBJ): $(RTXSRCDIR)/OSRTFileInputStream.cpp \
  $(RTXSRCDIR)/rtxStreamFile.h $(RTXSRCDIR)/rtxStream.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxMemBuf.h \
  $(RTXSRCDIR)/OSRTFileInputStream.h $(RTXSRCDIR)/OSRTInputStream.h \
  $(RTXSRCDIR)/OSRTInputStreamIF.h $(RTXSRCDIR)/OSRTStreamIF.h \
  $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxBigInt.h \
  $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTFileInputStream.cpp

OSRTFileOutputStream$(OBJ): $(RTXSRCDIR)/OSRTFileOutputStream.cpp \
  $(RTXSRCDIR)/rtxStreamFile.h $(RTXSRCDIR)/rtxStream.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxMemBuf.h \
  $(RTXSRCDIR)/OSRTFileOutputStream.h $(RTXSRCDIR)/OSRTOutputStream.h \
  $(RTXSRCDIR)/OSRTOutputStreamIF.h $(RTXSRCDIR)/OSRTStreamIF.h \
  $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxBigInt.h \
  $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTFileOutputStream.cpp

OSRTInputStream$(OBJ): $(RTXSRCDIR)/OSRTInputStream.cpp $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/OSRTInputStream.h \
  $(RTXSRCDIR)/OSRTInputStreamIF.h $(RTXSRCDIR)/OSRTStreamIF.h \
  $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxBigInt.h \
  $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTInputStream.cpp

OSRTMemBuf$(OBJ): $(RTXSRCDIR)/OSRTMemBuf.cpp $(RTXSRCDIR)/OSRTMemBuf.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTMemBuf.cpp

OSRTMemoryInputStream$(OBJ): $(RTXSRCDIR)/OSRTMemoryInputStream.cpp \
  $(RTXSRCDIR)/rtxStreamMemory.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/OSRTMemoryInputStream.h \
  $(RTXSRCDIR)/OSRTInputStream.h $(RTXSRCDIR)/OSRTInputStreamIF.h \
  $(RTXSRCDIR)/OSRTStreamIF.h $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTMemoryInputStream.cpp

OSRTMemoryOutputStream$(OBJ): $(RTXSRCDIR)/OSRTMemoryOutputStream.cpp \
  $(RTXSRCDIR)/rtxStreamMemory.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/OSRTMemoryOutputStream.h \
  $(RTXSRCDIR)/OSRTOutputStream.h $(RTXSRCDIR)/OSRTOutputStreamIF.h \
  $(RTXSRCDIR)/OSRTStreamIF.h $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTMemoryOutputStream.cpp

OSRTMsgBuf$(OBJ): $(RTXSRCDIR)/OSRTMsgBuf.cpp $(RTXSRCDIR)/OSRTMsgBuf.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/OSRTMsgBufIF.h \
  $(RTXSRCDIR)/OSRTMemBuf.h $(RTXSRCDIR)/rtxMemBuf.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTMsgBuf.cpp

OSRTOutputStream$(OBJ): $(RTXSRCDIR)/OSRTOutputStream.cpp $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/OSRTOutputStream.h \
  $(RTXSRCDIR)/OSRTOutputStreamIF.h $(RTXSRCDIR)/OSRTStreamIF.h \
  $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h $(RTXSRCDIR)/rtxBigInt.h \
  $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTOutputStream.cpp

OSRTSocket$(OBJ): $(RTXSRCDIR)/OSRTSocket.cpp $(RTXSRCDIR)/OSRTSocket.h \
  $(RTXSRCDIR)/rtxSocket.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/rtxCommonDefs.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTSocket.cpp

OSRTSocketInputStream$(OBJ): $(RTXSRCDIR)/OSRTSocketInputStream.cpp \
  $(RTXSRCDIR)/rtxStreamSocket.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxSocket.h \
  $(RTXSRCDIR)/OSRTSocketInputStream.h $(RTXSRCDIR)/OSRTSocket.h \
  $(RTXSRCDIR)/OSRTInputStream.h $(RTXSRCDIR)/OSRTInputStreamIF.h \
  $(RTXSRCDIR)/OSRTStreamIF.h $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTSocketInputStream.cpp

OSRTSocketOutputStream$(OBJ): $(RTXSRCDIR)/OSRTSocketOutputStream.cpp \
  $(RTXSRCDIR)/rtxStreamSocket.h $(RTXSRCDIR)/rtxStream.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxCommonDefs.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxSocket.h \
  $(RTXSRCDIR)/OSRTSocketOutputStream.h $(RTXSRCDIR)/OSRTSocket.h \
  $(RTXSRCDIR)/OSRTOutputStream.h $(RTXSRCDIR)/OSRTOutputStreamIF.h \
  $(RTXSRCDIR)/OSRTStreamIF.h $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTSocketOutputStream.cpp

OSRTStream$(OBJ): $(RTXSRCDIR)/OSRTStream.cpp $(RTXSRCDIR)/rtxErrCodes.h \
  $(RTXSRCDIR)/rtxStream.h $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/OSRTStream.h \
  $(RTXSRCDIR)/OSRTCtxtHolder.h $(RTXSRCDIR)/OSRTCtxtHolderIF.h \
  $(RTXSRCDIR)/OSRTContext.h $(RTXSRCDIR)/rtxDiag.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxMemory.h \
  $(RTXSRCDIR)/OSRTStreamIF.h $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxBitString.h $(RTXSRCDIR)/rtxBuffer.h \
  $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxDateTime.h $(RTXSRCDIR)/rtxEnum.h \
  $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h \
  $(RTXSRCDIR)/rtxUTF8.h $(RTXSRCDIR)/rtxUtil.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTStream.cpp

OSRTString$(OBJ): $(RTXSRCDIR)/OSRTString.cpp $(RTXSRCDIR)/OSRTString.h \
  $(RTXSRCDIR)/rtxCommon.h $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/osMacros.h \
  $(RTXSRCDIR)/rtxExternDefs.h $(RTXSRCDIR)/rtxBigInt.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxDList.h $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxBitString.h \
  $(RTXSRCDIR)/rtxBuffer.h $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxDateTime.h \
  $(RTXSRCDIR)/rtxDiag.h $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxEnum.h \
  $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxFile.h \
  $(RTXSRCDIR)/rtxMemory.h $(RTXSRCDIR)/rtxPattern.h $(RTXSRCDIR)/rtxReal.h \
  $(RTXSRCDIR)/rtxUTF8.h $(RTXSRCDIR)/rtxUtil.h $(RTXSRCDIR)/rtxPrint.h \
  $(RTXSRCDIR)/OSRTStringIF.h
	$(CCC) $(RTXCCFLAGS) -c $(IPATHS) $(RTXSRCDIR)/OSRTString.cpp
