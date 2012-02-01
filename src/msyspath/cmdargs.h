/* cmdargs.h */

/* File autogenerated by gengetopt version 2.20  */

#ifndef CMDARGS_H
#define CMDARGS_H

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef CMDLINE_PARSER_PACKAGE
#define CMDLINE_PARSER_PACKAGE "msyspath.exe"
#endif

#ifndef CMDLINE_PARSER_VERSION
#define CMDLINE_PARSER_VERSION "1.0.0"
#endif

struct gengetopt_args_info
{
  const char *help_help; /* Print help and exit help description.  */
  const char *version_help; /* Print version and exit help description.  */
  const char *windows_help; /* print Windows form of NAMEs (C:\\WINNT) help description.  */
  const char *mixed_help; /* like --windows, but with regular slashes (C:/WINNT) help description.  */
  const char *unix_help; /* print Unix form of NAMEs (/cygdrive/c/winnt) help description.  */
  const char *absolute_help; /* output absolute path help description.  */
  const char *path_help; /* NAME is a PATH list (i.e., '/bin:/usr/bin') help description.  */
  const char *file_help; /* read FILE for input; use - to read from STDIN help description.  */
  
  int help_given ;	/* Whether help was given.  */
  int version_given ;	/* Whether version was given.  */
  int windows_given ;	/* Whether windows was given.  */
  int mixed_given ;	/* Whether mixed was given.  */
  int unix_given ;	/* Whether unix was given.  */
  int absolute_given ;	/* Whether absolute was given.  */
  int path_given ;	/* Whether path was given.  */
  int file_given ;	/* Whether file was given.  */

  char **inputs ; /* unamed options */
  unsigned inputs_num ; /* unamed options number */
  int Output_type_options_group_counter; /* counter for group Output_type_options */
} ;

extern const char *gengetopt_args_info_purpose;
extern const char *gengetopt_args_info_usage;
extern const char *gengetopt_args_info_help[];

int cmdline_parser (int argc, char * const *argv,
  struct gengetopt_args_info *args_info);
int cmdline_parser2 (int argc, char * const *argv,
  struct gengetopt_args_info *args_info,
  int override, int initialize, int check_required);
int cmdline_parser_file_save(const char *filename,
  struct gengetopt_args_info *args_info);

void cmdline_parser_print_help(void);
void cmdline_parser_print_version(void);

void cmdline_parser_init (struct gengetopt_args_info *args_info);
void cmdline_parser_free (struct gengetopt_args_info *args_info);

int cmdline_parser_required (struct gengetopt_args_info *args_info,
  const char *prog_name);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* CMDARGS_H */
