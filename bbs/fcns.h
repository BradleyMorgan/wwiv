/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.0x                         */
/*             Copyright (C)1998-2015, WWIV Software Services             */
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
#ifndef __INCLUDED_FCNS_H__
#define __INCLUDED_FCNS_H__

#include <cstdint>
#include <ctime>
#include <memory>
#include <string>

#include "core/file.h"
#include "sdk/vardec.h"
#include "sdk/net.h"

namespace wwiv {
namespace menus {
class MenuInstanceData;
}
}

class WUser;

// File: bbsutl.cpp
#include "bbs/bbsutl.h"

// File: bbsutl1.cpp
#include "bbs/bbsutl1.h"

// File: bbsutl2.cpp

std::string ctypes(int num);
void osan(const std::string& text, bool *abort, bool *next);
std::string strip_to_node(const std::string& txt);

// File: bgetch.cpp
#include "bbs/bgetch.h"

// File: bputch.cpp
#include "bbs/bputch.h"

// File: colors.cpp

void get_colordata();
void save_colordata();
void list_ext_colors();
void color_config();
void buildcolorfile();

// File: com.cpp
#include "bbs/com.h"

// File: connect1.cpp
#include "bbs/connect1.h"

// File: defaults.cpp

void select_editor();
const std::string DescribeColorCode(int nColorCode);
void color_list();
void config_qscan();
void enter_regnum();
void defaults(wwiv::menus::MenuInstanceData * MenuData);
void config_scan_plus(int type);


// File: diredit.cpp

void dlboardedit();


// File: dirlist.cpp

void dirlist(int mode);


// File: dupphone.cpp

void add_phone_number(int usernum, const char *phone);
void delete_phone_number(int usernum, const char *phone);
int  find_phone_number(const char *phone);


// File: events.cpp

void init_events();
void get_next_forced_event();
void cleanup_events();
void check_event();
void run_event(int evnt);
void eventedit();


// File: execexternal.cpp

int ExecuteExternalProgram(const std::string& commandLine, int nFlags);


// File: extract.cpp

void extract_mod(const char *b, long nLength, time_t tDateTime);
void extract_out(char *b, long nLength, const char *pszTitle, time_t tDateTime);
bool upload_mod(int nDirectoryNumber, const char *pszFileName, const char *pszDescription);


// File: finduser.cpp

int finduser(const std::string& searchString);
int finduser1(const std::string& searchString);


// File: gfiles.cpp

gfilerec *read_sec(int sn, int *nf);
void gfiles();


// File: gfledit.cpp

void modify_sec(int n);
void gfileedit();
bool fill_sec(int sn);


// File: hop.cpp

void HopSub();
void HopDir();


// File: inetmsg.cpp

void get_user_ppp_addr();
void send_inet_email();
bool check_inet_addr(const char *inetaddr);
char *read_inet_addr(char *pszInternetEmailAddress, int nUserNumber);
void write_inet_addr(const char *pszInternetEmailAddress, int nUserNumber);
void send_inst_sysstr(int whichinst, const char *pszSendString);


// File: instmsg.cpp

void send_inst_str(int whichinst, const char *pszSendString);
void send_inst_shutdown(int whichinst);
void send_inst_cleannet();
void broadcast(const char *fmt, ...);
void process_inst_msgs();
bool get_inst_info(int nInstanceNum, instancerec * ir);
int  num_instances();
bool  user_online(int nUserNumber, int *wi);
void instance_edit();
void write_inst(int loc, int subloc, int flags);
bool inst_msg_waiting();
int  setiia(int poll_ticks);


// File: lilo.cpp

bool IsPhoneNumberUSAFormat(WUser *pUser);
void getuser();
void logon();
void logoff();
void logon_guest();


// File: listplus.cpp

void printtitle_plus();
int  first_file_pos();
void print_searching(struct search_record * search_rec);
int  listfiles_plus(int type);
int  lp_add_batch(const char *pszFileName, int dn, long fs);
int  printinfo_plus(uploadsrec *pUploadRecord, int filenum, int marked, int LinesLeft,
                    struct search_record * search_rec);
int  print_extended_plus(const char *pszFileName, int numlist, int indent, int color,
                         struct search_record * search_rec);
void show_fileinfo(uploadsrec *pUploadRecord);
int  check_lines_needed(uploadsrec * pUploadRecord);
int  prep_search_rec(struct search_record * search_rec, int type);
int  calc_max_lines();
void load_lp_config();
void save_lp_config();
void sysop_configure();
short SelectColor(int which);
void check_listplus();
void config_file_list();
void update_user_config_screen(uploadsrec * pUploadRecord, int which);
void do_batch_sysop_command(int mode, const char *pszFileName);
int  search_criteria(struct search_record * sr);
void load_listing();
void view_file(const char *pszFileName);
int  lp_try_to_download(const char *pszFileMask, int dn);
void download_plus(const char *pszFileName);
void request_file(const char *pszFileName);
bool ok_listplus();


// File: lpfunc.cpp

int  listfiles_plus_function(int type);


// File: memory.cpp

void *BbsAllocA(size_t lNumBytes);

// File: menuedit.cpp

void EditMenus();
void ListMenuDirs();



// File: misccmd.cpp

void kill_old_email();
void list_users(int mode);
void time_bank();
int  getnetnum(const char *pszNetworkName);
void uudecode(const char *pszInputFileName, const char *pszOutputFileName);
void Packers();


// File: msgbase.cpp
#include "bbs/msgbase.h"

// File: msgbase1.cpp

void send_net_post(postrec * pPostRecord, const char *extra, int nSubNumber);
void post();
void grab_user_name(messagerec * pMessageRecord, const char *pszFileName);
void scan(int nMessageNumber, int nScanOptionType, int *nextsub, bool bTitleScan);
void qscan(int nBeginSubNumber, int *pnNextSubNumber);
void nscan(int nStartingSubNum = 0);
void ScanMessageTitles();
void delmail(File *pFile, int loc);
void remove_post();

// File: multmail.cpp

void multimail(int *nUserNumber, int numu);
void slash_e();

// File: pause.cpp

void pausescr();

// File: quote.cpp
#include "bbs/quote.h"


// File: readmail.cpp

void readmail(int mode);
int  check_new_mail(int nUserNumber);


// File: shortmsg.cpp
#include "bbs/shortmsg.h"


// File: showfiles.cpp

void show_files(const char *pszFileName, const char *pszDirectoryName);


// File: SmallRecord.cpp

void InsertSmallRecord(int nUserNumber, const char *name);
void DeleteSmallRecord(const char *name);


// File: sr.cpp
#include "bbs/sr.h"

// File: srrcv.cpp

char modemkey(int *tout);
int  receive_block(char *b, unsigned char *bln, bool bUseCRC);
void xymodem_receive(const char *pszFileName, bool *received, bool bUseCRC);
void zmodem_receive(const std::string& filename, bool *received);


// File: srsend.cpp

void send_block(char *b, int nBlockType, bool bUseCRC, char byBlockNumber);
char send_b(File &file, long pos, int nBlockType, char byBlockNumber, bool *bUseCRC, const char *pszFileName,
            int *terr, bool *abort);
bool okstart(bool *bUseCRC, bool *abort);
void xymodem_send(const char *pszFileName, bool *sent, double *percent, bool bUseCRC, bool bUseYModem,
                  bool bUseYModemBatch);
void zmodem_send(const char *pszFileName, bool *sent, double *percent);


// File: subacc.cpp
#include "bbs/subacc.h"

// File: subedit.cpp

void boardedit();


// File: sublist.cpp

void old_sublist();
void SubList();


// File: subreq.cpp

void sub_xtr_del(int n, int nn, int f);
void sub_xtr_add(int n, int nn);
int  amount_of_subscribers(const char *pszNetworkFileName);


// File: subxtr.cpp

bool read_subs_xtr(int nMaxSubs, int nNumSubs, subboardrec* s);


// File: syschat.cpp

void RequestChat();
void select_chat_name(char *pszSysopName);
void two_way_chat(char *pszRollover, int nMaxLength, bool crend, char *pszSysopName);
void chat1(char *pszChatLine, bool two_way);


// File: sysoplog.cpp
#include "sysoplog.h"
// File: sysopf.cpp
#include "bbs/sysopf.h"

// File: user.cpp

bool okconf(WUser *pUser);
void add_ass(int nNumPoints, const char *pszReason);

// File: utility.cpp
#include "utility.h"


// File: wqscn.cpp

bool open_qscn();
void close_qscn();
void read_qscn(int nUserNumber, uint32_t* qscn, bool bStayOpen, bool bForceRead = false);
void write_qscn(int nUserNumber, uint32_t* qscn, bool bStayOpen);

// File: xfer.cpp
#include "bbs/xfer.h"

// File: xferovl.cpp

void move_file();
void sortdir(int nDirectoryNum, int type);
void sort_all(int type);
void rename_file();
bool maybe_upload(const char *pszFileName, int nDirectoryNum, const char *pszDescription);
void upload_files(const char *pszFileName, int nDirectoryNum, int type);
bool uploadall(int nDirectoryNum);
void relist();
void edit_database();
void modify_database(const char *pszFileName, bool add);
bool is_uploadable(const char *pszFileName);
void xfer_defaults();
void finddescription();
void arc_l();


// File: xferovl1.cpp

void modify_extended_description(char **sss, const char *dest);
bool valid_desc(const char *pszDescription);
bool get_file_idz(uploadsrec * pUploadRecord, int dn);
int  read_idz_all();
int  read_idz(int mode, int tempdir);
void tag_it();
void tag_files();
int  add_batch(char *pszDescription, const char *pszFileName, int dn, long fs);
int  try_to_download(const char *pszFileMask, int dn);
void download();
char fancy_prompt(const char *pszPrompt, const char *pszAcceptChars);
void endlist(int mode);
void SetNewFileScanDate();
void removefilesnotthere(int dn, int *autodel);
void removenotthere();
int  find_batch_queue(const char *pszFileName);
void remove_batch(const char *pszFileName);


// File: xfertmp.cpp

bool bad_filename(const char *pszFileName);
// returns true if the file is downloaded.
bool download_temp_arc(const char *pszFileName, bool count_against_xfer_ratio);
void add_arc(const char *arc, const char *pszFileName, int dos);
void add_temp_arc();
void del_temp();
void list_temp_dir();
void temp_extract();
void list_temp_text();
void list_temp_arc();
void temporary_stuff();
void move_file_t();
void removefile();

#endif // __INCLUDED_FCNS_H__
