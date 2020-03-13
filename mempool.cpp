#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "mempool.h"



MemPool::MemPool(const unsigned int iCnt, const unsigned int iSize)
    :m_uiMaxCnt(iCnt),m_uiMaxSize(iSize),m_uiFreeCnt(0)
{
    m_pBuf = nullptr;
    m_pBufHead = nullptr;
    m_pBufLast = nullptr;

    if(iCnt <= 1 || iSize == 0)
        return;
    m_pBuf = new char[(iSize + AddrSize) * iSize];
}

MemPool::~MemPool()
{
    m_pBufHead = nullptr;
    m_pBufLast = nullptr;
    m_uiFreeCnt = 0;
    delete [] m_pBuf;
}

bool MemPool::Init(void *data/*=0*/)
{
    ////对分配到的内存进行切片，以链表存储
    if(m_pBuf != nullptr)
    {
        const unsigned int count = m_uiMaxCnt;
        const unsigned int len = AddrSize + m_uiMaxSize;    //块大小
        const unsigned int max = len * count;   //总内存的大小

        memset(m_pBuf, 0, sizeof(char)*max);
        m_pBufLast = m_pBuf + len * (count-1);

        char *pCur = nullptr;
        char *pNext = nullptr;

        for(unsigned int i=0; i<count-1; i++)
        {
            pCur = m_pBuf + len * i;        //当前buf块
            pNext = m_pBuf + len * (i+1);   //下一buf块起始地址
            *(pointer_t*)pCur = (pointer_t)pNext;   //存储在前一buf块的头部
            *(pointer_t*)(pCur + AddrSize) = (pointer_t)data;   //在头部存储用户数据
        }
        *(pointer_t*)(pNext + AddrSize) = (pointer_t)data;  //在头部存储用户数据，最后一块内存块

        m_pBufHead = m_pBuf;
        m_uiFreeCnt = count;
        return true;
    }
    return false;

}

char* MemPool::Get()
{
    char *pRet = nullptr;
    if(!Empty())
    {
        m_uiFreeCnt--;
        pRet = m_pBufHead + AddrSize;
        m_pBufHead = (char*)(*(pointer_t*)m_pBufHead);
    }
    return pRet;
}

bool MemPool::Put(char *p)
{
    if(p != nullptr)
    {
        p -= AddrSize;
        ////判断位置
        if(p < m_pBuf || p > m_pBufLast)
            return false;

        if(m_pBufHead != NULL)
        {
            *(pointer_t*)p = (pointer_t)m_pBufHead;
        }
        else {
            *(pointer_t*)p = 0;
        }
        m_pBufHead = p;
        m_uiFreeCnt++;
    }
    return true;
}

bool MemPool::Empty() const
{
    return (m_uiFreeCnt == 0);
}

bool MemPool::Full() const
{
    return (m_uiMaxCnt == m_uiFreeCnt);
}

unsigned int MemPool::GetMaxCnt()
{
    return m_uiMaxCnt;
}

unsigned int MemPool::GetFreeCnt()
{
    return m_uiFreeCnt;
}

unsigned int MemPool::GetMaxSize()
{
    return m_uiMaxSize;
}

void MemPool::Output()
{
    char* p = m_pBufHead;
    while (p != nullptr)
    {
        printf("--> %ld", (pointer_t)p);
        p = (char*)(*(pointer_t*)p);
    }
    printf("\n");
}






