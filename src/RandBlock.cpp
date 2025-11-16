#include "RandBlock.h"

RandBlock::RandBlock(int min, int max)
{
    m_rdev = new std::random_device;
    m_generator = new std::mt19937(m_rdev->operator()());
    m_distrib = new std::uniform_int_distribution<>(min, max);
}

RandBlock::~RandBlock()
{
    delete m_distrib;
    delete m_generator;
    delete m_rdev;
}

int RandBlock::rand()
{
    return m_distrib->operator()(*m_generator);
}
