/*
 * Complex.hpp
 *
 *  Created on: 20 maj 2015
 *      Author: anna
 */

#ifndef SRC_COMPLEX_HPP_
#define SRC_COMPLEX_HPP_

#include "Colors.hpp"









Mat templateFunction2(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {

		}



	return result;
}




#endif /* SRC_COMPLEX_HPP_ */
