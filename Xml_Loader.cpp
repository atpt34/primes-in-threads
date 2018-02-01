#include "Xml_Loader.h"
#include "Interval.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::to_string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cout;

using std::stringstream;
using std::istringstream;

Xml_Loader::Xml_Loader(const string& name)
{
  load(name);
}

void Xml_Loader::load(const string& name)
{
  ifstream ifs{name};
  if (!ifs.is_open())
    throw Xml_Exception{"Unable to open file\n"};
  stringstream buf;
  buf << ifs.rdbuf();
  data = buf.str();
}

template <typename T>
vector<T> Xml_Loader::parse(const Xml_Struct& xs)
{
  istringstream is{data};
  string in;
  is >> in;
  if (in != xs.root_tag.beg_tag) 
    throw Xml_Exception{string{"No start tag "} + xs.root_tag.beg_tag};
  //cout << in << '\n';
  is >> in;
  if (in != xs.data_tag.beg_tag) 
    throw Xml_Exception{string{"No start tag "} + xs.data_tag.beg_tag};
  //cout << in << '\n';
  vector<T> vd;
  while (true) {
    is >> in;
    //cout << in << '\n';
    if (in == xs.data_tag.end_tag) {
      break;
    } else {
      if (in != xs.dataelem_tag.beg_tag)
        throw Xml_Exception{string{"No start tag "} + xs.dataelem_tag.beg_tag};
      vector<string> vp(xs.param_tag.size());
      for (decltype(vp)::size_type i = 0; i < vp.size(); ++i) {
        is >> in;
        //cout << in << '\n';
        if (in != xs.param_tag[i].beg_tag) 
          throw Xml_Exception{string{"No start tag "} + xs.param_tag[i].beg_tag};
        is >> in;
        //cout << in << '\n';
        vp[i] = in;
        is >> in;
        //cout << in << '\n';
        if (in != xs.param_tag[i].end_tag) 
          throw Xml_Exception{string{"No end tag "} + xs.param_tag[i].end_tag};
      }
      is >> in;
      //cout << in << '\n';
      if (in != xs.dataelem_tag.end_tag) 
        throw Xml_Exception{string{"No end tag "} + xs.dataelem_tag.end_tag};
      try {
        vd.push_back(create_data<T>(vp));
      } catch (...) {
        throw Xml_Exception{"Invalid data creation"};
      }
    }
  }
  is >> in;
  //cout << in << '\n';
  if (in != xs.root_tag.end_tag) 
    throw Xml_Exception{string{"No end tag "} + xs.root_tag.end_tag};
  return vd;
}

template 
std::vector<Interval> Xml_Loader::parse(const Xml_Struct& xs);

template <typename T>
void Xml_Loader::save(const std::string& xml_file, const Xml_Struct& xs, const std::vector<T>& vt)
{
  ofstream ofs{xml_file};
  if (!ofs.is_open())
    throw Xml_Exception{"Unable to open file\n"};
  ofs << xs.root_tag.beg_tag << '\n';
  ofs << xs.data_tag.beg_tag << '\n';
  for (const auto& d : vt) {
    ofs << xs.dataelem_tag.beg_tag << ' ';
    ofs << to_string(d) << ' ';
    ofs << xs.dataelem_tag.end_tag << '\n';
  }
  ofs << xs.data_tag.end_tag << '\n';
  ofs << xs.root_tag.end_tag << '\n';
}

template 
void Xml_Loader::save(const std::string& xml_file, const Xml_Struct& xs, const std::vector<int>& vt);

void Xml_Loader::print_data()
{
  cout << data << '\n';
}


