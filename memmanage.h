#ifndef MEMMANAGE_H
#define MEMMANAGE_H

#include "mempool.h"

///定长内存池管理

struct MemPoolContainer
{
    MemPool memPool;
    struct MemPoolContainer *pNext;
    MemPoolContainer(const unsigned int count, const unsigned int size)
        : memPool(count, size), pNext(nullptr)
    {

    }
};

class MemManage
{
public:
    ///第一次分配count块大小为size的内存，内存用完则自动分配step块内存
    /// 第一次分配的内存大小和个数均不能小于1
    MemManage(const unsigned int count, const unsigned int step, const unsigned int size);

    ~MemManage();

    ///获得和释放内存
    char* Get();
    void Put(char *p);

    void Free();    ///释放空闲内存池
    void Clear();   ///释放所有内存池

public:
    unsigned int GetBufSize() const;
    unsigned int GetMaxCnt() const;
    unsigned int GetFreeCnt() const;

    ///step的值必须大于1，否则1不会创建内存池
    void SetStep(unsigned int step);
    unsigned int GetStep() const;

    ///仅测试使用
    void Output();

private:
    bool CreatePool(const unsigned int count, const unsigned int size, MemPoolContainer* pMemPoolContainer);
    void DestoryPool(MemPoolContainer *pMemPoolContainer);



private:
    ///禁止拷贝，拷贝赋值操作
    MemManage();
    MemManage(const MemManage&);
    MemManage& operator=(const MemManage&);

private:
    const unsigned int m_uiBuffSize;
    unsigned int m_uiStep;
    MemPoolContainer* m_pHead;


};

#endif // MEMMANAGE_H
