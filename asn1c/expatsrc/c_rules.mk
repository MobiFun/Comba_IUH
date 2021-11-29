xmlparse$(OBJ): $(EXPATSRCDIR)/xmlparse.c $(EXPATSRCDIR)/expat.h
	$(CC) $(CFLAGS) -c $(IPATHS) $(XMLINC) $(XMLDEFS) $(EXPATSRCDIR)/xmlparse.c

xmlrole$(OBJ): $(EXPATSRCDIR)/xmlrole.c $(EXPATSRCDIR)/expat.h
	$(CC) $(CFLAGS) -c $(IPATHS) $(XMLINC) $(XMLDEFS) $(EXPATSRCDIR)/xmlrole.c

xmltok$(OBJ): $(EXPATSRCDIR)/xmltok.c $(EXPATSRCDIR)/expat.h
	$(CC) $(CFLAGS) -c $(IPATHS) $(XMLINC) $(XMLDEFS) $(EXPATSRCDIR)/xmltok.c

xmltok_impl$(OBJ): $(EXPATSRCDIR)/xmltok_impl.c $(EXPATSRCDIR)/expat.h
	$(CC) $(CFLAGS) -c $(IPATHS) $(XMLINC) $(XMLDEFS) $(EXPATSRCDIR)/xmltok_impl.c

xmltok_ns$(OBJ): $(EXPATSRCDIR)/xmltok_ns.c $(EXPATSRCDIR)/expat.h
	$(CC) $(CFLAGS) -c $(IPATHS) $(XMLINC) $(XMLDEFS) $(EXPATSRCDIR)/xmltok_ns.c


