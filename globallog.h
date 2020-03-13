#ifndef GLOBALLOG_H
#define GLOBALLOG_H

#include <string>
#include "datastruct.h"

using namespace std;


class GlobalLog
{
public:
    GlobalLog();

    static bool WriteLog(ModulType modulType, LogType logType, MessageType messageType,
                    const string &message);

public:
    static string m_strPath;
};

#endif // GLOBALLOG_H
