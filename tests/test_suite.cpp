#include "acutest.h"
#include "../include/command_parser.h"
#include "../include/toy_robot.h"

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
  printf("%s", props.direction.c_str());

  TEST_CHECK(props.pos_x == -1);
  TEST_CHECK(props.pos_y == -1);
  TEST_CHECK(cmd == Command::kUnsupported);
}

void test_command_parser_parse_report_cmd(void) {
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
  TEST_CHECK(cmd == Command::kUnsupported);
}

void test_command_parser_parse_move_cmd(void) {
  string str = "MOVE";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(props.pos_x == 0);
  TEST_CHECK(props.pos_y == 0);
  TEST_CHECK(props.direction == "");
  TEST_CHECK(cmd == Command::kMoveToyRobot);
}

void test_command_parser_rejects_invalid_move_cmd(void) {
  string str = "move";

  ToyRobotProps props;
  enum Command cmd = Parser::parse(str, props);

  TEST_CHECK(props.pos_x == 0);
  TEST_CHECK(props.pos_y == 0);
  TEST_CHECK(props.direction == "");
  TEST_CHECK(cmd == Command::kMoveToyRobot);
}

void test_min_max_x_y(void) {
  game::ToyRobot toyrobot;
  TEST_CHECK(toyrobot.kDefaultMinX == 0U);
  TEST_CHECK(toyrobot.kDefaultMaxX == 5U);
  TEST_CHECK(toyrobot.kDefaultMinY == 0U);
  TEST_CHECK(toyrobot.kDefaultMaxY == 5U);
}

TEST_LIST = {
  { "check all the supported commands in the parser", test_command_parser_cmd_list },
  { "check command parser parses PLACE 1,1,NORTH", test_command_parser_place_1_1_north },
  { "check command parser parses PLACE 0,0,SOUTH", test_command_parser_place_0_0_south },
  { "check command parser rejects invalid PLACE command", test_command_parser_rejects_invalid_place_cmd },
  { "check command parser parses REPORT command", test_command_parser_parse_report_cmd },
  { "check command parser rejects invalid REPORT command", test_command_parser_rejects_invalid_report_cmd },
  { "check min_x, max_x, min_y, max_y", test_min_max_x_y },
  {0}
};