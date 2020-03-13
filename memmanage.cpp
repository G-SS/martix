#include "mempool.h"
#include "memmanage.h"

MemManage::MemManage(const unsigned int count, const unsigned int step, const unsigned int size)
    :m_uiBuffSize(size),m_uiStep(0),m_pHead(nullptr)
{
    if(count <= 1 || step <= 1 || size == 0)
        return;
    m_uiStep = step;
    CreatePool(count, size+AddrSize, m_pHead);
}

MemManage::~MemManage()
{
    m_uiStep = 0;
    Clear();
}

char* MemManage::Get()
{
    char* pRet = nullptr;

    MemPoolContainer* pPre = nullptr;
    MemPoolContainer* pCur = m_pHead;

    while(pCur != nullptr)
    {
        pRet = pCur->memPool.Get();
        if(pRet != nullptr)
        {
            pRet += AddrSize;   ///用户buf块的起始内存地址
            if(pPre != nullptr)
            {
                ///把非空内存池调整到链表头部
                pPre->pNext = pCur->pNext;
                pCur->pNext = m_pHead;
                m_pHead = pCur;
            }
            break;
        }
        pPre = pCur;
        pCur = pCur->pNext;
    }

    ////内存池没有内存块了，创建新的内存池
    if(pRet==nullptr && m_uiStep>1)
    {
        MemPoolContainer* pMemPoolContainer = nullptr;
        if(CreatePool(m_uiStep, m_uiBuffSize+AddrSize, pMemPoolContainer))
        {
            pMemPoolContainer->pNext = m_pHead;
            m_pHead = pMemPoolContainer;
            pRet = pMemPoolContainer->memPool.Get();
            pRet += AddrSize;   ///用户buff块起始位置
        }
    }

    return pRet;
}


void MemManage::Put(char *p)
{
    if(p!=nullptr)
    {
        p -= AddrSize;
        MemPool *mp = (MemPool*)((unsigned long*)p);
        mp->Put(p);
    }
}

void MemManage::Free()
{
    MemPoolContainer *pDelete = nullptr;
    MemPoolContainer *pPre = nullptr;
    MemPoolContainer *pCur = m_pHead;

    while(pCur != nullptr)
    {
        if(pCur->memPool.Full())
        {
            pDelete = pCur;
            if(pPre != nullptr)
            {
                pPre->pNext = pCur->pNext;
            }
            else
            {
                m_pHead = pCur->pNext;
            }
            pCur = pCur->pNext;
            DestoryPool(pDelete);
            continue;
        }
        pPre = pCur;
        pCur = pCur->pNext;
    }
}


void MemManage::Clear()
{
    MemPoolContainer *pDelete = nullptr;
    MemPoolContainer *pCur = m_pHead;
    m_pHead = nullptr;

    while(pCur!=nullptr)
    {
        pDelete = pCur;
        pCur = pCur->pNext;
        DestoryPool(pDelete);
    }
}

unsigned int MemManage::GetMaxCnt() const
{
    unsigned int count = 0;
    MemPoolContainer *pCur = m_pHead;
    while(pCur!=nullptr)
    {
        count += pCur->memPool.GetMaxCnt();
        pCur = pCur->pNext;
    }
    return count;
}


unsigned int MemManage::GetBufSize() const
{
    return m_uiBuffSize;
}

unsigned int MemManage::GetFreeCnt() const
{
    unsigned int count = 0;
    MemPoolContainer *pCur = m_pHead;
    while(pCur != nullptr)
    {
        count += pCur->memPool.GetFreeCnt();
        pCur = pCur->pNext;
    }
    return count;
}

unsigned int MemManage::GetStep() const
{
    return m_uiStep;
}

///step需大于1
void MemManage::SetStep(unsigned int step)
{
    if(step > 1)
        m_uiStep = step;
}

void MemManage::Output()
{
    MemPoolContainer* pCur = m_pHead;
    while (pCur != nullptr)
    {
        pCur->memPool.Output();
        pCur = pCur->pNext;
    }
}






