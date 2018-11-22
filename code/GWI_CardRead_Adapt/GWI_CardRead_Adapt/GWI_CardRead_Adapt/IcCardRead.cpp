#include "stdafx.h"
#include "IcCardRead.h"


CIcCardRead::CIcCardRead()
{

}

CIcCardRead::~CIcCardRead()
{

}

int CIcCardRead::OpenDevice()
{
	return IC2_OpenDevice();
}
int CIcCardRead::CloseDevice()
{
	return IC2_CloseDevice();
}
int CIcCardRead::ReadCardTracks (int trackid, char* pchTrackData2, char* pchTrackData3, int  itimeout)
{
	return IC2_ReadCardTracks (trackid, pchTrackData2, pchTrackData3, itimeout);
}
int CIcCardRead::ChipPowerOn (char* pchInitData)
{
	return IC2_ChipPowerOn (pchInitData);
}

int CIcCardRead::ChipPowerOff()
{
	return IC2_ChipPowerOff();
}
int CIcCardRead::ICCChipIo (short ChipProtocols, char* szDataIn, char* lpszDataOut)
{
	return IC2_ICCChipIo (ChipProtocols, szDataIn, lpszDataOut);
}
int CIcCardRead::GetDeviceStatus( int* pDevstatus)
{
	return IC2_GetDeviceStatus( pDevstatus);
}
int CIcCardRead::GetMediaStatus( int* pMediastatus)
{
	return IC2_GetMediaStatus(pMediastatus);
}
int CIcCardRead::ResetDevice()
{
	return IC2_ResetDevice();
}