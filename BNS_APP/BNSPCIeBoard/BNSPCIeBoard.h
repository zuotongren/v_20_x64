// BNSPCIeBoard.h   header file to declare CBNSFactory for generating various type of board objects
//				and the base class BNSPCIeBoard

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

#ifndef  BNSPCIeBOARD
#define BNSPCIeBOARD

#include "BNSPCIeHardware.h"

// This class is exported from the BNSPCIeBoard.dll
class AFX_EXT_CLASS CBNSPCIeBoard 
{
private:
	SBoard_Spec		m_BoardSpec;

public:
	virtual SBoard_Spec		*BoardSpec();

public:
	CBNSPCIeBoard(void);
	virtual ~CBNSPCIeBoard(void);

	virtual int WriteFrameBuffer(unsigned char *buffer);
	virtual int WriteLUT(unsigned char LUT[256]);

	virtual int SetTrueFrames(unsigned short TF);
	virtual int GetTrueFrames();

	virtual int SetLCType(bool bNematic);

	virtual int GetRunStatus();

	virtual int SetPower(bool powerOn);
	virtual int GetPower();
};


class AFX_EXT_CLASS CBNSPCIeFactory
{
public:
	CBNSPCIeFactory(void);
	~CBNSPCIeFactory(void);

	CBNSPCIeBoard *BuildBoard(CString rqstBoardName, 
							  char buffer[_MAX_PATH], 
							  char buffer2[_MAX_PATH], 
							  bool bInit, 
							  bool TestEnable, 
							  bool RAMWriteEnable, 
							  bool *VerifyHardware);
};

#endif


#undef AFX_DATA
#define AFX_DATA