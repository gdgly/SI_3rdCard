#include "stdafx.h"
#include "DCardRead.h"

CDCardRead::CDCardRead()
{

}

CDCardRead::~CDCardRead()
{

}
int CDCardRead::OpenDevice()
{
	return CDB_OpenDevice();
}
int CDCardRead::CloseDevice()
{
	return CDB_CloseDevice();
}
int CDCardRead::ReadCardTracks (int trackid, char* pchTrackData2, char* pchTrackData3, int  itimeout)
{
	return CDB_ReadCardTracks (trackid, pchTrackData2, pchTrackData3, itimeout);

}
int CDCardRead::ChipPowerOn (char* pchInitData)
{
	return CDB_ChipPowerOn (pchInitData);
}
int CDCardRead::ChipPowerOff()
{
	return CDB_ChipPowerOff();
}

int CDCardRead::ICCChipIo (char* szDataIn,  DWORD iLenIn, char* lpszDataOut, DWORD &iLenOut)
{
	int iret = -1;
	iret =  CDB_CDBChipIo(0,szDataIn, lpszDataOut);
	iLenOut = strlen(lpszDataOut);
	return iret;
}
int CDCardRead::RFChipPowerOn (char* pchInitData)
{
	return CDB_RFChipPowerOn (pchInitData);
}
int CDCardRead::RFChipPowerOff()
{
	return CDB_RFChipPowerOff();
}
int CDCardRead::RFChipIo(char* szDataIn,  DWORD iLenIn, char* lpszDataOut, DWORD &iLenOut)
{
	int iret = -1;
	iret = CDB_RFChipIo(0,(char*)szDataIn, lpszDataOut);
	iLenOut =strlen(lpszDataOut);
	return iret;
}
int CDCardRead::GetDeviceStatus( int* pDevstatus)
{
	return CDB_GetDeviceStatus(pDevstatus);
}
int CDCardRead::GetMediaStatus( int* pMediastatus)
{
	return CDB_GetMediaStatus( pMediastatus);
}
int CDCardRead::ResetDevice()
{
	return CDB_ResetDevice(2);
}
int CDCardRead::InhaleCard (int iTimeout)
{
	return CDB_InhaleCard (3,iTimeout);
}
int CDCardRead::EjectICard ()
{
	return CDB_EjectICard ();
}
int CDCardRead::StopInhaleCard()
{
	return CDB_StopInhaleCard();
}
int CDCardRead::RetainCard ()
{
	return CDB_RetainCard();
}