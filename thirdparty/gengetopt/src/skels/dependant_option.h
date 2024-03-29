/*
 * File automatically generated by
 * gengen 1.0 by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#ifndef DEPENDANT_OPTION_GEN_CLASS_H
#define DEPENDANT_OPTION_GEN_CLASS_H

#include <string>
#include <iostream>

using std::string;
using std::ostream;

class dependant_option_gen_class
{
 protected:
  string dep_option;
  string dep_option_descr;
  string option_descr;
  string option_var_name;
  string package_var_name;

 public:
  dependant_option_gen_class()
  {
  }
  
  dependant_option_gen_class(const string &_dep_option, const string &_dep_option_descr, const string &_option_descr, const string &_option_var_name, const string &_package_var_name) :
    dep_option (_dep_option), dep_option_descr (_dep_option_descr), option_descr (_option_descr), option_var_name (_option_var_name), package_var_name (_package_var_name)
  {
  }

  static void
  generate_string(const string &s, ostream &stream, unsigned int indent)
  {
    if (!indent || s.find('\n') == string::npos)
      {
        stream << s;
        return;
      }

    string::size_type pos;
    string::size_type start = 0;
    string ind (indent, ' ');
    while ( (pos=s.find('\n', start)) != string::npos)
      {
        stream << s.substr (start, (pos+1)-start);
        start = pos+1;
        if (start+1 <= s.size ())
          stream << ind;
      }
    if (start+1 <= s.size ())
      stream << s.substr (start);
  }

  void set_dep_option(const string &_dep_option)
  {
    dep_option = _dep_option;
  }

  void set_dep_option_descr(const string &_dep_option_descr)
  {
    dep_option_descr = _dep_option_descr;
  }

  void set_option_descr(const string &_option_descr)
  {
    option_descr = _option_descr;
  }

  void set_option_var_name(const string &_option_var_name)
  {
    option_var_name = _option_var_name;
  }

  void set_package_var_name(const string &_package_var_name)
  {
    package_var_name = _package_var_name;
  }

  void generate_dependant_option(ostream &stream, unsigned int indent = 0);
  
};

#endif // DEPENDANT_OPTION_GEN_CLASS_H
