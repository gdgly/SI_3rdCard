// µœ÷Ic2
#ifndef __ICCARD__READ__H__
#define __ICCARD__READ__H__

#include ".\\lib\\DIcCardReaderApi.h"
#pragma  comment(lib, ".\\lib\\DIcCardReader.lib")

class CIcCardRead
{
public:
	CIcCardRead();
	~CIcCardRead();
	int OpenDevice();
	int CloseDevice();
	int ReadCardTracks (int trackid, char* pchTrackData2, char* pchTrackData3, int  itimeout);
	int ChipPowerOn (char* pchInitData);
	int ChipPowerOff();
	int ICCChipIo (short ChipProtocols, char* szDataIn, char* lpszDataOut);
	int GetDeviceStatus( int* pDevstatus);
	int GetMediaStatus( int* pMediastatus);
	int ResetDevice();

};

#endif