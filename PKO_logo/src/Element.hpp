/*
 * Element.h
 *
 *  Created on: 8 cze 2015
 *      Author: anna
 */

#ifndef SRC_ELEMENT_HPP_
#define SRC_ELEMENT_HPP_

#include <cv.h>
#include <highgui.h>

class Element {
public:
	Point p;
	float scale;
	std::string type;
	Element(){};
	virtual ~Element(){};
};

#endif /* SRC_ELEMENT_HPP_ */
