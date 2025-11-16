#ifndef RANDBLOCK_H
#define RANDBLOCK_H

#include <random>

class RandBlock
{
public:
    RandBlock(int min, int max);

private:
    std::uniform_int_distribution<> m_distrib;
};

#endif // RANDBLOCK_H
