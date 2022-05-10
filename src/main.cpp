#include <fstream>
#include <iostream>

#include "../include/command_parser.h"
#include "../include/toy_robot.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Error, filename is missing.\nFormat: ./toy_robot <filename>"
         << endl;
    return 1;
  }

  string file_name = argv[1];
  ifstream input(file_name);

  if (input.is_open()) {
    string line;
    game::ToyRobot toyrobot;

    while (std::getline(input, line)) {
      ToyRobotProps props;

      Command cmd = Parser::parse(line, props);
      if (cmd == Command::kPlaceToyRobot)
        toyrobot.Place(props);
      else if (cmd == Command::kMoveToyRobot)
        toyrobot.Move();
      else if (cmd == Command::kTurnLeft) {
        game::Turn t = game::Turn::kTurnLeft;
        toyrobot.Rotate(t);
      } else if (cmd == Command::kTurnRight) {
        game::Turn t = game::Turn::kTurnRight;
        toyrobot.Rotate(t);
      } else if (cmd == Command::kReportPosition)
        toyrobot.Report();
    }
  }
  input.close();

  return 0;
}
