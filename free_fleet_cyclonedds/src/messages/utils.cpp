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

#include "utils.hpp"

namespace free_fleet {
namespace cyclonedds {

//==============================================================================

char* dds_string_alloc_and_copy(const std::string& _str)
{
  char* ptr = dds_string_alloc(_str.length());
  for (size_t i = 0; i < _str.length(); ++i)
  {
    ptr[i] = _str[i];
  }
  return ptr;
}

//==============================================================================

void convert(const messages::Location& input, MiddlewareMessages_Location& output)
{
  output.sec = input.sec;
  output.nanosec = input.nanosec;
  output.x = input.x;
  output.y = input.y;
  output.yaw = input.yaw;
  output.level_name = dds_string_alloc_and_copy(input.level_name);
}

//==============================================================================

void convert(const MiddlewareMessages_Location& input, messages::Location& output)
{
  output.sec = input.sec;
  output.nanosec = input.nanosec;
  output.x = input.x;
  output.y = input.y;
  output.yaw = input.yaw;
  output.level_name = std::string(input.level_name);
}

//==============================================================================

void convert(
  const messages::ModeParameter& input,
  MiddlewareMessages_ModeParameter& output)
{
  output.name = dds_string_alloc_and_copy(input.name);
  output.value = dds_string_alloc_and_copy(input.value);
}

//==============================================================================

void convert(
  const MiddlewareMessages_ModeParameter& input,
  messages::ModeParameter& output)
{
  output.name = std::string(input.name);
  output.value = std::string(input.value);
}

//==============================================================================

void convert(
  const messages::ModeRequest& input,
  MiddlewareMessages_ModeRequest& output)
{
  output.robot_name = dds_string_alloc_and_copy(input.robot_name);
  output.task_id = dds_string_alloc_and_copy(input.task_id);
  convert(input.mode, output.mode);

  std::size_t mode_params_num = input.parameters.size();
  output.parameters._maximum = static_cast<uint32_t>(mode_params_num);
  output.parameters._length = static_cast<uint32_t>(mode_params_num);
  output.parameters._buffer =
    MiddlewareMessages_ModeRequest_parameters_seq_allocbuf(mode_params_num);
  for(std::size_t i = 0; i < mode_params_num; ++i)
    convert(input.parameters[i], output.parameters._buffer[i]);
}

//==============================================================================

void convert(
  const MiddlewareMessages_ModeRequest& input,
  messages::ModeRequest& output)
{
  output.robot_name = std::string(input.robot_name);
  output.task_id = std::string(input.task_id);
  convert(input.mode, output.mode);
  for (uint32_t i = 0; i < input.parameters._length; ++i)
  {
    messages::ModeParameter param;
    convert(input.parameters._buffer[i], param);
    output.parameters.push_back(param);
  }
}

//==============================================================================

void convert(
  const messages::NavigationRequest& input,
  MiddlewareMessages_NavigationRequest& output)
{
  output.robot_name = dds_string_alloc_and_copy(input.robot_name);
  output.task_id = dds_string_alloc_and_copy(input.task_id);

  std::size_t path_elem_num = input.path.size();
  output.path._maximum = static_cast<uint32_t>(path_elem_num);
  output.path._length = static_cast<uint32_t>(path_elem_num);
  output.path._buffer = 
    MiddlewareMessages_Path_allocbuf(path_elem_num);
  for (std::size_t i = 0; i < path_elem_num; ++i)
    output.path._buffer[i] = static_cast<uint32_t>(input.path[i]);
}

//==============================================================================

void convert(
  const MiddlewareMessages_NavigationRequest& input,
  messages::NavigationRequest& output)
{
  output.robot_name = std::string(input.robot_name);
  output.task_id = std::string(input.task_id);
  output.path.clear();
  for (uint32_t i = 0; i < input.path._length; ++i)
    output.path.push_back(input.path._buffer[i]);
}

//==============================================================================

void convert(
  const messages::RobotMode& input,
  MiddlewareMessages_RobotMode& output)
{
  output.mode = input.mode;
  output.info = dds_string_alloc_and_copy(input.info);
}

//==============================================================================

void convert(
  const MiddlewareMessages_RobotMode& input,
  messages::RobotMode& output)
{
  output.mode = input.mode;
  output.info = std::string(input.info);
}

//==============================================================================

void convert(
  const messages::RobotState& input,
  MiddlewareMessages_RobotState& output)
{
  output.name = dds_string_alloc_and_copy(input.name);
  output.model = dds_string_alloc_and_copy(input.model);
  output.task_id = dds_string_alloc_and_copy(input.task_id);
  convert(input.mode, output.mode);
  output.battery_percent = input.battery_percent;
  convert(input.location, output.location);

  std::size_t path_elem_num = input.path.size();
  output.path._maximum = static_cast<uint32_t>(path_elem_num);
  output.path._length = static_cast<uint32_t>(path_elem_num);
  output.path._buffer = 
    MiddlewareMessages_Path_allocbuf(path_elem_num);
  for (std::size_t i = 0; i < path_elem_num; ++i)
    output.path._buffer[i] = static_cast<uint32_t>(input.path[i]);
}

//==============================================================================

void convert(
    const MiddlewareMessages_RobotState& input,
    messages::RobotState& output)
{
  output.name = std::string(input.name);
  output.model = std::string(input.model);
  output.task_id = std::string(input.task_id);
  convert(input.mode, output.mode);
  output.battery_percent = input.battery_percent;
  convert(input.location, output.location);

  output.path.clear();
  for (uint32_t i = 0; i < input.path._length; ++i)
    output.path.push_back(input.path._buffer[i]);
}

//==============================================================================

void convert(
  const rmf_traffic::agv::Graph& input, 
  MiddlewareMessages_Graph& output)
{
  std::size_t num_waypoints = input.num_waypoints();
  output.waypoints._maximum = static_cast<uint32_t>(num_waypoints);
  output.waypoints._length = static_cast<uint32_t>(num_waypoints);
  output.waypoints._buffer =
    MiddlewareMessages_Graph_waypoints_seq_allocbuf(num_waypoints);
  for (std::size_t i = 0; i < num_waypoints; ++i)
  {
    const auto& waypoint = input.get_waypoint(i);
    const auto& location = waypoint.get_location();
    output.waypoints._buffer[i].map_name = 
        dds_string_alloc_and_copy(waypoint.get_map_name());
    output.waypoints._buffer[i].x = location[0];
    output.waypoints._buffer[i].y = location[1];
    output.waypoints._buffer[i].is_holding_point = waypoint.is_holding_point();
    output.waypoints._buffer[i].is_passthrough_point =
      waypoint.is_passthrough_point();
    output.waypoints._buffer[i].is_parking_spot =
      waypoint.is_parking_spot();
    output.waypoints._buffer[i].index = static_cast<uint32_t>(waypoint.index());
    const std::string* waypoint_name = waypoint.name();
    if (waypoint_name)
      output.waypoints._buffer[i].name =
        dds_string_alloc_and_copy(*waypoint_name);
    else
      output.waypoints._buffer[i].name = nullptr;
  }

  std::size_t num_lanes = input.num_lanes();
  output.lanes._maximum = static_cast<uint32_t>(num_lanes);
  output.lanes._length = static_cast<uint32_t>(num_lanes);
  output.lanes._buffer =
    MiddlewareMessages_Graph_lanes_seq_allocbuf(num_lanes);
  for (std::size_t i = 0; i < num_lanes; ++i)
  {
    const auto& lane = input.get_lane(i);
    output.lanes._buffer[i].entry =
      static_cast<uint32_t>(lane.entry().waypoint_index());
    output.lanes._buffer[i].exit =
      static_cast<uint32_t>(lane.exit().waypoint_index());
  }
}

//==============================================================================

void convert(
  const MiddlewareMessages_Graph& input, 
  rmf_traffic::agv::Graph& output)
{
  // TODO: clear up the graph before adding waypoints and lanes
  std::size_t num_waypoints = static_cast<std::size_t>(input.waypoints._length);
  for (std::size_t i = 0; i < num_waypoints; ++i)
  {
    auto& waypoint = output.add_waypoint(
      std::string(input.waypoints._buffer[i].map_name),
      {input.waypoints._buffer[i].x, input.waypoints._buffer[i].y})
    .set_holding_point(input.waypoints._buffer[i].is_holding_point)
    .set_passthrough_point(input.waypoints._buffer[i].is_passthrough_point)
    .set_parking_spot(input.waypoints._buffer[i].is_parking_spot);
    assert(waypoint.index() == i);
    if (input.waypoints._buffer[i].name)
      output.set_key(std::string(input.waypoints._buffer[i].name), i);
  }

  std::size_t num_lanes = static_cast<std::size_t>(input.lanes._length);
  for (std::size_t i = 0; i < num_lanes; ++i)
  {
    auto& lane = output.add_lane(
      static_cast<std::size_t>(input.lanes._buffer[i].entry),
      static_cast<std::size_t>(input.lanes._buffer[i].exit));
    assert(lane.index() == i);
  }
}

//==============================================================================

} // namespace cyclonedds
} // namespace free_fleet
