ASN1RT_C_OBJECTS = \
   asn1CEvtHndlr$(OBJ) \
   rt16BitChars$(OBJ) \
   rt32BitChars$(OBJ) \
   rtBCD$(OBJ) \
   rtcompare$(OBJ) \
   rtContext$(OBJ) \
   rtconv$(OBJ) \
   rtcopy$(OBJ) \
   rtError$(OBJ) \
   rtMakeGeneralizedTime$(OBJ) \
   rtMakeUTCTime$(OBJ) \
   rtNewContext$(OBJ) \
   rtOID$(OBJ) \
   rtParseGeneralizedTime$(OBJ) \
   rtParseUTCTime$(OBJ) \
   rtPrint$(OBJ) \
   rtPrintToStream$(OBJ) \
   rtPrintToString$(OBJ) \
   rtStream$(OBJ) \
   rtTable$(OBJ) \
   rtUTF8StrToDynBitStr$(OBJ) \
   rtValidateStr$(OBJ) \
	rtGetLibInfo$(OBJ)

ASN1RT_CPPOBJECTS = \
   asn1CppTypes$(OBJ) \
   asn1CppEvtHndlr$(OBJ) \
   ASN1CBitStr$(OBJ) \
   ASN1CSeqOfList$(OBJ) \
   ASN1CTime$(OBJ) \
   ASN1CGeneralizedTime$(OBJ) \
   ASN1CUTCTime$(OBJ) \
   ASN1TObjId$(OBJ) \
   ASN1TOctStr$(OBJ) \
   ASN1TTime$(OBJ) \
   ASN1TGeneralizedTime$(OBJ) \
   ASN1TUTCTime$(OBJ)

ONLY_BER_C_RTOBJECTS = \
   berError$(OBJ) \
	berGetLibInfo$(OBJ) \
   berTagToString$(OBJ) \
   xd_real$(OBJ) \
   xd_indeflen$(OBJ) \
   xd_enum$(OBJ) \
   xd_count$(OBJ) \
   xd_common$(OBJ) \
   xd_match$(OBJ) \
   xd_match1$(OBJ) \
   xd_chkend$(OBJ) \
   xd_charstr$(OBJ) \
   xd_boolean$(OBJ) \
   xd_bitstr_s$(OBJ) \
   xd_bitstr$(OBJ) \
   xd_bigint$(OBJ) \
   xd_16BitCharStr$(OBJ) \
   xd_32BitCharStr$(OBJ) \
   xd_unsigned$(OBJ) \
   xd_uint8$(OBJ) \
   xd_uint16$(OBJ) \
   xd_OpenTypeExt$(OBJ) \
   xd_OpenType$(OBJ) \
   xd_OpenTypeAppend$(OBJ) \
   xd_octstr_s$(OBJ) \
   xd_octstr$(OBJ) \
   xd_objid$(OBJ) \
   xd_oid64$(OBJ) \
   xd_reloid$(OBJ) \
   xd_null$(OBJ) \
   xd_NextElement$(OBJ) \
   xd_MovePastEOC$(OBJ) \
   xd_memcpy$(OBJ) \
   xd_len$(OBJ) \
   xd_integer$(OBJ) \
   xd_int8$(OBJ) \
   xd_int16$(OBJ) \
   xd_int64$(OBJ) \
   xd_uint64$(OBJ) \
   xd_setp$(OBJ) \
   xd_Tag1AndLen$(OBJ) \
   xd_consstr$(OBJ) \
   xdf_TagAndLen$(OBJ) \
   xdf_ReadContents$(OBJ) \
   xe_real$(OBJ) \
   xe_common$(OBJ) \
   xe_charstr$(OBJ) \
   xe_boolean$(OBJ) \
   xe_bitstr$(OBJ) \
   xe_bigint$(OBJ) \
   xe_16BitCharStr$(OBJ) \
   xe_32BitCharStr$(OBJ) \
   xe_unsigned$(OBJ) \
   xe_uint8$(OBJ) \
   xe_uint16$(OBJ) \
   xe_TagAndIndefLen$(OBJ) \
   xe_OpenType$(OBJ) \
   xe_OpenTypeExt$(OBJ) \
   xe_octstr$(OBJ) \
   xe_objid$(OBJ) \
   xe_oid64$(OBJ) \
   xe_reloid$(OBJ) \
   xe_null$(OBJ) \
   xe_memcpy$(OBJ) \
   xe_integer$(OBJ) \
   xe_int8$(OBJ) \
   xe_int16$(OBJ) \
   xe_int64$(OBJ) \
   xe_uint64$(OBJ) \
   xe_enum$(OBJ) \
   xe_derCanonicalSort$(OBJ) \
   xe_ptr$(OBJ) \
   xe_free$(OBJ) \
   xu_BufferState$(OBJ) \
   xu_fdump$(OBJ) \
   xu_fmt_tag$(OBJ) \
   xu_fmt_contents$(OBJ) \
   berDecDecimal$(OBJ) \
   berDecReal10$(OBJ) \
   berEncReal10$(OBJ) \
   derEncReal10$(OBJ) \
   \
   berStrmInitContext$(OBJ) \
   berStrmFreeContext$(OBJ) \
   berEncStrmBigInt$(OBJ) \
   berEncStrmBitStr$(OBJ) \
   berEncStrmBMPStr$(OBJ) \
   berEncStrmBool$(OBJ) \
   berEncStrmCharStr$(OBJ) \
   berEncStrmCommon$(OBJ) \
   berEncStrmEnum$(OBJ) \
   berEncStrmInt$(OBJ) \
   berEncStrmInt8$(OBJ) \
   berEncStrmInt16$(OBJ) \
   berEncStrmInt64$(OBJ) \
   berEncStrmIntValue$(OBJ) \
   berEncStrmNull$(OBJ) \
   berEncStrmObjId$(OBJ) \
   berEncStrmObjId64$(OBJ) \
   berEncStrmOctStr$(OBJ) \
   berEncStrmReal$(OBJ) \
   berEncStrmRelativeOID$(OBJ) \
   berEncStrmUInt$(OBJ) \
   berEncStrmUInt8$(OBJ) \
   berEncStrmUInt16$(OBJ) \
   berEncStrmUInt64$(OBJ) \
   berEncStrmUnivStr$(OBJ) \
   berEncStrmOpenTypeExt$(OBJ) \
   berEncStrmXSDAny$(OBJ) \
   berDecStrmBitStr$(OBJ) \
   berDecStrmBigInt$(OBJ) \
   berDecStrmBMPStr$(OBJ) \
   berDecStrmCharStr$(OBJ) \
   berDecStrmCommon$(OBJ) \
   berDecStrmDynBitStr$(OBJ) \
   berDecStrmDynOctStr$(OBJ) \
   berDecStrmEnum$(OBJ) \
   berDecStrmInt$(OBJ) \
   berDecStrmInt8$(OBJ) \
   berDecStrmInt16$(OBJ) \
   berDecStrmInt64$(OBJ) \
   berDecStrmNextElement$(OBJ) \
   berDecStrmNull$(OBJ) \
   berDecStrmObjId$(OBJ) \
   berDecStrmObjId64$(OBJ) \
   berDecStrmOctStr$(OBJ) \
   berDecStrmOpenType$(OBJ) \
   berDecStrmOpenTypeAppend$(OBJ) \
   berDecStrmOpenTypeExt$(OBJ) \
   berDecStrmPeekTagAndLen$(OBJ) \
   berDecStrmReadTLV$(OBJ) \
   berDecStrmReal$(OBJ) \
   berDecStrmRelativeOID$(OBJ) \
   berDecStrmUInt$(OBJ) \
   berDecStrmUInt8$(OBJ) \
   berDecStrmUInt16$(OBJ) \
   berDecStrmUInt64$(OBJ) \
   berDecStrmUnivStr$(OBJ) \
   berDecStrmBool$(OBJ) \
   berSocket$(OBJ) \
   berDecStrmDecimal$(OBJ) \
   berDecStrmReal10$(OBJ) \
   berEncStrmReal10$(OBJ) \
   \
   cerEncStrmBMPStr$(OBJ) \
   cerEncStrmBitStr$(OBJ) \
   cerEncStrmCharStr$(OBJ) \
   cerEncStrmOctStr$(OBJ) \
   cerEncStrmUnivStr$(OBJ) \
   cerEncCanonicalSort$(OBJ) \
   cerEncStrmReal10$(OBJ) \
   derEncBitString$(OBJ)

ONLY_BER_CPP_RTOBJECTS = \
   asn1BerCppTypes$(OBJ) \
   ASN1BEREncodeStream$(OBJ) \
   ASN1BERDecodeStream$(OBJ) \
   $(ONLY_BER_C_RTOBJECTS)

BER_ASN1C_RTOBJECTS = \
   $(ONLY_BER_C_RTOBJECTS) \
   $(ASN1RT_C_OBJECTS)

ONLY_PER_C_RTOBJECTS = \
   pd_16BitConstrainedString$(OBJ) \
   pd_32BitConstrainedString$(OBJ) \
   pd_BigInteger$(OBJ) \
   pd_BigIntegerEx$(OBJ) \
   pd_BitString$(OBJ) \
   pd_BMPString$(OBJ) \
   pd_UniversalString$(OBJ) \
   pd_ChoiceOpenTypeExt$(OBJ) \
   pd_common$(OBJ) \
   pd_ConsWholeNumber64$(OBJ) \
   pd_ConsInteger$(OBJ) \
   pd_ConsInt8$(OBJ) \
   pd_ConsInt16$(OBJ) \
   pd_ConsInt64$(OBJ) \
   pd_ConstrainedString$(OBJ) \
   pd_ConsUnsigned$(OBJ) \
   pd_ConsUInt8$(OBJ) \
   pd_ConsUInt16$(OBJ) \
   pd_ConsUInt64$(OBJ) \
   pd_DynBitString$(OBJ) \
   pd_DynOctetString$(OBJ) \
   pd_ObjectIdentifier$(OBJ) \
   pd_oid64$(OBJ) \
   pd_RelativeOID$(OBJ) \
   pd_OctetString$(OBJ) \
   pd_OpenType$(OBJ) \
   pd_OpenTypeExt$(OBJ) \
   pd_Real$(OBJ) \
   pd_SemiConsInteger$(OBJ) \
   pd_SemiConsUnsigned$(OBJ) \
   pd_SemiConsInt64$(OBJ) \
   pd_SemiConsUInt64$(OBJ) \
   pd_VarWidthCharString$(OBJ) \
   pd_deprecated$(OBJ) \
   pe_16BitConstrainedString$(OBJ) \
   pe_32BitConstrainedString$(OBJ) \
   pe_BigInteger$(OBJ) \
   pe_BitString$(OBJ) \
   pe_BMPString$(OBJ) \
   pe_UniversalString$(OBJ) \
   pe_ChoiceTypeExt$(OBJ) \
   pe_common$(OBJ) \
   pe_common64$(OBJ) \
   pe_ConsWholeNumber64$(OBJ) \
   pe_ConsInteger$(OBJ) \
   pe_ConsInt64$(OBJ) \
   pe_ConstrainedString$(OBJ) \
   pe_ConsUnsigned$(OBJ) \
   pe_ConsUInt64$(OBJ) \
   pe_identifier$(OBJ) \
   pe_ObjectIdentifier$(OBJ) \
   pe_identifier64$(OBJ) \
   pe_oid64$(OBJ) \
   pe_RelativeOID$(OBJ) \
   pe_OctetString$(OBJ) \
   pe_OpenType$(OBJ) \
   pe_OpenTypeExt$(OBJ) \
   pe_Real$(OBJ) \
   pe_SemiConsInteger$(OBJ) \
   pe_SemiConsInt64$(OBJ) \
   pe_SemiConsUnsigned$(OBJ) \
   pe_SemiConsUInt64$(OBJ) \
   pe_VarWidthCharString$(OBJ) \
   pe_2sCompBinInt$(OBJ) \
   pe_2sCompBinInt64$(OBJ) \
   pe_NonNegBinInt$(OBJ) \
   pe_NonNegBinInt64$(OBJ) \
   pe_SmallNonNegWholeNumber$(OBJ) \
   pu_16BitCharSet$(OBJ) \
   pu_32BitCharSet$(OBJ) \
   pu_addSizeConstraint$(OBJ) \
   pu_alignCharStr$(OBJ) \
   pu_checkSize$(OBJ) \
   pu_common$(OBJ) \
   pu_deprecated$(OBJ) \
   pu_dump$(OBJ) \
   pu_field$(OBJ) \
   pu_insLenField$(OBJ) \
   pu_internal$(OBJ) \
   pu_setCharSet$(OBJ) \
   pu_setFldBitCount$(OBJ) \
   pu_setFldBitOffset$(OBJ) \
	pu_GetLibInfo$(OBJ) \
   perDecDecimal$(OBJ) \
   perDecReal10$(OBJ) \
   perEncReal10$(OBJ) 

PER_ASN1C_RTOBJECTS = \
   $(ONLY_PER_C_RTOBJECTS) \
   $(ASN1RT_C_OBJECTS)

ONLY_PER_CPP_RTOBJECTS = \
   asn1PerCppTypes$(OBJ) \
   $(ONLY_PER_C_RTOBJECTS)

# START OSBUILD
LIC_OBJECTS1 = \
orj$(OBJ)

LIC_OBJECTS_RT = \
orj$(OBJ) rt$(OBJ)

LIC_OBJECTS_BER = \
obj$(OBJ) rtb$(OBJ)

LIC_OBJECTS_PER = \
opj$(OBJ) rtp$(OBJ)

LIC_OBJECTS_XER = \
oxj$(OBJ) rtx$(OBJ)

LIC_OBJECTS2 = \
$(LIC_OBJECTS1) \
lic$(PS)xd_bitstr_s$(OBJ) lic$(PS)xd_charstr$(OBJ) lic$(PS)xd_chkend$(OBJ) lic$(PS)xd_consstr$(OBJ) \
lic$(PS)xd_count$(OBJ) lic$(PS)xd_common$(OBJ) lic$(PS)xd_integer$(OBJ) lic$(PS)xd_octstr_s$(OBJ) \
lic$(PS)xd_setp$(OBJ) lic$(PS)xd_memcpy$(OBJ) lic$(PS)xu_malloc$(OBJ) lic$(PS)xd_NextElement$(OBJ) \
lic$(PS)xd_len$(OBJ) lic$(PS)xd_MovePastEOC$(OBJ) lic$(PS)xu_BufferState$(OBJ) 
# END OSBUILD

STUB_OBJECTS_RT = \
rtevalstub$(OBJ)

STUB_OBJECTS_BER = \
rtevalstubb$(OBJ)

STUB_OBJECTS_PER = \
rtevalstubp$(OBJ)

STUB_OBJECTS_XER = \
rtevalstubx$(OBJ)

# stubs for every library.
rtevalstubb$(OBJ): \
    $(RTSRCDIR)/rtevalstub.c \
    $(RTSRCDIR)/asn1intl.h \
    $(RTSRCDIR)/asn1type.h \
    $(RTXSRCDIR)/rtxContext.h 
	$(CC) $(RTCFLAGS) -c $(IPATHS) $(OBJOUT) -D_BER $(RTSRCDIR)/rtevalstub.c

rtevalstubp$(OBJ): \
    $(RTSRCDIR)/rtevalstub.c \
    $(RTSRCDIR)/asn1intl.h \
    $(RTSRCDIR)/asn1type.h \
    $(RTXSRCDIR)/rtxContext.h 
	$(CC) $(RTCFLAGS) -c $(IPATHS) $(OBJOUT) -D_PER $(RTSRCDIR)/rtevalstub.c

rtevalstubx$(OBJ): \
    $(RTSRCDIR)/rtevalstub.c \
    $(RTSRCDIR)/asn1intl.h \
    $(RTSRCDIR)/asn1type.h \
    $(RTXSRCDIR)/rtxContext.h 
	$(CC) $(RTCFLAGS) -c $(IPATHS) $(OBJOUT) -D_XER $(RTSRCDIR)/rtevalstub.c


