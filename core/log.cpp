/**************************************************************************/
/*                                                                        */
/*                          WWIV Version 5.x                              */
/*             Copyright (C)2014-2016 WWIV Software Services              */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/**************************************************************************/
#include "core/log.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "core/file.h"
#include "core/strings.h"
#include "core/version.h"

using std::clog;
using std::endl;
using std::map;
using std::ofstream;
using std::string;
using namespace wwiv::strings;

namespace wwiv {
namespace core {

// static
map<string, string> Logger::fn_map_;

Logger::Logger() : Logger("I") {}

Logger::Logger(const string& kind) : kind_(kind), display_fn_(Logger::DefaultDisplay) { 
  stream_ << kind_ << date_time() << " "; 
}

Logger::~Logger() {
  const string filename = Logger::fn_map_[kind_];
  if (!filename.empty()) {
    // Only try to log to a file if the filename isn't empty.
    // Otherwise just log to the screen.
    ofstream out(filename, ofstream::app);
    if (!out) {
      clog << "Unable to open log file: '" << filename << "'" << endl;
    } else {
      out << stream_.str() << endl;
    }
  }
  display_fn_(stream_.str());
}

static std::string exit_filename;

//static
void Logger::ExitLogger() {
  time_t t = time(nullptr);
  Logger() << exit_filename << " exiting at " << asctime(localtime(&t));
}

// static
void Logger::DefaultDisplay(const std::string& s) {
  clog << s << endl;
}

// static
void Logger::Init(int argc, char** argv) {
  string filename(argv[0]);
  if (ends_with(filename, ".exe") || ends_with(filename, ".EXE")) {
    filename = filename.substr(0, filename.size() - 4);
  }
  std::size_t last_slash = filename.rfind(File::pathSeparatorChar);
  if (last_slash != string::npos) {
    filename = filename.substr(last_slash + 1);
  }
  set_filename("I", StrCat(filename, ".log"));
  time_t t = time(nullptr);
  string l(asctime(localtime(&t)));
  StringTrim(&l);
  Logger() << filename << " version " << wwiv_version << beta_version
           << " (" << wwiv_date << ")";
   Logger() << filename << " starting at " << l;
   if (argc > 1) {
     string cmdline;
     for (int i = 1; i < argc; i++) {
       cmdline += argv[i];
       cmdline += " ";
     }
     Logger() << "command line: " << cmdline;
   }

  exit_filename = filename;
}

// static
string Logger::date_time() {
  time_t t = time(NULL);
  char s[255];
  strftime(s, sizeof(s), "%Y%m%d:%H%M%S", localtime(&t));
  return string(s);
}

}
}
