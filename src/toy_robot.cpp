#include "../include/toy_robot.h"

#include <algorithm>
#include <iostream>

using namespace std;
using namespace game;

const string ToyRobot::kDirectionEast = "EAST";
const string ToyRobot::kDirectionWest = "WEST";
const string ToyRobot::kDirectionNorth = "NORTH";
const string ToyRobot::kDirectionSouth = "SOUTH";

ToyRobot::ToyRobot()
    : min_x_{kDefaultMinX},
      max_x_{kDefaultMaxX},
      min_y_{kDefaultMinY},
      max_y_{kDefaultMaxY},
      valid_state_{false},
      robot_props{},
      directions(
          {kDirectionNorth, kDirectionEast, kDirectionSouth, kDirectionWest}) {
  directions_size_ = directions.size();
}

bool ToyRobot::CheckValidPosition(int pos_x, int pos_y) {
  return (pos_x >= kDefaultMinX && pos_x <= kDefaultMaxX &&
          pos_y >= kDefaultMinY && pos_y <= kDefaultMaxY);
}

bool ToyRobot::Place(ToyRobotProps& props) {
  if (!CheckValidPosition(props.pos_x, props.pos_y)) return false;

  if (!Face(props.direction)) return false;

  robot_props.pos_x = props.pos_x;
  robot_props.pos_y = props.pos_y;
  valid_state_ = true;
  return valid_state_;
}

bool ToyRobot::Face(string new_direction) {
  if (new_direction != kDirectionEast && new_direction != kDirectionWest &&
      new_direction != kDirectionNorth && new_direction != kDirectionSouth) {
    return false;
  }

  robot_props.direction = new_direction;
  return true;
}

void ToyRobot::Move() {
  if (!valid_state_) return;

  int temp_x = robot_props.pos_x;
  int temp_y = robot_props.pos_y;

  if (robot_props.direction == kDirectionEast)
    temp_x += 1;
  else if (robot_props.direction == kDirectionWest)
    temp_x -= 1;
  else if (robot_props.direction == kDirectionNorth)
    temp_y += 1;
  else if (robot_props.direction == kDirectionSouth)
    temp_y -= 1;
  else
    return;

  if (!CheckValidPosition(temp_x, temp_y)) return;

  robot_props.pos_x = temp_x;
  robot_props.pos_y = temp_y;
}

void ToyRobot::Report() {
  if (valid_state_)
    cout << robot_props.pos_x << "," << robot_props.pos_y << ","
         << robot_props.direction << endl;
}

void ToyRobot::Rotate(enum Turn t) {
  if (!valid_state_) return;

  switch (t) {
    case Turn::kTurnLeft:
      TurnLeft();
      break;
    case Turn::kTurnRight:
      TurnRight();
      break;
    default:
      break;
  }
}

void ToyRobot::TurnLeft() {
  vector<string>::iterator it =
      std::find(directions.begin(), directions.end(), robot_props.direction);

  int pos = ((it - directions.begin()) - 1 + directions_size_) % directions_size_;
  robot_props.direction = directions[pos];
}

void ToyRobot::TurnRight() {
  vector<string>::iterator it =
      std::find(directions.begin(), directions.end(), robot_props.direction);

  int pos = ((it - directions.begin()) + 1) % directions_size_;
  robot_props.direction = directions[pos];
}