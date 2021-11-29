#ifdef FUNCNAME

EXTXMLMETHOD int FUNCNAME (OSCTXT* pctxt, const OSXSDDateTime* pvalue,
              const OSUTF8CHAR* elemName, OSXMLNamespace* pNS)
{
   int stat;
   if (0 != elemName) {
      stat = rtXmlEncStartElement (pctxt, elemName, pNS, 0, TRUE);
   }
   else {
      /* Make sure previous start element is terminated */
      stat = rtXmlEncTermStartElement (pctxt);
   }
   if (0 == stat) {
      if (pctxt->state != OSXMLATTR)
         pctxt->state = OSXMLDATA;
      stat = ENCVALUEFUNC (pctxt, pvalue);
   }
   if (0 != elemName && 0 == stat) {
      stat = rtXmlEncEndElement (pctxt, elemName, pNS);
   }

   return (stat != 0) ? LOG_RTERR (pctxt, stat) : 0;
}

#endif /* FUNCNAME */

