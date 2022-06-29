#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>
#include <string.h>
#include <QtGlobal>
#include <stdarg.h>
#include <iostream>
#include <stdarg.h>
#include <QDebug>
#define INFO_TRACE 0x01
#define INFO_ERROR 0x02
#define INFO_WARN  0x04
#define INFO_DEBUG 0x08
#define INFO_ALL INFO_TRACE|INFO_ERROR|INFO_WARN|INFO_DEBUG
const int g_nlogLevel = INFO_ALL;

using namespace std;
#define FILE_MAX_SIZE (1024*1024)
#define BUFSIZE_MAX 1024

//向字符数组 buffer 中写入当前时间
inline void get_local_time(char* buffer)
{
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
        (timeinfo->tm_year+1900), timeinfo->tm_mon+1, timeinfo->tm_mday,
        timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

/*
获得日志文件大小
@param filename [in]: 文件名
@return 文件大小
*/
inline long get_file_size(char* filename)
{
    long length = 0;
    FILE *fp = nullptr;

    fp = fopen(filename, "rb");
    if (fp != nullptr)
    {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
    }

    if (fp != nullptr)
    {
        fclose(fp);
        fp = nullptr;
    }

    return length;
}


/*
写入日志文件
@param filename [in]: 日志文件名
@param max_size [in]: 日志文件大小限制
@param buffer [in]: 日志内容
@param buf_size [in]: 日志内容大小
@return 空
*/

#ifdef Q_OS_WIN32
inline void write_log_file(int nLevel, string buf,...)
{
    if(!(nLevel & g_nlogLevel)) return;

    //
    va_list args;
    char buffer[BUFSIZE_MAX] = { '\0' };
    va_start(args, buf);
    vsprintf_s(buffer, buf.c_str(), args);


    char * filename = (char*)"..\\log.txt";
    if (filename != nullptr)
    {
        // 写日志
        FILE *fp;
        fp = fopen(filename, "at+");
        if (fp != nullptr)
        {
            char now[32];
            memset(now, 0, sizeof(now));
            get_local_time(now);

            //
            char pszLog[BUFSIZE_MAX] = {0};
            switch (nLevel)
            {
            case INFO_TRACE:
                qDebug()<<QString("[%1] <%2> %3").arg(now).arg("Trace").arg(buffer);
                sprintf_s(pszLog, "[%s] <%s> %s\n", now, "Trace", buffer);
                break;
            case INFO_ERROR:
                qDebug()<<QString("[%1] <%2> %3").arg(now).arg("Error").arg(buffer);
                sprintf_s(pszLog, "[%s] <%s> %s\n", now, "Error", buffer);
                break;
            case INFO_WARN :
                qDebug()<<QString("[%1] <%2> %3").arg(now).arg("Warn").arg(buffer);
                sprintf_s(pszLog, "[%s] <%s> %s\n", now, "Warn ", buffer);
                break;
            case INFO_DEBUG:
                qDebug()<<QString("[%1] <%2> %3").arg(now).arg("Debug").arg(buffer);
                sprintf_s(pszLog, "[%s] <%s> %s\n", now, "Debug", buffer);
                break;
            }
            fwrite(pszLog, strlen(pszLog), sizeof(char), fp);
            fclose(fp);
            fp = nullptr;
        }
    }
}
#endif

#ifdef Q_OS_LINUX
inline void write_log_file(int nLevel, string buf,...)
{
    if(!(nLevel & g_nlogLevel)) return;

    //
    va_list args;
    char buffer[BUFSIZE_MAX] = { '\0' };
    va_start(args, buf);
    vsprintf(buffer, buf.c_str(), args);

    char * filename=(char*)"./log.txt";
    if (filename != nullptr)
    {
        // 写日志
        FILE *fp;
        fp = fopen(filename, "at+");
        if (fp != nullptr)
        {
            char now[32];
            memset(now, 0, sizeof(now));
            get_local_time(now);

            //
            char pszLog[BUFSIZE_MAX] = {0};
            sprintf(pszLog, "[%s] %s\n", now, buffer);
            fwrite(pszLog, strlen(pszLog), sizeof(char), fp);
            //fwrite(now, strlen(now), 1, fp);
            //fwrite(": ", 2, 2, fp);
            //fwrite(buffer, strlen(buffer), 1, fp);
            //fwrite("\r\n",2,1,fp);
            //fwrite("\n",2,1,fp);
            fclose(fp);
            fp = nullptr;
        }
    }
}
#endif


#ifdef QT_NO_DEBUG
#define Log_accessControl write_log_file
#else
#define Log_accessControl write_log_file
#endif
