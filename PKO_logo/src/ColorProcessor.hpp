/*
 * ColorProcessor.hpp
 *
 *  Created on: 20 maj 2015
 *      Author: anna
 */

#ifndef SRC_COLORPROCESSOR_HPP_
#define SRC_COLORPROCESSOR_HPP_

#include "Colors.hpp"

Mat BGR2GRAY(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			int color = img(i,j)[0] + img(i,j)[1] + img(i,j)[3];
			color /= 3;
			result(i,j) = Vec3b(color,color,color);
		}
	return result;
}

Mat adjustContrast(Mat& _img, float val) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	int color;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			color = img(i,j)[0] * val;
			result(i,j)[0] = color > 255 ? 255 : color;
			color = img(i,j)[1] * val;
			result(i,j)[1] = color > 255 ? 255 : color;
			color = img(i,j)[2] * val;
			result(i,j)[2] = color > 255 ? 255 : color;
		}
	return result;
}

Mat findColorRel(Mat& _img, int thresh, int color) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	float diff1, diff2;



	for(int i = 0; i< img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {

			diff1 = img(i,j)[color]*1.2 - (img(i,j)[(color+1)%2] + thresh);
			diff2 = img(i,j)[color]*1.2 - (img(i,j)[(color+2)%2] + thresh);

			if( diff1 > 0 || diff2 > 0) {
				if(img(i,j)[color] < 220 || (img(i,j)[color] >= 220  && diff1 > 50 && diff2 > 50))
					result(i,j) = WHITE;

			}
			else
				result(i,j) = BLACK;
		}
	return result;
}

Mat findColorRel2(Mat& _img, int thresh, int color) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	float diff1, diff2;



	for(int i = 0; i< img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {

			diff1 = img(i,j)[color]*1.2 - (img(i,j)[(color+1)%2] + thresh);
			diff2 = img(i,j)[color]*1.2 - (img(i,j)[(color+2)%2] + thresh);

			if( diff1 > 0 && diff2 > 0) {
				if(img(i,j)[color] < 150 || (img(i,j)[color] >= 150  && diff1 > 20 && diff2 > 20))
					result(i,j) = WHITE;

			}
			else
				result(i,j) = BLACK;
		}
	return result;
}

Mat findColor(Mat& _img, int thresh, int color) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i< img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j)[color] > thresh) {
				result(i,j) = WHITE;
			}
		}
	return result;
}

Mat adjustRed(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			result(i,j) = img(i,j);
			if(img(i,j)[2] > img(i,j)[0] + 50 && img(i,j)[2] > img(i,j)[1] + 50)
				img(i,j)[2] + 20 > 255 ? result(i,j)[2] = 255 : result(i,j)[2] = result(i,j)[2] + 20;
		}
	return result;
}

Mat findWhite(Mat& _img, int thresh1, int thresh2) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;


	//Mat temp = BGR2GRAY(img);

	//Mat_<cv::Vec3b> temp2 = adjustContrast(temp, 2.3);
	//result = temp2;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j)[0] > thresh2 && img(i,j)[1] > thresh2 && img(i,j)[2] > thresh2
					&& (abs(img(i,j)[0] - img(i,j)[1]) < thresh1 && abs(img(i,j)[1] - img(i,j)[2]) < thresh1)
						&& abs(img(i,j)[1] - img(i,j)[2]) < thresh1)
				result(i,j) = WHITE;
		}



	return result;
}

Vec3b BGR2HSV (Vec3b bgr) {
	float R = (float)bgr[2] / 255.0;
	float G = (float)bgr[1] / 255.0;
	float B = (float)bgr[0] / 255.0;

	float H, S, V;

	float Cmax, Cmin;
	if(R > G) {
		Cmax = R > B ? R : B;
		Cmin = G < B ? G : B;
	}
	else {
		Cmax = G > B ? G : B;
		Cmin = R < B ? R : B;
	}
	V = Cmax;
	if(V != 0.0) {
		S = (V - Cmin) / V;
	}
	else
		S = 0;

	if(V == R) {
		H = 60.0 * (G - B) / (V - Cmin);
	}
	else if(V == G) {
		H = 120.0 + 60.0 * (B - R) / (V - Cmin);
	}
	else if(V == B) {
		H = 240.0 + 60.0 * (R - G) / (V - Cmin);
	}

	if(H < 0)
		H += 360.0;
	V = 255.0 * V;
	S = 255.0 * S;
	H = H / 2.0;
	//std::cout<< H << "\t" << S << "\t" << V << std::endl;

	return Vec3b((int)H,(int)S,(int)V);
}

Mat BGR2HSV(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			result(i,j) = BGR2HSV(img(i,j));

		}



	return result;
}

Mat filterHsv(Mat& _img, int hlow1, int hhigh1, int hlow2, int hhigh2, int slow, int shigh, int vlow, int vhigh) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {

			if(((img(i,j)[0] >= hlow1 && img(i,j)[0] <= hhigh1) ||  (img(i,j)[0] >= hlow2 && img(i,j)[0] <= hhigh2)) &&
						img(i,j)[1] >= slow && img(i,j)[2] >= vlow && img(i,j)[1] <= shigh && img(i,j)[2] <= vhigh)
				result(i,j) = WHITE;
			//else
				//std::cout<<img(i,j)<<std::endl;
		}

	return result;
}



Mat templateFunction1(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {

		}



	return result;
}



#endif /* SRC_COLORPROCESSOR_HPP_ */
