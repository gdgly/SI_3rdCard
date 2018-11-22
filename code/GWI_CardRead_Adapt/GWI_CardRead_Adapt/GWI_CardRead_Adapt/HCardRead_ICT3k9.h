// µœ÷IDC
#ifndef __HCARDREAD__ICT3K9__H__
#define __HCARDREAD__ICT3K9__H__

#include "HCardReadBase.h"
class HCardRead_ICT3k9 :public CHCardReadBase
{
public:
	HCardRead_ICT3k9();
	~HCardRead_ICT3k9();
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
