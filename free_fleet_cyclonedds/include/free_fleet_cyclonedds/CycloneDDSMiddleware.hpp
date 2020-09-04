/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef INCLUDE__FREE_FLEET_CYCLONEDDS__CYCLONEDDSMIDDLEWARE_HPP
#define INCLUDE__FREE_FLEET_CYCLONEDDS__CYCLONEDDSMIDDLEWARE_HPP

#include <memory>

#include <free_fleet/transport/Middleware.hpp>
#include <free_fleet/messages/RobotState.hpp>
#include <free_fleet/messages/ModeRequest.hpp>
#include <free_fleet/messages/NavigationRequest.hpp>

#include <rmf_utils/impl_ptr.hpp>

namespace free_fleet {
namespace cyclonedds {

class CycloneDDSMiddleware : public transport::Middleware
{
public:

  struct Config
  {
    int dds_domain;
    std::string graph_service_name;
    std::string state_topic_name;
    std::string mode_request_topic_name;
    std::string navigation_request_topic_name;

    void print_config();
  };

  static std::shared_ptr<CycloneDDSMiddleware> make_client(Config config);

  static std::shared_ptr<CycloneDDSMiddleware> make_manager(Config config);

  ~CycloneDDSMiddleware();

  void send_graph(std::shared_ptr<rmf_traffic::agv::Graph> graph) final;
  
  std::shared_ptr<rmf_traffic::agv::Graph> request_graph() final;

  void send_state(const messages::RobotState& state) final;

  std::vector<std::shared_ptr<messages::RobotState>> read_states() final;

  void send_mode_request(const messages::ModeRequest& request) final;

  std::shared_ptr<messages::ModeRequest> read_mode_request() final;

  void send_navigation_request(
      const messages::NavigationRequest& request) final;
  
  std::shared_ptr<messages::NavigationRequest>
      read_navigation_request() final;

  class Implementation;
private:
  rmf_utils::impl_ptr<Implementation> _pimpl;
  CycloneDDSMiddleware();
};

} // namespace cyclonedds
} // namespace free_fleet

#endif // INCLUDE__FREE_FLEET_CYCLONEDDS__CYCLONEDDSMIDDLEWARE_HPP
