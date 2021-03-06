#include "Xml_Loader.h"
#include "Interval.h"
#include "Primes_Calculator.h"
#include "settings.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
  try {
    Xml_Loader xl;
    if (argc > 1) {
      xl.load(argv[1]);
    } else {
      std::cout << "You can provide xml file as an argument\n";
      xl.load("src.xml");
    }
    Primes_Calculator pc;
    pc.calculate(xl.parse<Interval>(interval_xs));
    xl.save("out.xml", primes_xs, pc.get_primes());

  } catch (const Xml_Exception& xe) {
    std::cerr << xe.message << '\n';
  } catch (const std::runtime_error& re) {
    std::cerr << re.what();
  }
}
