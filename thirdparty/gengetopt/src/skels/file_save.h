/*
 * File automatically generated by
 * gengen 1.0 by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#ifndef FILE_SAVE_GEN_CLASS_H
#define FILE_SAVE_GEN_CLASS_H

#include <string>
#include <iostream>

using std::string;
using std::ostream;

class file_save_gen_class
{
 protected:
  string arg;
  bool check_given;
  string given;
  bool has_arg;
  string opt_name;

 public:
  file_save_gen_class() :
    check_given (false), has_arg (false)
  {
  }
  
  file_save_gen_class(const string &_arg, bool _check_given, const string &_given, bool _has_arg, const string &_opt_name) :
    arg (_arg), check_given (_check_given), given (_given), has_arg (_has_arg), opt_name (_opt_name)
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

  void set_arg(const string &_arg)
  {
    arg = _arg;
  }

  void set_check_given(bool _check_given)
  {
    check_given = _check_given;
  }

  void set_given(const string &_given)
  {
    given = _given;
  }

  void set_has_arg(bool _has_arg)
  {
    has_arg = _has_arg;
  }

  void set_opt_name(const string &_opt_name)
  {
    opt_name = _opt_name;
  }

  void generate_file_save(ostream &stream, unsigned int indent = 0);
  
};

#endif // FILE_SAVE_GEN_CLASS_H
