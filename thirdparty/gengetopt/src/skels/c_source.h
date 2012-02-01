/*
 * File automatically generated by
 * gengen 1.1 by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#ifndef C_SOURCE_GEN_CLASS_H
#define C_SOURCE_GEN_CLASS_H

#include <string>
#include <iostream>

using std::string;
using std::ostream;

class c_source_gen_class
{
 protected:
  string args_info;
  bool check_possible_values;
  bool check_required_options;
  string clear_arg;
  bool cmd_list;
  string command_line;
  bool conf_parser;
  string custom_getopt;
  string description;
  bool do_generate_strdup;
  string file_save_loop;
  string final_exit;
  string free;
  string full_help_option_print;
  bool generate_string_parser;
  string generator_version;
  string getopt_string;
  string given_init;
  string handle_dependencies;
  string handle_group;
  string handle_no_short_option;
  string handle_option;
  string handle_required;
  bool handle_unamed;
  bool has_hidden;
  string header_file_ext;
  string help_option_print;
  bool include_getopt;
  string init_args_info;
  string list_def;
  string list_free;
  string long_option_struct;
  string multiple_fill_array;
  bool multiple_options;
  bool multiple_token_functions;
  bool multiple_token_vars;
  bool no_package;
  string option_values;
  string package_var_name;
  string parser_name;
  string purpose;
  string reset_groups;
  string source_name;
  string struct_def;
  string update_multiple_given;
  string usage_string;
  string version_var_name;

 public:
  c_source_gen_class() :
    check_possible_values (false), check_required_options (false), cmd_list (false), conf_parser (false), do_generate_strdup (false), generate_string_parser (false), handle_unamed (false), has_hidden (false), include_getopt (false), multiple_options (false), multiple_token_functions (false), multiple_token_vars (false), no_package (false)
  {
  }
  
  c_source_gen_class(const string &_args_info, bool _check_possible_values, bool _check_required_options, const string &_clear_arg, bool _cmd_list, const string &_command_line, bool _conf_parser, const string &_custom_getopt, const string &_description, bool _do_generate_strdup, const string &_file_save_loop, const string &_final_exit, const string &_free, const string &_full_help_option_print, bool _generate_string_parser, const string &_generator_version, const string &_getopt_string, const string &_given_init, const string &_handle_dependencies, const string &_handle_group, const string &_handle_no_short_option, const string &_handle_option, const string &_handle_required, bool _handle_unamed, bool _has_hidden, const string &_header_file_ext, const string &_help_option_print, bool _include_getopt, const string &_init_args_info, const string &_list_def, const string &_list_free, const string &_long_option_struct, const string &_multiple_fill_array, bool _multiple_options, bool _multiple_token_functions, bool _multiple_token_vars, bool _no_package, const string &_option_values, const string &_package_var_name, const string &_parser_name, const string &_purpose, const string &_reset_groups, const string &_source_name, const string &_struct_def, const string &_update_multiple_given, const string &_usage_string, const string &_version_var_name) :
    args_info (_args_info), check_possible_values (_check_possible_values), check_required_options (_check_required_options), clear_arg (_clear_arg), cmd_list (_cmd_list), command_line (_command_line), conf_parser (_conf_parser), custom_getopt (_custom_getopt), description (_description), do_generate_strdup (_do_generate_strdup), file_save_loop (_file_save_loop), final_exit (_final_exit), free (_free), full_help_option_print (_full_help_option_print), generate_string_parser (_generate_string_parser), generator_version (_generator_version), getopt_string (_getopt_string), given_init (_given_init), handle_dependencies (_handle_dependencies), handle_group (_handle_group), handle_no_short_option (_handle_no_short_option), handle_option (_handle_option), handle_required (_handle_required), handle_unamed (_handle_unamed), has_hidden (_has_hidden), header_file_ext (_header_file_ext), help_option_print (_help_option_print), include_getopt (_include_getopt), init_args_info (_init_args_info), list_def (_list_def), list_free (_list_free), long_option_struct (_long_option_struct), multiple_fill_array (_multiple_fill_array), multiple_options (_multiple_options), multiple_token_functions (_multiple_token_functions), multiple_token_vars (_multiple_token_vars), no_package (_no_package), option_values (_option_values), package_var_name (_package_var_name), parser_name (_parser_name), purpose (_purpose), reset_groups (_reset_groups), source_name (_source_name), struct_def (_struct_def), update_multiple_given (_update_multiple_given), usage_string (_usage_string), version_var_name (_version_var_name)
  {
  }

  virtual ~c_source_gen_class()
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

  void set_args_info(const string &_args_info)
  {
    args_info = _args_info;
  }

  void set_check_possible_values(bool _check_possible_values)
  {
    check_possible_values = _check_possible_values;
  }

  void set_check_required_options(bool _check_required_options)
  {
    check_required_options = _check_required_options;
  }

  virtual void generate_clear_arg(ostream &stream, unsigned int indent) = 0;

  void set_clear_arg(const string &_clear_arg)
  {
    clear_arg = _clear_arg;
  }

  void set_cmd_list(bool _cmd_list)
  {
    cmd_list = _cmd_list;
  }

  void set_command_line(const string &_command_line)
  {
    command_line = _command_line;
  }

  void set_conf_parser(bool _conf_parser)
  {
    conf_parser = _conf_parser;
  }

  virtual void generate_custom_getopt(ostream &stream, unsigned int indent) = 0;

  void set_custom_getopt(const string &_custom_getopt)
  {
    custom_getopt = _custom_getopt;
  }

  void set_description(const string &_description)
  {
    description = _description;
  }

  void set_do_generate_strdup(bool _do_generate_strdup)
  {
    do_generate_strdup = _do_generate_strdup;
  }

  virtual void generate_file_save_loop(ostream &stream, unsigned int indent) = 0;

  void set_file_save_loop(const string &_file_save_loop)
  {
    file_save_loop = _file_save_loop;
  }

  void set_final_exit(const string &_final_exit)
  {
    final_exit = _final_exit;
  }

  virtual void generate_free(ostream &stream, unsigned int indent) = 0;

  void set_free(const string &_free)
  {
    free = _free;
  }

  virtual void generate_full_help_option_print(ostream &stream, unsigned int indent) = 0;

  void set_full_help_option_print(const string &_full_help_option_print)
  {
    full_help_option_print = _full_help_option_print;
  }

  void set_generate_string_parser(bool _generate_string_parser)
  {
    generate_string_parser = _generate_string_parser;
  }

  void set_generator_version(const string &_generator_version)
  {
    generator_version = _generator_version;
  }

  void set_getopt_string(const string &_getopt_string)
  {
    getopt_string = _getopt_string;
  }

  virtual void generate_given_init(ostream &stream, unsigned int indent) = 0;

  void set_given_init(const string &_given_init)
  {
    given_init = _given_init;
  }

  virtual void generate_handle_dependencies(ostream &stream, unsigned int indent) = 0;

  void set_handle_dependencies(const string &_handle_dependencies)
  {
    handle_dependencies = _handle_dependencies;
  }

  virtual void generate_handle_group(ostream &stream, unsigned int indent) = 0;

  void set_handle_group(const string &_handle_group)
  {
    handle_group = _handle_group;
  }

  virtual void generate_handle_no_short_option(ostream &stream, unsigned int indent) = 0;

  void set_handle_no_short_option(const string &_handle_no_short_option)
  {
    handle_no_short_option = _handle_no_short_option;
  }

  virtual void generate_handle_option(ostream &stream, unsigned int indent) = 0;

  void set_handle_option(const string &_handle_option)
  {
    handle_option = _handle_option;
  }

  virtual void generate_handle_required(ostream &stream, unsigned int indent) = 0;

  void set_handle_required(const string &_handle_required)
  {
    handle_required = _handle_required;
  }

  void set_handle_unamed(bool _handle_unamed)
  {
    handle_unamed = _handle_unamed;
  }

  void set_has_hidden(bool _has_hidden)
  {
    has_hidden = _has_hidden;
  }

  void set_header_file_ext(const string &_header_file_ext)
  {
    header_file_ext = _header_file_ext;
  }

  virtual void generate_help_option_print(ostream &stream, unsigned int indent) = 0;

  void set_help_option_print(const string &_help_option_print)
  {
    help_option_print = _help_option_print;
  }

  void set_include_getopt(bool _include_getopt)
  {
    include_getopt = _include_getopt;
  }

  virtual void generate_init_args_info(ostream &stream, unsigned int indent) = 0;

  void set_init_args_info(const string &_init_args_info)
  {
    init_args_info = _init_args_info;
  }

  virtual void generate_list_def(ostream &stream, unsigned int indent) = 0;

  void set_list_def(const string &_list_def)
  {
    list_def = _list_def;
  }

  virtual void generate_list_free(ostream &stream, unsigned int indent) = 0;

  void set_list_free(const string &_list_free)
  {
    list_free = _list_free;
  }

  virtual void generate_long_option_struct(ostream &stream, unsigned int indent) = 0;

  void set_long_option_struct(const string &_long_option_struct)
  {
    long_option_struct = _long_option_struct;
  }

  virtual void generate_multiple_fill_array(ostream &stream, unsigned int indent) = 0;

  void set_multiple_fill_array(const string &_multiple_fill_array)
  {
    multiple_fill_array = _multiple_fill_array;
  }

  void set_multiple_options(bool _multiple_options)
  {
    multiple_options = _multiple_options;
  }

  void set_multiple_token_functions(bool _multiple_token_functions)
  {
    multiple_token_functions = _multiple_token_functions;
  }

  void set_multiple_token_vars(bool _multiple_token_vars)
  {
    multiple_token_vars = _multiple_token_vars;
  }

  void set_no_package(bool _no_package)
  {
    no_package = _no_package;
  }

  virtual void generate_option_values(ostream &stream, unsigned int indent) = 0;

  void set_option_values(const string &_option_values)
  {
    option_values = _option_values;
  }

  void set_package_var_name(const string &_package_var_name)
  {
    package_var_name = _package_var_name;
  }

  void set_parser_name(const string &_parser_name)
  {
    parser_name = _parser_name;
  }

  void set_purpose(const string &_purpose)
  {
    purpose = _purpose;
  }

  virtual void generate_reset_groups(ostream &stream, unsigned int indent) = 0;

  void set_reset_groups(const string &_reset_groups)
  {
    reset_groups = _reset_groups;
  }

  void set_source_name(const string &_source_name)
  {
    source_name = _source_name;
  }

  virtual void generate_struct_def(ostream &stream, unsigned int indent) = 0;

  void set_struct_def(const string &_struct_def)
  {
    struct_def = _struct_def;
  }

  virtual void generate_update_multiple_given(ostream &stream, unsigned int indent) = 0;

  void set_update_multiple_given(const string &_update_multiple_given)
  {
    update_multiple_given = _update_multiple_given;
  }

  void set_usage_string(const string &_usage_string)
  {
    usage_string = _usage_string;
  }

  void set_version_var_name(const string &_version_var_name)
  {
    version_var_name = _version_var_name;
  }

  void generate_c_source(ostream &stream, unsigned int indent = 0);
  
};

#endif // C_SOURCE_GEN_CLASS_H