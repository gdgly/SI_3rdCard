#ifndef __HIC2_MT__H__
#define __HIC2_MT__H__

#include "HIc2Base.h"
class CHIC2_MT : public CHIc2Base
{
public:
	CHIC2_MT();
	~CHIC2_MT();
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
