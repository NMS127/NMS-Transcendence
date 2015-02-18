//	KernelObjID.h
//
//	This file contains a list of all object IDs implemented by
//	this module

#ifndef INCL_KERNELOBJID
#define INCL_KERNELOBJID

#define	OBJID_CSTRING					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 1)
#define OBJID_CINTARRAY					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 2)
#define OBJID_COBJECTARRAY				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 3)
#define OBJID_CARCHIVER					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 4)
#define OBJID_CFILEREADSTREAM			MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 5)
#define OBJID_CFILEWRITESTREAM			MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 6)
#define OBJID_CUNARCHIVER				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 7)
#define OBJID_CDICTIONARY				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 8)
#define OBJID_CSYMBOLTABLE				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 9)
#define OBJID_CSTRINGARRAY				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 10)
#define OBJID_CMEMORYWRITESTREAM		MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 11)
#define OBJID_CMEMORYREADSTREAM			MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 12)
#define OBJID_CDATAFILE					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 13)
#define OBJID_CFILEREADBLOCK			MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 14)
#define OBJID_CRESOURCEREADBLOCK		MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 15)
#define OBJID_CSTRUCTARRAY				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 16)
#define OBJID_CATOMTABLE				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 17)
#define OBJID_CGRESOURCEFILE			MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 18)
#define OBJID_CTEXTFILELOG				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 19)
#define OBJID_CIDTABLE					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 20)
#define OBJID_CGBITMAP					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 21)
#define OBJID_CGFONT					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 22)
#define OBJID_CSHAREDOBJECTQUEUE		MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 23)
#define OBJID_CINTSET					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 24)

#define OBJID_CCINTEGER					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 100)
#define OBJID_CCSTRING					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 101)
#define OBJID_CCLINKEDLIST				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 102)
#define OBJID_CCPRIMITIVE				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 103)
#define OBJID_CCODECHAIN				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 104)
#define OBJID_CCNIL						MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 105)
#define OBJID_CCTRUE					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 106)
#define OBJID_CCSYMBOLTABLE				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 107)
#define OBJID_CCLAMBDA					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 108)
#define OBJID_CCATOMTABLE				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 109)
#define OBJID_CCVECTOROLD				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 110)
#define OBJID_CCVECTOR					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 111)

#define OBJID_CUAPPLICATION				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 200)
#define OBJID_CUWINDOW					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 201)
#define OBJID_CUFRAME					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 202)
#define OBJID_CULINEEDITOR				MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 203)
#define OBJID_CUBUTTON					MakeOBJCLASSIDExt(OBJCLASS_MODULE_KERNEL, 204)

//	Include global IDs

#ifndef INCL_GLOBALOBJID
#include "GlobalObjID.h"
#endif

#endif