/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  Filip Krumpe <filip.krumpe@posteo.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "textoutputhelper.h"

#include <iomanip>

#include "osmpoi.h"

bool text_output::TextOutputHelper::writeBallsFile(
    const std::vector<label_helper::LabelHelper::LabelBall> &aBalls,
    char aSep) {
  std::ofstream file(mOutputPath.c_str());

  if (!file.is_open()) {
    return false;
  }
  file.clear();

  std::size_t importance = 0;
  file << aBalls.size();

  for (auto &ball : aBalls) {
    file << "\n"
         << std::fixed << std::setprecision(17) << ball.mPos.getLatDegree()
         << aSep << ball.mPos.getLonDegree() << aSep << importance++ << aSep
         << (int32_t)(ball.mBallRadius);
  }

  file.close();

  return true;
}

bool text_output::TextOutputHelper::writeCompleteFile(
    const std::vector<label_helper::LabelHelper::LabelBall> &aBalls,
    char aSep) {
  std::ofstream file(mOutputPath.c_str());

  if (!file.is_open()) {
    return false;
  }
  file.clear();

  std::size_t importance = 0;
  file << aBalls.size();

  for (auto ball : aBalls) {

    std::string label = ball.mLabel;
    while (label.find("\n") != label.npos) {
      label.replace(label.find('\n'), 1, "\\n");
    }

    file << "\n"
         << std::fixed << std::setprecision(17) << ball.mPos.getLatDegree()
         << aSep << ball.mPos.getLonDegree() << aSep << importance++ << aSep
         << std::fixed << std::setprecision(2) << ball.mBallRadius << aSep
         << ball.mOsmId << aSep << "'" << label << "'" << aSep
         << ball.mLabelFactor;
  }

  file.close();

  return true;
}
