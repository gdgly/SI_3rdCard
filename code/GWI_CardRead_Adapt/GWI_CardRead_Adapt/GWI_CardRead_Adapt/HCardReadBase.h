#ifndef __HCARDREAD__BASE__H__
#define __HCARDREAD__BASE__H__
#include "stdafx.h"

class CHCardReadBase
{
public:
	CHCardReadBase();
	virtual ~CHCardReadBase();
	virtual int OpenDevice() = 0;
	virtual int CloseDevice()  = 0;
	virtual int ReadCardTracks (int trackid, char* pchTrackData2, char* pchTrackData3, int  itimeout) = 0;
	virtual int ChipPowerOn (char* pchInitData) = 0;
	virtual int ChipPowerOff() = 0;
	virtual int ICCChipIo (char* szDataIn,  DWORD iLenIn, char* lpszDataOut, DWORD &iLenOut) = 0;
	virtual int RFChipPowerOn (char* pchInitData) = 0;
	virtual int RFChipPowerOff() = 0;
	virtual int RFChipIo(char* szDataIn,  DWORD iLenIn, char* lpszDataOut, DWORD &iLenOut) = 0;
	virtual int GetDeviceStatus( int* pDevstatus) = 0;
	virtual int GetMediaStatus( int* pMediastatus) = 0;
	virtual int ResetDevice() = 0;
	virtual int InhaleCard (int iTimeout) = 0;
	virtual int EjectICard () = 0;
	virtual int StopInhaleCard() = 0;
	virtual int RetainCard () = 0;
};

#endif