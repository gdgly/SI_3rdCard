// µœ÷IDC
#ifndef __DCARD__READ__H__
#define __DCARD__READ__H__

#include ".\\lib\\DCardReaderApi.h"
#pragma  comment(lib, ".\\lib\\DCardReader.lib")

class CDCardRead
{
public:
	CDCardRead();
	~CDCardRead();
	int OpenDevice();
	int CloseDevice();
	int ReadCardTracks (int trackid, char* pchTrackData2, char* pchTrackData3, int  itimeout);
	int ChipPowerOn (char* pchInitData);
	int ChipPowerOff();
	int ICCChipIo (char* szDataIn,  DWORD iLenIn, char* lpszDataOut, DWORD &iLenOut);
	int RFChipPowerOn (char* pchInitData);
	int RFChipPowerOff();
	int RFChipIo(char* szDataIn,  DWORD iLenIn, char* lpszDataOut, DWORD &iLenOut);
	int GetDeviceStatus( int* pDevstatus);
	int GetMediaStatus( int* pMediastatus);
	int ResetDevice();
	int InhaleCard (int iTimeout);
	int EjectICard ();
	int StopInhaleCard();
	int RetainCard ();
};


#endif
