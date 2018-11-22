#include "stdafx.h"
#include "HCardRead_ICT3k9.h"

HCardRead_ICT3k9::HCardRead_ICT3k9()
{

}

HCardRead_ICT3k9::~HCardRead_ICT3k9()
{

}
int HCardRead_ICT3k9::OpenDevice()
{
	return 1;
}
int HCardRead_ICT3k9::CloseDevice()
{
	return 1;
}
int HCardRead_ICT3k9::ReadCardTracks (int trackid, char* pchTrackData2, char* pchTrackData3, int  itimeout)
{
	return 1;
}
int HCardRead_ICT3k9::ChipPowerOn (char* pchInitData)
{
	return 1;
}
int HCardRead_ICT3k9::ChipPowerOff()
{
	return 1;
}

int HCardRead_ICT3k9::ICCChipIo (char* szDataIn,  DWORD iLenIn, char* lpszDataOut, DWORD &iLenOut)
{
	return 1;
}
int HCardRead_ICT3k9::RFChipPowerOn (char* pchInitData)
{
	return 1;
}
int HCardRead_ICT3k9::RFChipPowerOff()
{
	return 1;
}
int HCardRead_ICT3k9::RFChipIo(char* szDataIn,  DWORD iLenIn, char* lpszDataOut, DWORD &iLenOut)
{
	return 1;
}
int HCardRead_ICT3k9::GetDeviceStatus( int* pDevstatus)
{
	return 1;
}
int HCardRead_ICT3k9::GetMediaStatus( int* pMediastatus)
{
	return 1;
}
int HCardRead_ICT3k9::ResetDevice()
{
	return 1;
}
int HCardRead_ICT3k9::InhaleCard (int iTimeout)
{
	return 1;
}
int HCardRead_ICT3k9::EjectICard ()
{
	return 1;
}
int HCardRead_ICT3k9::StopInhaleCard()
{
	return 1;
}
int HCardRead_ICT3k9::RetainCard ()
{
	return 1;
}