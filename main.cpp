#include "Primes_Calculator.h"
#include "Xml_Loader.h"

int main()
{
  Xml_Loader xl("src.xml");
  Primes_Calculator pc(xl.get_intervals());
  xl.save("out.xml", pc.get_primes());
  return 0;
}
