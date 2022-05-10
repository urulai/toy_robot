#include "../include/toy_robot.h"

#include <iostream>

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
      robot_props{} {
  // Initializing the directions vector.
  // The directions are stored in a clockwise direction.
  // North -> East -> South -> West
  // For e.g.: A toy robot facing North will now face East after RIGHT command.
  directions.push_back(kDirectionNorth);
  directions.push_back(kDirectionEast);
  directions.push_back(kDirectionSouth);
  directions.push_back(kDirectionWest);
}

bool ToyRobot::CheckValidPosition(int pos_x, int pos_y) {
  return (pos_x >= kDefaultMinX && pos_x <= kDefaultMaxX &&
          pos_y >= kDefaultMinY && pos_y <= kDefaultMaxY);
}

bool ToyRobot::Place(ToyRobotProps& props) {
  if (!CheckValidPosition(props.pos_x, props.pos_y)) return false;

  if (!Face(props.direction, true)) return false;

  robot_props.pos_x = props.pos_x;
  robot_props.pos_y = props.pos_y;
  valid_state_ = true;
  return valid_state_;
}

bool ToyRobot::Face(string new_direction, bool init) {
  if (new_direction != kDirectionEast && new_direction != kDirectionWest &&
      new_direction != kDirectionNorth && new_direction != kDirectionSouth) {
    return false;
  }

  if (!init && !valid_state_) return false;

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
  vector<string>::reverse_iterator it = directions.rbegin();

  for (; it != directions.rend(); it++) {
    if (robot_props.direction == *it) break;
  }

  if (++it == directions.rend()) {
    it = directions.rbegin();
    robot_props.direction = *it;
  } else {
    robot_props.direction = *it;
  }
}

void ToyRobot::TurnRight() {
  vector<string>::iterator it = directions.begin();

  for (; it != directions.end(); ++it) {
    if (robot_props.direction == *it) break;
  }

  if (++it == directions.end()) {
    it = directions.begin();
    robot_props.direction = *it;

  } else {
    robot_props.direction = *it;
  }
}