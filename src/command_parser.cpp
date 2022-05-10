#include "../include/command_parser.h"

#include <regex>

const string Parser::kCommandPlace = "PLACE";
const string Parser::kCommandMove = "MOVE";
const string Parser::kCommandTurnLeft = "LEFT";
const string Parser::kCommandTurnRight = "RIGHT";
const string Parser::kCommandReport = "REPORT";

Command Parser::parse(const string str, ToyRobotProps& props) {
  enum Command cmd = Command::kUnsupported;

  // The pattern will match from 4 to 6 characters.
  regex pattern_to_match_other_commands("^([A-Z]{4,6})$");
  // Pattern to match PLACE command.
  regex pattern_place_command("^PLACE\\s(\\d),(\\d),([A-Z]{4,5})$");

  smatch results;
  if (regex_search(str, results, pattern_place_command)) {
    // Ignoring the entire matched text.
    for (size_t idx = 1; idx < results.size(); idx++) {
      // First capturing group.
      if (idx == 1)
        props.pos_x = stoi(results.str(idx));
      // Second capturing group.
      else if (idx == 2)
        props.pos_y = stoi(results.str(idx));
      // Third capturing group.
      else if (idx == 3)
        props.direction = results.str(idx);
    }

    cmd = Command::kPlaceToyRobot;
  } else if (regex_search(str, results, pattern_to_match_other_commands)) {
    if (results.str(1) == Parser::kCommandMove)
      cmd = Command::kMoveToyRobot;
    else if (results.str(1) == Parser::kCommandReport)
      cmd = Command::kReportPosition;
    else if (results.str(1) == Parser::kCommandTurnLeft)
      cmd = Command::kTurnLeft;
    else if (results.str(1) == Parser::kCommandTurnRight)
      cmd = Command::kTurnRight;
  }

  return cmd;
}
