/*
 * File automatically generated by
 * gengen 1.0 by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#ifndef MULTIPLE_OPT_STRUCT_GEN_CLASS_H
#define MULTIPLE_OPT_STRUCT_GEN_CLASS_H

#include <string>
#include <iostream>

using std::string;
using std::ostream;

class multiple_opt_struct_gen_class
{
 protected:
  string list_name;
  string type;

 public:
  multiple_opt_struct_gen_class()
  {
  }
  
  multiple_opt_struct_gen_class(const string &_list_name, const string &_type) :
    list_name (_list_name), type (_type)
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

  void set_list_name(const string &_list_name)
  {
    list_name = _list_name;
  }

  void set_type(const string &_type)
  {
    type = _type;
  }

  void generate_multiple_opt_struct(ostream &stream, unsigned int indent = 0);
  
};

#endif // MULTIPLE_OPT_STRUCT_GEN_CLASS_H
