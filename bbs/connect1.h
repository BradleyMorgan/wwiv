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
/**************************************************************************/
#ifndef __INCLUDED_BBS_CONNECT1_H__
#define __INCLUDED_BBS_CONNECT1_H__

#include "sdk/net.h"

void zap_call_out_list();
void read_call_out_list();
void zap_bbs_list();
void read_bbs_list_index();
bool valid_system(int ts);
net_system_list_rec *next_system(int ts);
void zap_contacts();
void read_contacts();
void set_net_num(int network_number);

#endif  // __INCLUDED_BBS_CONNECT1_H__