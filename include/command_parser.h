#ifndef INCLUDE_COMMAND_PARSER_H_
#define INCLUDE_COMMAND_PARSER_H_

#include "../include/toy_robot_properties.h"

#include <string>

using namespace std;

enum class Command : int8_t {
  kUnsupported = 0,
  kPlaceToyRobot = 1,
  kMoveToyRobot = 2,
  kTurnLeft = 3,
  kTurnRight = 4,
  kReportPosition = 5,
  // Add new commands here.
};

class Parser {
 public:
  static Command parse(const string str, ToyRobotProps& props);

  const static string kCommandPlace;
  const static string kCommandMove;
  const static string kCommandTurnLeft;
  const static string kCommandTurnRight;
  const static string kCommandReport;
};

#endif // INCLUDE_COMMAND_PARSER_H_