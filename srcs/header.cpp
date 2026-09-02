#include "enby.hpp"
#include <string>
/* #include <chrono> */
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstdlib>

std::string makeHeader(const std::string& filename) {
    // 1. Get user and email from environment variables (fallback to marvin)
    const char* user_env = std::getenv("USER");
    std::string user = user_env ? user_env : "marvin";
    
    const char* mail_env = std::getenv("MAIL");
    std::string mail = mail_env ? mail_env : "marvin@42.fr";

    // 2. Format the current date exactly as "%Y/%m/%d %H:%M:%S"
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y/%m/%d %H:%M:%S");
    std::string date = oss.str();

    // 3. Prepare the dynamic text strings
    std::string author = "By: " + user + " <" + mail + ">";
    std::string created = "Created: " + date + " by " + user;
    std::string updated = "Updated: " + date + " by " + user;

    // 4. The 42 ASCII art (each string is exactly 25 chars wide)
    const std::string ascii[7] = {
        "        :::      ::::::::",
        "      :+:      :+:    :+:",
        "    +:+ +:+         +:+  ",
        "  +#+  +:+       +#+     ",
        "+#+#+#+#+#+   +#+        ",
        "     #+#    #+#          ",
        "    ###   ########.fr    "
    };

    // 5. Lambda to format standard text lines (80 chars total)
    // "/*   " (5 chars) + left_text + spaces + right_ascii + "   */" (5 chars) = 80
    // So inner space available is 70 chars.
    auto makeLine = [](std::string left, const std::string& right) {
        // Prevent overflow if filename/author is unusually long
        if (left.length() > 45) {
            left = left.substr(0, 45); 
        }
        
        std::string res = "/*   " + left;
        int spaces = 70 - left.length() - right.length();
        if (spaces > 0) {
            res.append(spaces, ' ');
        }
        res += right + "   */\n";
        return res;
    };

    // 6. Assemble the final header string
    std::string topBottom = "/* ************************************************************************** */\n";
    std::string emptyLine = makeLine("", "");

    std::string header;
    header += topBottom;
    header += emptyLine;
    header += makeLine("", ascii[0]);
    header += makeLine(filename, ascii[1]);
    header += makeLine("", ascii[2]);
    header += makeLine(author, ascii[3]);
    header += makeLine("", ascii[4]);
    header += makeLine(created, ascii[5]);
    header += makeLine(updated, ascii[6]);
    header += emptyLine;
    header += topBottom;
    header += "\n"; 

    return header;
}
