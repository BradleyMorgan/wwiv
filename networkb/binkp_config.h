/**************************************************************************/
/*                                                                        */
/*                          WWIV Version 5.x                              */
/*               Copyright (C)2015, WWIV Software Services                */
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
#pragma once
#ifndef __INCLUDED_NETWORKB_BINKP_CONFIG_H__
#define __INCLUDED_NETWORKB_BINKP_CONFIG_H__

#include <cstdint>
#include <exception>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "core/inifile.h"
#include "networkb/config_exceptions.h"
#include "sdk/networks.h"

namespace wwiv {
namespace net {

struct BinkNodeConfig {
  std::string host;
  int port;
};

class BinkConfig {
 public:
  BinkConfig(const std::string& callout_network_name, const wwiv::sdk::Config& config, const wwiv::sdk::Networks& networks);
  BinkConfig(int node_number, const wwiv::sdk::Config& config, const std::string& network_dir);
  virtual ~BinkConfig();
  const BinkNodeConfig* node_config_for(int node) const;

  uint16_t callout_node_number() const { return callout_node_; }
  const std::string system_name() const { return system_name_; }
  const std::string sysop_name() const { return sysop_name_; }
  const std::string gfiles_directory() const { return gfiles_directory_;  }
  const std::string callout_network_name() const { return callout_network_name_; }
  const std::string network_dir(const std::string& network_name) const;
  const wwiv::sdk::Networks& networks() { return networks_; }

  void set_skip_net(bool skip_net) { skip_net_ = skip_net; }
  bool skip_net() const { return skip_net_; }

 private:
  std::map<uint16_t, BinkNodeConfig> node_config_;
  std::string home_dir_;

  uint16_t callout_node_;
  std::string system_name_;
  std::string callout_network_name_;
  std::string sysop_name_;
  std::string gfiles_directory_;
  const wwiv::sdk::Networks networks_;
  bool skip_net_;
};

bool ParseBinkConfigLine(const std::string& line,
			 uint16_t* node,
			 BinkNodeConfig* config);

}  // namespace net
}  // namespace wwiv


#endif  // __INCLUDED_NETWORKB_BINKP_CONFIG_H__
