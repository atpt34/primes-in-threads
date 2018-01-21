#include "Xml_Loader.h"
#include <iostream>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;

Xml_Loader::Xml_Loader(string name)
{
  ifstream ifs{name};
  if (!ifs.is_open())
    throw Xml_Exception{"Unable to open file\n"};
  string in;
  ifs >> in;
  if (in != "<root>") 
    throw Xml_Exception{"No start tag '<root>'!\n"};
  ifs >> in;
  if (in == "<intervals>") {
    while (true) {
      ifs >> in;
      if (in == "</intervals>")
        break; 
      if (in != "<interval>") 
        throw Xml_Exception{"No start tag '<interval>'!\n"};
      ifs >> in;
      if (in != "<low>") 
        throw Xml_Exception{"No start tag '<low>'!\n"};
      int low;
      ifs >> low;
      ifs >> in;
      if (in != "</low>") 
        throw Xml_Exception{"No end tag '</low>'!\n"};
      ifs >> in;
      if (in != "<high>") 
        throw Xml_Exception{"No start tag '<high>'!\n"};
      int high;
      ifs >> high;
      ifs >> in;
      if (in != "</high>") 
        throw Xml_Exception{"No end tag '</high>'!\n"};
      ifs >> in;
      if (in != "</interval>") 
        throw Xml_Exception{"No end tag '</interval>'!\n"};
      m_vi.emplace_back(low, high);
    }
  }
  ifs >> in;
  if (in != "</root>") 
    throw Xml_Exception{"No end tag '</root>'!\n"};
}

void Xml_Loader::save(string xml_file, const vector<int>& data)
{
  ofstream ofs{xml_file};
  if (!ofs.is_open())
    throw Xml_Exception{"Unable to open file\n"};
  ofs << "<root>" << '\n';
  ofs << "<primes>" << '\n';
  for (const auto& p : data) {
    ofs << p << '\n';
  }
  ofs << '\n';
  ofs << "</primes>" << '\n';
  ofs << "</root>" << '\n';
}

void Xml_Loader::print_intervals()
{
  cout << '\n';
  for (const auto& i : m_vi)
    cout << i.get_low() << ',' << i.get_high() << '\n';
  cout << '\n';
}
