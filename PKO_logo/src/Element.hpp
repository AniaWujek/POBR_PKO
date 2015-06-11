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
	Point center;
	Point box;
	float diag;
	float scale;
	std::string type;
	Element(){
		scale = 1.0;
		diag = 0.0;
	};
	virtual ~Element(){};
};

#endif /* SRC_ELEMENT_HPP_ */
