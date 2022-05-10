#ifndef INCLUDE_TOY_ROBOT_PROPERTIES_H_
#define INCLUDE_TOY_ROBOT_PROPERTIES_H_

#include <string>

struct ToyRobotProps{
  int pos_x;
  int pos_y;
  std::string direction;

  ToyRobotProps(): pos_x{-1}, pos_y{-1}, direction{""} {}
};

#endif // INCLUDE_TOY_ROBOT_PROPERTIES_H_
