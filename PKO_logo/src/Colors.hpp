/*
 * Colors.hpp
 *
 *  Created on: 19 maj 2015
 *      Author: anna
 */

#ifndef SRC_COLORS_HPP_
#define SRC_COLORS_HPP_

#include <cv.h>
#include <highgui.h>

using namespace cv;

Vec3b const BLACK = Vec3b(0,0,0);
Vec3b const WHITE = Vec3b(255,255,255);
Vec3b const RED = Vec3b(0,0,255);
Vec3b const LIME = Vec3b(0,255,0);
Vec3b const BLUE = Vec3b(255,0,0);
Vec3b const YELLOW = Vec3b(0,255,255);
Vec3b const CYAN = Vec3b(255,255,0);
Vec3b const MAGENTA = Vec3b(255,0,255);
Vec3b const SILVER = Vec3b(192,192,192);
Vec3b const GRAY = Vec3b(128,128,128);
Vec3b const MAROON = Vec3b(0,0,128);
Vec3b const OLIVE = Vec3b(0,128,128);
Vec3b const GREEN = Vec3b(0,128,0);
Vec3b const PURPLE = Vec3b(128,0,128);
Vec3b const TEAL = Vec3b(128,0,128);
Vec3b const NAVY = Vec3b(128,0,0);

std::vector<Vec3b> COLORS {BLACK,WHITE,RED,LIME,BLUE,YELLOW,CYAN,MAGENTA,SILVER,GRAY,MAROON,OLIVE,GREEN,PURPLE,TEAL,NAVY};



#endif /* SRC_COLORS_HPP_ */
