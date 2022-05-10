#ifndef INCLUDE_TOY_ROBOT_H_
#define INCLUDE_TOY_ROBOT_H_

#include "../include/toy_robot_properties.h"
#include <string>
#include <vector>

using namespace std;

namespace game {

  enum class Turn : int8_t {
    kTurnLeft = 0,
    kTurnRight = 1
  };

class ToyRobot {
 public:
  void Move();
  void Place(ToyRobotProps& props);
  bool Face(string new_direction, bool init=false);
  void Rotate(enum Turn t);
  void Report();

  ToyRobot();

  const static string kDirectionEast;
  const static string kDirectionWest;
  const static string kDirectionNorth;
  const static string kDirectionSouth;

  const int kDefaultMinX = 0U;
  const int kDefaultMaxX = 5U;
  const int kDefaultMinY = 0U;
  const int kDefaultMaxY = 5U;

 private:
  bool CheckValidPosition(int pos_x, int pos_y);
  void TurnLeft();
  void TurnRight();

  int min_x_, max_x_, min_y_, max_y_;
  bool valid_state_;
  ToyRobotProps robot_props;

  vector<string> directions;
};

};  // namespace Game

#endif  // INCLUDE_TOY_ROBOT_H_