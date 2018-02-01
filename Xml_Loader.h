#ifndef MY_XML_LOADER_H
#define MY_XML_LOADER_H

#include <string>
#include <vector>

struct Xml_Struct;

/*
  The class responsible for processing data 
  from/to specified xml file.
*/
class Xml_Loader {
public:
  Xml_Loader() = default;
  Xml_Loader(const std::string& name);
  Xml_Loader(const Xml_Loader&) = default;
  Xml_Loader(Xml_Loader&&) = default;
  ~Xml_Loader() = default;

  Xml_Loader& operator=(const Xml_Loader&) = default;
  Xml_Loader& operator=(Xml_Loader&&) = default;

  void load(const std::string& name);
  
  template <typename T>
  std::vector<T> parse(const Xml_Struct& xs);

  template <typename T>
  void save(const std::string& xml_file, const Xml_Struct& xs, const std::vector<T>& vt);

private:
  void print_data();

private:
  std::string data;
};

struct Xml_Exception {
  Xml_Exception(std::string m) : message{m} {}
  std::string message;
};

struct Xml_Elem {
  std::string beg_tag;
  std::string end_tag;
};

struct Xml_Struct {
  Xml_Elem root_tag;
  Xml_Elem data_tag;
  Xml_Elem dataelem_tag;
  std::vector<Xml_Elem> param_tag;
};


template <typename T>
T create_data(const std::vector<std::string>& vs);

#endif
