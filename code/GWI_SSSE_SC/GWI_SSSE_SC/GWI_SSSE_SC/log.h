#pragma  once

#include <fstream>
#include<direct.h>
using namespace std;
#define    FATAL_LOG  0x0000

#define    ERROR_LOG  0x0001

#define    TRACE_LOG  0x0010

#define    INFOR_LOG  0x0100

#define    DEBUG_LOG  0x1000 



#define	MAX_NAME (256)

#define	LOGSYNCTIME (1000)



void SaveLog(char *funName, int returnValue, char *Msg);

void setTraceLevel(int type);

void log_data(char* fname,char* errmsg,char *errvalue);

void log_fatal(char* fname,char* errmsg,char * format,...);



void log_error(char* fname,char* errmsg,char * format,...);

void log_infor(char* fname,char* errmsg,char * format,...);

void log_trace(char* fname,char* errmsg,char * format,...);

void log_debug(char* fname,char* errmsg,char * format,...);