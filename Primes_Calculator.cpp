#include "Primes_Calculator.h"

#include <algorithm>
#include <thread>

using std::vector;
using std::thread;
using std::mutex;
using std::lock_guard;
using std::distance;
using std::sort;
using std::unique;

Primes_Calculator::Primes_Calculator(const vector<Interval>& vi)
{
  par_calc(vi); //seq_calc(vi);
  eliminate_duplicates();
}

const vector<int>& Primes_Calculator::get_primes()
{
  return m_primes;
}

void Primes_Calculator::seq_calc(const vector<Interval>& vi)
{
  for(const auto& in : vi) {
    for (int i = in.get_low(); i <= in.get_high(); ++i) {
      if (is_prime(i))
        m_primes.push_back(i);
    }
  }
}

void Primes_Calculator::par_push(int n)
{
  lock_guard<mutex> lg{m_shared_mutex};
  m_primes.push_back(n);
}

void Primes_Calculator::par_thread_calc(const Interval& in)
{
  for (int i = in.get_low(); i <= in.get_high(); ++i) {
    if (is_prime(i))
      par_push(i);
  }
}

void Primes_Calculator::par_calc(const vector<Interval>& vi)
{
  vector<thread> vt;
  for (const auto& in : vi)
    vt.push_back(thread(&Primes_Calculator::par_thread_calc, this, in));
  for (auto& t : vt)
    t.join();
}

void Primes_Calculator::eliminate_duplicates()
{
  sort(m_primes.begin(), m_primes.end());
  auto unique_end = unique(m_primes.begin(), m_primes.end());
  m_primes.resize(distance(m_primes.begin(), unique_end));
}

bool Primes_Calculator::is_prime(int n)
{
  if (n <= 0 || n == 1)
    return false;
  if (n == 2)
    return true;
  if ((n % 2) == 0)
    return false;
  for (int d = 3; d * d <= n; d += 2) {
    if ((n % d) == 0)
      return false;
  }
  return true;
}
