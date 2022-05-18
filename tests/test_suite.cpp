#include "../include/command_parser.h"
#include "../include/toy_robot.h"
#include "acutest.h"

#include <iostream>

// Command Parser tests
void test_command_parser_cmd_list(void) {
  TEST_CHECK(Parser::kCommandMove == "MOVE");
  TEST_CHECK(Parser::kCommandPlace == "PLACE");
  TEST_CHECK(Parser::kCommandReport == "REPORT");
  TEST_CHECK(Parser::kCommandTurnLeft == "LEFT");
  TEST_CHECK(Parser::kCommandTurnRight == "RIGHT");
}

void test_command_parser_place_1_1_north(void) {
  string str = "PLACE 1,1,NORTH";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(props.pos_x == 1);
  TEST_CHECK(props.pos_y == 1);
  TEST_CHECK(props.direction == game::ToyRobot::kDirectionNorth);
  TEST_CHECK(cmd == Command::kPlaceToyRobot);
}

void test_command_parser_place_0_0_south(void) {
  string str = "PLACE 0,0,SOUTH";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(props.pos_x == 0);
  TEST_CHECK(props.pos_y == 0);
  TEST_CHECK(props.direction == game::ToyRobot::kDirectionSouth);
  TEST_CHECK(cmd == Command::kPlaceToyRobot);
}

void test_command_parser_rejects_invalid_place_cmd(void) {
  string str = "PLACE 0,0,east";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(props.pos_x == -1);
  TEST_CHECK(props.pos_y == -1);
  TEST_CHECK(cmd == Command::kUnsupported);
}

void test_command_parser_parses_valid_report_cmd(void) {
  string str = "REPORT";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(props.pos_x == -1);
  TEST_CHECK(props.pos_y == -1);
  TEST_CHECK(props.direction == "");
  TEST_CHECK(cmd == Command::kReportPosition);
}

void test_command_parser_rejects_invalid_report_cmd(void) {
  string str = "REPORT_";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);
  std::cout << static_cast<unsigned int>(cmd) << std::endl;
  TEST_CHECK(cmd == Command::kUnsupported);
}

void test_command_parser_parses_valid_move_cmd(void) {
  string str = "MOVE";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);
  TEST_CHECK(cmd == Command::kMoveToyRobot);
}

void test_command_parser_rejects_invalid_move_cmd(void) {
  string str = "move";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);
  TEST_CHECK(cmd == Command::kUnsupported);
}

void test_command_parser_parses_valid_right_cmd(void) {
  string str = "RIGHT";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);
  TEST_CHECK(cmd == Command::kTurnRight);
}

void test_command_parser_rejects_invalid_right_cmd(void) {
  string str = "right";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);
  TEST_CHECK(cmd == Command::kUnsupported);
}

void test_command_parser_parses_valid_left_cmd(void) {
  string str = "LEFT";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);
  TEST_CHECK(cmd == Command::kTurnLeft);
}

void test_command_parser_rejects_invalid_left_cmd(void) {
  string str = "left";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);
  TEST_CHECK(cmd == Command::kUnsupported);
}

void test_min_max_x_y(void) {
  game::ToyRobot toyrobot;
  TEST_CHECK(toyrobot.kDefaultMinX == 0U);
  TEST_CHECK(toyrobot.kDefaultMaxX == 5U);
  TEST_CHECK(toyrobot.kDefaultMinY == 0U);
  TEST_CHECK(toyrobot.kDefaultMaxY == 5U);
}

void test_robot_place_command_is_ignored(void) {
  // Tests Place command is ignored, when the direction is not correct.
  game::ToyRobot toy_robot;
  string str = "PLACE 0,0,East";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(!toy_robot.Place(props));
}

void test_robot_place_command_is_accepted(void) {
  // Tests Place command is accepted, when the direction is correct.
  game::ToyRobot toy_robot;
  string str = "PLACE 0,0,EAST";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(toy_robot.Place(props));
}

void test_robot_face_command_is_ignored(void) {
  // Tests Face command is ignored, when the toy robot is not in a valid state.
  game::ToyRobot toy_robot;
  TEST_CHECK(toy_robot.Face(game::ToyRobot::kDirectionEast));
}

void test_robot_face_command_is_accepted_for_initialization(void) {
  // Tests Face command is accepted for toy robot initialization.
  game::ToyRobot toy_robot;
  TEST_CHECK(toy_robot.Face(game::ToyRobot::kDirectionEast));
}

void test_robot_face_command_is_accepted(void) {
  // Tests Face command is accepted, when the toy robot is in a valid state.
  game::ToyRobot toy_robot;
  string str = "PLACE 0,0,EAST";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(toy_robot.Place(props));
  TEST_CHECK(toy_robot.Face(game::ToyRobot::kDirectionWest));
}

TEST_LIST = {
    {"all the supported commands in the parser",
     test_command_parser_cmd_list},
    {"command parser parses PLACE 1,1,NORTH",
     test_command_parser_place_1_1_north},
    {"command parser parses PLACE 0,0,SOUTH",
     test_command_parser_place_0_0_south},
    {"command parser rejects invalid PLACE command",
     test_command_parser_rejects_invalid_place_cmd},
    {"command parser parses valid REPORT command",
     test_command_parser_parses_valid_report_cmd},
    {"command parser rejects invalid REPORT command",
     test_command_parser_rejects_invalid_report_cmd},
    {"command parser parses valid MOVE command",
     test_command_parser_parses_valid_move_cmd},
    {"command parser rejects invalid MOVE command",
     test_command_parser_rejects_invalid_move_cmd},
    {"command parser parses valid RIGHT command",
     test_command_parser_parses_valid_right_cmd},
    {"command parser rejects invalid RIGHT command",
     test_command_parser_rejects_invalid_right_cmd},
    {"command parser parses valid LEFT command",
     test_command_parser_parses_valid_left_cmd},
    {"command parser rejects invalid LEFT command",
     test_command_parser_rejects_invalid_left_cmd},
    {"min_x, max_x, min_y, max_y", test_min_max_x_y},
    {"Place command is ignored, when the direction is not correct.",
     test_robot_place_command_is_ignored},
    {"Place command is accepted, when the direction is correct.",
     test_robot_place_command_is_accepted},
    {"Face command is ignored, when the toy robot is not in a valid "
     "state.",
     test_robot_face_command_is_ignored},
    {"Face command is accepted, when the toy robot game starts",
     test_robot_face_command_is_accepted_for_initialization},
    {"Face command is accepted, when the toy robot is in a valid state",
     test_robot_face_command_is_accepted},

    // Add new tests above this line.
    {0}};