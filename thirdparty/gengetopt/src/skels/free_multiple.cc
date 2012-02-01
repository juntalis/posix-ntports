/*
 * File automatically generated by
 * gengen 1.0 by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#include "free_multiple.h"

void
free_multiple_gen_class::generate_free_multiple(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  stream << "if (";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_arg)";
  stream << "\n";
  stream << indent_str;
  stream << "  {";
  stream << "\n";
  stream << indent_str;
  stream << "    for (i = 0; i < ";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_given; ++i)";
  stream << "\n";
  stream << indent_str;
  stream << "      {";
  stream << "\n";
  stream << indent_str;
  if (has_string_type)
    {
      stream << "        if (";
      generate_string (structure, stream, indent + indent_str.length ());
      stream << "->";
      generate_string (opt_var, stream, indent + indent_str.length ());
      stream << "_arg [i])";
      stream << "\n";
      stream << indent_str;
      stream << "          {";
      stream << "\n";
      stream << indent_str;
      stream << "            free (";
      generate_string (structure, stream, indent + indent_str.length ());
      stream << "->";
      generate_string (opt_var, stream, indent + indent_str.length ());
      stream << "_arg [i]); /* free ";
      generate_string (comment, stream, indent + indent_str.length ());
      stream << " */";
      stream << "\n";
      stream << indent_str;
      indent = 12;
      stream << "            ";
      generate_string (structure, stream, indent + indent_str.length ());
      stream << "->";
      generate_string (opt_var, stream, indent + indent_str.length ());
      stream << "_arg [i] = 0;";
      indent = 0;
      stream << "\n";
      stream << indent_str;
      stream << "          }";
      stream << "\n";
      stream << indent_str;
    }
  stream << "        if (";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_orig [i])";
  stream << "\n";
  stream << indent_str;
  stream << "          {";
  stream << "\n";
  stream << indent_str;
  stream << "            free (";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_orig [i]); /* free ";
  generate_string (comment, stream, indent + indent_str.length ());
  stream << " */";
  stream << "\n";
  stream << indent_str;
  indent = 12;
  stream << "            ";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_orig [i] = 0;";
  indent = 0;
  stream << "\n";
  stream << indent_str;
  stream << "          }";
  stream << "\n";
  stream << indent_str;
  stream << "      }";
  stream << "\n";
  stream << indent_str;
  if (has_string_type)
    {
      stream << "    if (";
      generate_string (structure, stream, indent + indent_str.length ());
      stream << "->";
      generate_string (opt_var, stream, indent + indent_str.length ());
      stream << "_arg [0])";
      stream << "\n";
      stream << indent_str;
      stream << "      free (";
      generate_string (structure, stream, indent + indent_str.length ());
      stream << "->";
      generate_string (opt_var, stream, indent + indent_str.length ());
      stream << "_arg [0]); /* free default string */";
      stream << "\n";
      stream << indent_str;
    }
  stream << "    free (";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_arg); /* free ";
  generate_string (comment, stream, indent + indent_str.length ());
  stream << " */";
  stream << "\n";
  stream << indent_str;
  indent = 4;
  stream << "    ";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_arg = 0;";
  indent = 0;
  stream << "\n";
  stream << indent_str;
  stream << "    free (";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_orig); /* free ";
  generate_string (comment, stream, indent + indent_str.length ());
  stream << " */";
  stream << "\n";
  stream << indent_str;
  indent = 4;
  stream << "    ";
  generate_string (structure, stream, indent + indent_str.length ());
  stream << "->";
  generate_string (opt_var, stream, indent + indent_str.length ());
  stream << "_orig = 0;";
  indent = 0;
  stream << "\n";
  stream << indent_str;
  stream << "  }";
  stream << "\n";
  stream << indent_str;
}