#ifndef MEMPOOL_H
#define MEMPOOL_H

typedef unsigned long pointer_t;        // 32&64 位系统指针占用内存的长度都和 unsigned long 类型占用的长度相等
static const unsigned int AddrSize = sizeof(char*);

////内存池

class MemPool
{
public:
    ////创建内存池，并指定内存块个数iCnt, 内存块大小iSize
    MemPool(const unsigned int iCnt, const unsigned int iSize);
    ////初始化内存池
    bool Init(void *data = 0);

    ////获取和释放内存
    char *Get();
    bool Put(char *p);

    ////
    bool Empty() const;
    bool Full() const;
    unsigned int GetFreeCnt();
    unsigned int GetMaxCnt();
    unsigned int GetMaxSize();

    void Output();

    ~MemPool();


private:
    ////禁止默认拷贝，拷贝复制，拷贝赋值运算
    MemPool();
    MemPool(const MemPool &);
    MemPool& operator= (const MemPool&);

public:
    const unsigned int m_uiMaxCnt;
    const unsigned int m_uiMaxSize;

private:
    char *m_pBuf;
    char *m_pBufHead;
    char *m_pBufLast;
    unsigned int m_uiFreeCnt;
};

#endif // MEMPOOL_H
