/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2016, WWIV Software Services             */
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
/*                                                                        */
/**************************************************************************/
#include "bbs/printfile.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "bbs/bgetch.h"
#include "bbs/bbs.h"
#include "bbs/bbsutl.h"
#include "bbs/local_io.h"
#include "bbs/keycodes.h"
#include "bbs/pause.h"
#include "bbs/vars.h"
#include "bbs/wconstants.h"
#include "bbs/wsession.h"
#include "core/wwivport.h"
#include "core/file.h"
#include "core/strings.h"
#include "core/wwivassert.h"

using std::string;
using std::unique_ptr;
using namespace wwiv::strings;

char *get_file(const string& filename, long *len) {
  File file(filename);
  if (!file.Open(File::modeBinary | File::modeReadOnly)) {
    *len = 0L;
    return nullptr;
  }

  long lFileSize = file.GetLength();
  char* pszFileText = static_cast<char *>(malloc(lFileSize + 50));
  if (pszFileText == nullptr) {
    *len = 0L;
    return nullptr;
  }
  *len = static_cast<long>(file.Read(pszFileText, lFileSize));
  return pszFileText;
}

/**
 * Creates the fully qualified filename to display adding extensions and directories as needed.
 */
const string CreateFullPathToPrint(const string& basename) {
  std::vector<string> dirs { session()->language_dir, session()->config()->gfilesdir()};
  for (const auto& base : dirs) {
    File file(base, basename);
    if (basename.find('.') != string::npos) {
      // We have a file with extension.
      if (file.Exists()) {
        return file.full_pathname();
      }
      // Since no wwiv filenames contain embedded dots skip to the next directory.
      continue;
    }
    const string root_filename = file.full_pathname();
    if (session()->user()->HasAnsi()) {
      if (session()->user()->HasColor()) {
        // ANSI and color
        string candidate = StringPrintf("%s.ans", root_filename.c_str());
        if (File::Exists(candidate)) {
          return candidate;
        }
      }
      // ANSI.
      string candidate = StringPrintf("%s.b&w", root_filename.c_str());
      if (File::Exists(candidate)) {
        return candidate;
      }
    }
    // ANSI/Color optional
    string candidate = StringPrintf("%s.msg", root_filename.c_str());
    if (File::Exists(candidate)) {
      return candidate;
    }
  }
  // Nothing matched, return the input.
  return basename;
}

/**
 * Prints the file file_name.  Returns true if the file exists and is not
 * zero length.  Returns false if the file does not exist or is zero length
 *
 * @param file_name Name of the file to display
 * @param bAbortable If true, a keyboard input may abort the display
 * @param bForcePause Should pauses be used even for ANSI files - Normally
 *        pause on screen is disabled for ANSI files.
 *
 * @return true if the file exists and is not zero length
 */
bool printfile(const string& filename, bool bAbortable, bool bForcePause) {
  string full_path_name = CreateFullPathToPrint(filename);
  File f(full_path_name);
  if (!f.Exists()) {
	  // No need to print a file that does not exist.
	  return false;
  }
  if (!f.IsFile()) {
	  // Not a file, no need to print a file that is not a file.
	  return false;
  }
  long lFileSize;
  unique_ptr<char[], void (*)(void*)> ss(get_file(full_path_name.c_str(), &lFileSize), &std::free);
  if (!ss) {
    return false;
  }
  long lCurPos = 0;
  bool bHasAnsi = false;
  while (lCurPos < lFileSize && !hangup) {
    if (ss[lCurPos] == ESC) {
      // if we have an ESC, then this file probably contains
      // an ansi sequence
      bHasAnsi = true;
    } else if (ss[lCurPos] == CZ) {
      // We are done here on a control-Z since that's DOS EOF.  Also ANSI
      // files created with PabloDraw expect that anything after a Control-Z
      // is fair game for metadata and includes SAUCE metadata after it which
      // we do not want to render in the bbs.
      break;
    }
    if (bHasAnsi && !bForcePause) {
      // If this is an ANSI file, then don't pause
      // (since we may be moving around
      // on the screen, unless the caller tells us to pause anyway)
      lines_listed = 0;
    }
    bout.bputch(ss[lCurPos++], true);
    if (bAbortable) {
      bool abort = false;
      checka(&abort);
      if (abort) {
        break;
      }
      if (bkbhit()) {
        char ch = bgetch();
        if (ch == ' ') {
          break;
        }
      }
    }
  }
  bout.FlushOutComChBuffer();
  // If the file is empty, lets' return false here since nothing was displayed.
  return lFileSize > 0;
}

/**
 * Displays a file locally, using LIST util if so defined in WWIV.INI,
 * otherwise uses normal TTY output.
 */
void print_local_file(const string& ss) {
  printfile(ss);
  bout.nl(2);
  pausescr();
}

