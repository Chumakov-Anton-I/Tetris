#ifndef RANDBLOCK_H
#define RANDBLOCK_H

#include <random>

class RandBlock
{
public:
    RandBlock(int min, int max);
    ~RandBlock();

    int rand();

private:
    std::random_device *m_rdev;
    std::mt19937 *m_generator;
    std::uniform_int_distribution<> *m_distrib;
};

#endif // RANDBLOCK_H
