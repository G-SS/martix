#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "globallog.h"

string GlobalLog::m_strPath = "/home/martix/log.txt";

GlobalLog::GlobalLog()
{

}

bool GlobalLog::WriteLog(ModulType modulType, LogType logType, MessageType messaggeType,
                         const string &message)
{
    FILE *fp = nullptr;
    char log[512] = "";
    char currentTime[20] = "";
    time_t rawtime;

    time(&rawtime);
    strftime(currentTime, sizeof(currentTime), "%F %T", localtime(&rawtime));
    fp = fopen(m_strPath.data(), "a+w+");

    sprintf(log, "[INFO] %s %d %d %d %s.\n",currentTime, modulType, logType, messaggeType, message.data());

    if(fwrite(log, 1, sizeof(log), fp))
    {
        return false;
    }
    return true;
}
