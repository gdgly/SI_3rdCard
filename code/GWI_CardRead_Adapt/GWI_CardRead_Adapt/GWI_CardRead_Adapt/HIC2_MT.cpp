#include "stdafx.h"
#include "HIC2_MT.h"

CHIC2_MT::CHIC2_MT()
{

}

CHIC2_MT::~CHIC2_MT()
{

}

int CHIC2_MT::OpenDevice()
{
	return 1;
}
int CHIC2_MT::CloseDevice()
{
	return 1;
}
int CHIC2_MT::ReadCardTracks (int trackid, char* pchTrackData2, char* pchTrackData3, int  itimeout)
{
	return 1;
}
int CHIC2_MT::ChipPowerOn (char* pchInitData)
{
	return 1;
}

int CHIC2_MT::ChipPowerOff()
{
	return 1;
}
int CHIC2_MT::ICCChipIo (short ChipProtocols, char* szDataIn, char* lpszDataOut)
{
	return 1;
}
int CHIC2_MT::GetDeviceStatus( int* pDevstatus)
{
	return 1;
}
int CHIC2_MT::GetMediaStatus( int* pMediastatus)
{
	return 1;
}
int CHIC2_MT::ResetDevice()
{
	return 1;
}