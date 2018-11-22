#include "stdafx.h"
#include "log.h"

long m_tracelevel = INFOR_LOG | ERROR_LOG | DEBUG_LOG | TRACE_LOG;

#define DATAMAXLEN 10240

#define FUNMAXLEN  256

void setTraceLevel(int type)

{

	m_tracelevel = type;

	m_tracelevel |= (INFOR_LOG | ERROR_LOG);

}

void SaveLog(char *funName, int returnValue, char *Msg)

{

	char sFileName[FUNMAXLEN];

	char sLog[DATAMAXLEN + FUNMAXLEN*2];

	SYSTEMTIME CurTime;

	GetLocalTime(&CurTime);  

	_mkdir("D:\\driver");
	char temp[MAX_PATH] = {};
	sprintf(temp,"D:\\driver\\%04d%02d",CurTime.wYear,CurTime.wMonth);
	_mkdir(temp);

	sprintf(sFileName,"%s\\log%04d%02d%02d.txt",temp,CurTime.wYear,CurTime.wMonth,CurTime.wDay,CurTime.wHour);

	sprintf(sLog,"[%4d-%02d-%02d %02d:%02d:%02d:%003d][funName:%s][ret:%d][msg:%s]",

		CurTime.wYear,CurTime.wMonth,CurTime.wDay,CurTime.wHour,CurTime.wMinute,CurTime.wSecond,CurTime.wMilliseconds,funName,returnValue,Msg);

	ofstream  f(sFileName,ios::out|ios::app);



	if (f.good())
	{
		f<<sLog<<endl;

		f.close();	
	}




}

void log_data(char* fname,char* errmsg,char *errvalue)

{

	char sFileName[FUNMAXLEN];

	char sLog[DATAMAXLEN + FUNMAXLEN*2];

	SYSTEMTIME CurTime;

	GetLocalTime(&CurTime);  
	_mkdir("D:\\driver");
	char temp[MAX_PATH] = {};
	sprintf(temp,"D:\\driver\\%04d%02d",CurTime.wYear,CurTime.wMonth);
	_mkdir(temp);

	sprintf(sFileName,"%s\\log%04d%02d%02d.txt",temp,CurTime.wYear,CurTime.wMonth,CurTime.wDay,CurTime.wHour);

	sprintf(sLog,"[%4d-%02d-%02d %02d:%02d:%02d:%003d][%s][%s][%s]",

		CurTime.wYear,CurTime.wMonth,CurTime.wDay,CurTime.wHour,CurTime.wMinute,CurTime.wSecond,CurTime.wMilliseconds,fname,errmsg,errvalue);

	ofstream  f(sFileName,ios::out|ios::app);

	if (f.good())
	{
		f<<sLog<<endl;

		f.close();	
	}





}

void log_infor(char* fname,char* errmsg,char *format,...)

{

	if(m_tracelevel & INFOR_LOG)

	{

		char tmpbuf[FUNMAXLEN];

		char errvalue[DATAMAXLEN + FUNMAXLEN*2];

		sprintf(tmpbuf,"infor in %s",fname);

		memset(errvalue,0x0,sizeof(errvalue));

		va_list ap;

		va_start(ap,format);

		_vsnprintf(errvalue,DATAMAXLEN - 1,format,ap);

		va_end(ap);

		log_data(tmpbuf,errmsg,errvalue);

	}

}

void log_error(char* fname,char* errmsg,char *format,...)

{

	if(m_tracelevel & ERROR_LOG)

	{

		char tmpbuf[FUNMAXLEN];

		char errvalue[DATAMAXLEN + FUNMAXLEN*2];

		sprintf(tmpbuf,"error in %s",fname);

		memset(errvalue,0x0,sizeof(errvalue));

		va_list ap;

		va_start(ap,format);

		_vsnprintf(errvalue,DATAMAXLEN - 1,format,ap);

		va_end(ap);

		log_data(tmpbuf,errmsg,errvalue);

	}

}

void log_debug(char* fname,char* errmsg,char *format,...)

{

	if(m_tracelevel & DEBUG_LOG)

	{

		char tmpbuf[FUNMAXLEN];

		char errvalue[DATAMAXLEN + FUNMAXLEN*2];

		sprintf(tmpbuf,"debug in %s",fname);

		memset(errvalue,0x0,sizeof(errvalue));

		va_list ap;

		va_start(ap,format);

		_vsnprintf(errvalue,DATAMAXLEN - 1,format,ap);

		va_end(ap);

		log_data(tmpbuf,errmsg,errvalue);

	}

}
void log_trace(char* fname,char* errmsg,char *format,...)

{

	if(m_tracelevel & TRACE_LOG)

	{

		char tmpbuf[FUNMAXLEN];

		char errvalue[DATAMAXLEN + FUNMAXLEN*2];

		sprintf(tmpbuf,"trace in %s",fname);

		memset(errvalue,0x0,sizeof(errvalue));

		va_list ap;

		va_start(ap,format);

		_vsnprintf(errvalue,DATAMAXLEN - 1,format,ap);

		va_end(ap);

		log_data(tmpbuf,errmsg,errvalue);

	}

}

void log_fatal(char* fname,char* errmsg,char *format,...)

{

	char tmpbuf[FUNMAXLEN];

	char errvalue[DATAMAXLEN + FUNMAXLEN*2];

	sprintf(tmpbuf,"fatal error in %s",fname);

	memset(errvalue,0x0,sizeof(errvalue));

	va_list ap;

	va_start(ap,format);

	_vsnprintf(errvalue,DATAMAXLEN - 1,format,ap);

	va_end(ap);

	log_data(tmpbuf,errmsg,errvalue);

}