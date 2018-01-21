#ifndef MY_PRIMES_CALCULATOR_H
#define MY_PRIMES_CALCULATOR_H

#include <vector>
#include <mutex>
#include "Interval.h"

/*
  The class calculates primes in given intervals.
*/
class Primes_Calculator {
public:
  Primes_Calculator() = default;
  Primes_Calculator(const std::vector<Interval>& vi);
  Primes_Calculator(const Primes_Calculator&) = delete;
  Primes_Calculator(Primes_Calculator&&) = default;
  ~Primes_Calculator() = default;

  Primes_Calculator& operator=(const Primes_Calculator&) = delete;
  Primes_Calculator& operator=(Primes_Calculator&&) = default;

  const std::vector<int>& get_primes();

private:
  bool is_prime(int n);
  void eliminate_duplicates();
  void seq_calc(const std::vector<Interval>& vi);
  void par_calc(const std::vector<Interval>& vi);
  void par_push(int n);
  void par_thread_calc(const Interval& in);

private:
  std::vector<int> m_primes; 
  std::mutex m_shared_mutex;
};

#endif
