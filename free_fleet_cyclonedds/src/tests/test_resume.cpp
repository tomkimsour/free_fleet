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

#include <iostream>

#include <dds/dds.h>

#include <free_fleet_cyclonedds/CycloneDDSMiddleware.hpp>

#include <free_fleet/messages/ModeRequest.hpp>

int main(int argc, char** argv)
{
  if (argc < 5)
  {
    std::cout << "Please request using the following format," << std::endl;
    std::cout << "<Executable> <Domain ID> <Fleet Name> <Robot Name> <Task ID>" << std::endl;
    return 1;
  }

  int dds_domain = strtod(argv[1], NULL);
  std::string fleet_name(argv[2]);
  std::string robot_name(argv[3]);
  std::string task_id(argv[4]);

  auto manager =
    free_fleet::cyclonedds::CycloneDDSMiddleware::make_manager(
      dds_domain, fleet_name);
  if (!manager)
  {
    std::cerr << "[ERROR]: Failed to initialize a manager.\n";
    return 1;
  }

  free_fleet::messages::ModeRequest request;
  request.robot_name = robot_name;
  request.task_id = task_id;
  request.mode.mode = request.mode.MODE_MOVING;

  bool manager_loop = true;
  int count = 0;
  while (manager_loop)
  {
    manager->send_mode_request(request);
    count++;

    auto states = manager->read_states();
    if (!states.empty())
    {
      for (const auto& s : states)
      {
        if (s->name == robot_name &&
          s->mode.mode != s->mode.MODE_PAUSED)
          manager_loop = false;
      }
    }
    dds_sleepfor(DDS_MSECS(100));
  }

  std::cout << "Sent resume mode request and received feedback after "
    << count << " iterations." << std::endl;
  return 0;
}
