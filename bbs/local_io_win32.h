/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2015,WWIV Software Services             */
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
#ifndef __INCLUDED_LOCAL_IO_WIN32_H__
#define __INCLUDED_LOCAL_IO_WIN32_H__
// Always declare wwiv_windows.h first to avoid collisions on defines.
#include "bbs/wwiv_windows.h"

#include <string>

#include "bbs/keycodes.h"
#include "bbs/local_io.h"
#include "core/file.h"

// This C++ class should encompass all Local Input/Output from The BBS.
// You should use a routine in here instead of using printf, puts, etc.

class WStatus;
class WSession;

class Win32ConsoleIO : public LocalIO {
 public:
  // Constructor/Destructor
  Win32ConsoleIO();
  Win32ConsoleIO(const LocalIO& copy) = delete;
  virtual ~Win32ConsoleIO();

  virtual void LocalGotoXY(int x, int y) override;
  virtual int  WhereX() override;
  virtual int  WhereY() override;
  virtual void LocalLf() override;
  virtual void LocalCr() override;
  virtual void LocalCls() override;
  virtual void LocalClrEol() override;
  virtual void LocalBackspace() override;
  virtual void LocalPutchRaw(unsigned char ch) override;
  // Overridden by TestLocalIO in tests
  virtual void LocalPutch(unsigned char ch) override;
  virtual void LocalPuts(const std::string& text) override;
  virtual void LocalXYPuts(int x, int y, const std::string& text) override;
  virtual int  LocalPrintf(const char *formatted_text, ...) override;
  virtual int  LocalXYPrintf(int x, int y, const char *formatted_text, ...) override;
  virtual int  LocalXYAPrintf(int x, int y, int nAttribute, const char *formatted_text, ...) override;
  virtual void set_protect(int l) override;
  virtual void savescreen() override;
  virtual void restorescreen() override;
  virtual void skey(char ch) override;
  virtual void tleft(bool bCheckForTimeOut) override;
  virtual void UpdateTopScreen(WStatus* pStatus, WSession *pSession, int nInstanceNumber) override;
  virtual bool LocalKeyPressed() override;
  virtual unsigned char LocalGetChar() override;
  virtual void SaveCurrentLine(char *cl, char *atr, char *xl, char *cc) override;
  virtual void MakeLocalWindow(int x, int y, int xlen, int ylen) override;
  virtual void SetCursor(int cursorStyle) override;
  virtual void LocalWriteScreenBuffer(const char *buffer) override;
  virtual int  GetDefaultScreenBottom() override;

  virtual void LocalEditLine(char *s, int len, int editor_status, int *returncode, char *ss) override;
  virtual void UpdateNativeTitleBar() override;

private:
  virtual void LocalFastPuts(const std::string &text) override;

private:
  std::string m_chatReason;
  bool ExtendedKeyWaiting;

  COORD  m_cursorPosition;
  HANDLE m_hConOut;
  HANDLE m_hConIn;
  CONSOLE_SCREEN_BUFFER_INFO m_consoleBufferInfo;
  DWORD saved_input_mode_ = 0;

  void set_attr_xy(int x, int y, int a);
  COORD m_originalConsoleSize;
};


#endif // __INCLUDED_LOCAL_IO_WIN32_H__
