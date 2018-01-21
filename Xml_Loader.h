#ifndef MY_XML_LOADER_H
#define MY_XML_LOADER_H

#include <string>
#include <vector>

#include "Interval.h"

/*
  The class responsible for processing intervals 
  from/to specified xml file.
*/
class Xml_Loader {
public:
  Xml_Loader() = default;
  Xml_Loader(std::string name);
  Xml_Loader(const Xml_Loader&) = default;
  Xml_Loader(Xml_Loader&&) = default;
  ~Xml_Loader() = default;

  Xml_Loader& operator=(const Xml_Loader&) = default;
  Xml_Loader& operator=(Xml_Loader&&) = default;

  const std::vector<Interval>& get_intervals() const { return m_vi; }
  void save(std::string xml_file, const std::vector<int>& p);

private:
  void print_intervals();

private:
  std::vector<Interval> m_vi;
};

struct Xml_Exception {
  Xml_Exception(std::string m) : message{m} {}
  std::string message;
};

#endif
