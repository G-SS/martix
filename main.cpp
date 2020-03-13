#include <vector>
#include <iostream>
#include <cstring>
#include "datastruct.h"
#include "globallog.h"


using namespace std;

vector<int> getNum(char *string, const char *sqlit)
{
    vector<int> vec;



    char *a = strtok(string, sqlit);
    vec.push_back(atoi(a));

//    while(a)
//    {
//        a = strtok(string, sqlit);
//        vec.push_back(atoi(a));
//    }

    return vec;
}

int main()
{
    try
    {
        char chTmp[64] = "21 22 3 333";
        vector<int> vec = getNum(chTmp, " ");
        GlobalLog::m_strPath = "/home/martix/log.txt";
        GlobalLog::WriteLog(D, SS, Log, "Read OK.");
        int a = 0;

        return 0;

    }
    catch (exception &e)
    {
        GlobalLog::WriteLog(D, SS, Error, e.what());
        return 0;

    }

}
