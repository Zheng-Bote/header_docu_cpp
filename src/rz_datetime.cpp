#include "rz_datetime.h"

namespace rz_datetime {

std::string test() { return ("rz_datetime: Hello World"); }

/**
 * @brief returns the current date time
 *
 * @param format
 * human    (e.g.: 2023-03-25 15:41:32)
 * spdx     (e.g.: 2023-03-25T15:41:32CET)
 * string   (e.g.: 2023-03-25_15-41-32)
 *
 * @return const std::string
 */
const std::string currentDateTime(std::string format) {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format

  if (format.compare("human") == 0) {
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
  } else if (format.compare("spdx") == 0) {
    strftime(buf, sizeof(buf), "%Y-%m-%dT%X%Z", &tstruct);
  } else {
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);
  }
  return buf;
}

} // namespace rz_datetime
