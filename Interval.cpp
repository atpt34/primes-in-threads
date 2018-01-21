#include "Interval.h"

Interval::Interval(int l, int h)
  : m_low{l}, m_high{h}
{
  if (l > h)
    throw Interval_Exception{};
}

bool operator==(const Interval& i1, const Interval& i2)
{
  return i1.get_low() == i2.get_low() && i1.get_high() == i2.get_high();
}
