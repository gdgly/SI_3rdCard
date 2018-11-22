#ifndef __HIC2BASE__H__
#define __HIC2BASE__H__


class CHIc2Base
{
public:
	CHIc2Base();
	virtual ~CHIc2Base();
	virtual int OpenDevice() = 0;
	virtual int CloseDevice() = 0;
	virtual int ReadCardTracks (int trackid, char* pchTrackData2, char* pchTrackData3, int  itimeout) = 0;
	virtual int ChipPowerOn (char* pchInitData) = 0;
	virtual int ChipPowerOff() = 0;
	virtual int ICCChipIo (short ChipProtocols, char* szDataIn, char* lpszDataOut) = 0;
	virtual int GetDeviceStatus( int* pDevstatus) = 0;
	virtual int GetMediaStatus( int* pMediastatus) = 0;
	virtual int ResetDevice() = 0;
};

#endif