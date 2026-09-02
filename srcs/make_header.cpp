#include "enby.hpp"
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <algorithm>

// Structure to hold language-specific comment formats
struct CommentStyle {
  std::string start;
  std::string end;
  char fill;
  int length;
};

// Helper to determine comment style based on filename/extension
CommentStyle getStyle(const std::string& filename) {
  auto endsWith = [](const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() && 
    str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
  };

  // Extension groups
  std::vector<std::string> c_style = {".c", ".h", ".cc", ".hh", ".cpp", ".hpp", ".tpp", ".ipp", ".cxx", ".go", ".rs", ".php", ".java", ".kt", ".kts", ".css", ".scss"};
  std::vector<std::string> html_style = {".htm", ".html", ".xml"};
  std::vector<std::string> js_style = {".js", ".ts"};
  std::vector<std::string> tex_style = {".tex"};
  std::vector<std::string> ml_style = {".ml", ".mli", ".mll", ".mly"};
  std::vector<std::string> vim_style = {".vim", "vimrc"};
  std::vector<std::string> asm_style = {".el", "emacs", ".asm", ".s"};
  std::vector<std::string> fortran_style = {".f90", ".f95", ".f03", ".f", ".for"};

  for (const auto& ext : c_style) if (endsWith(filename, ext)) return {"/*", "*/", '*', 80};
  for (const auto& ext : html_style) if (endsWith(filename, ext)) return {"<!--", "-->", '*', 80};
  for (const auto& ext : js_style) if (endsWith(filename, ext)) return {"//", "//", '*', 80};
  for (const auto& ext : tex_style) if (endsWith(filename, ext)) return {"%", "%", '*', 80};
  for (const auto& ext : ml_style) if (endsWith(filename, ext)) return {"(*", "*)", '*', 80};
  for (const auto& ext : vim_style) if (endsWith(filename, ext)) return {"\"", "\"", '*', 80};
  for (const auto& ext : asm_style) if (endsWith(filename, ext)) return {";", ";", '*', 80};
  for (const auto& ext : fortran_style) if (endsWith(filename, ext)) return {"!", "!", '/', 80};
  if (endsWith(filename, ".lua")) return {"--", "--", '-', 80};
  if (endsWith(filename, ".py")) return {"#", "#", '*', 79};

  // Default style (Makefiles, bash, unknown)
  return {"#", "#", '*', 80};
}

std::string makeHeader(const std::string& filename, std::string existingCreated = "") {
  // 1. Get environment variables
  const char* user_env = std::getenv("USER");
  std::string user = user_env ? user_env : "marvin";
  
  const char* mail_env = std::getenv("MAIL");
  std::string mail = mail_env ? mail_env : "marvin@42.fr";

  // 2. Format the date
  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y/%m/%d %H:%M:%S");
  std::string date = oss.str();

  // 3. Prepare the text variables
  std::string author = "By: " + user + " <" + mail + ">";
  std::string created;
  if (!existingCreated.empty()) {
    created = existingCreated;
  } else {
    created = "Created: " + date + " by " + user;
  }
  std::string updated = "Updated: " + date + " by " + user;

  const std::string ascii[7] = {
    "        :::      ::::::::",
    "      :+:      :+:    :+:",
    "    +:+ +:+         +:+  ",
    "  +#+  +:+       +#+     ",
    "+#+#+#+#+#+   +#+        ",
    "     #+#    #+#          ",
    "    ###   ########.fr    "
  };

  // 4. Get the comment style for this specific file
  CommentStyle style = getStyle(filename);
  int margin = 5;

  // 5. Helper lambda to generate top and bottom border lines
  auto makeBorder = [&]() {
    int fillCount = style.length - style.start.length() - style.end.length() - 2;
    std::string fillStr(std::max(0, fillCount), style.fill);
    return style.start + " " + fillStr + " " + style.end + "\n";
  };

  // 6. Helper lambda to generate text lines (mimics Vimscript's `s:textline`)
  auto makeLine = [&](std::string left, const std::string& right) {
    left.erase(std::remove(left.begin(), left.end(), '\r'), left.end());
    int maxLeftLen = style.length - (margin * 2) - right.length();
    if (left.length() > (size_t)maxLeftLen) {
      left = left.substr(0, maxLeftLen);
    }

    int spacesCount = style.length - (margin * 2) - left.length() - right.length();
    std::string spaces(std::max(0, spacesCount), ' ');
      
    std::string leftMargin(std::max(0, margin - (int)style.start.length()), ' ');
    std::string rightMargin(std::max(0, margin - (int)style.end.length()), ' ');

    return style.start + leftMargin + left + spaces + right + rightMargin + style.end + "\n";
  };

  // 7. Assemble header
  std::string header;
  header += makeBorder();
  header += makeLine("", "");
  header += makeLine("", ascii[0]);
  header += makeLine(filename, ascii[1]);
  header += makeLine("", ascii[2]);
  header += makeLine(author, ascii[3]);
  header += makeLine("", ascii[4]);
  header += makeLine(created, ascii[5]);
  header += makeLine(updated, ascii[6]);
  header += makeLine("", "");
  header += makeBorder();
  header += "\n";

  return header;
}
