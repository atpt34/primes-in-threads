#ifndef MY_INTERVAL_H
#define MY_INTERVAL_H

/*
  The struct represents an interval of integers.
*/
struct Interval {
public:
  Interval(int l, int h);

  int get_low() const { return m_low; }
  int get_high() const { return m_high; }

private:
  int m_low;
  int m_high;
};

bool operator==(const Interval& i1, const Interval& i2);

struct Interval_Exception { };

#endif
