/*
 * Basic.hpp
 *
 *  Created on: 18 maj 2015
 *      Author: anna
 */

#ifndef SRC_BASIC_HPP_
#define SRC_BASIC_HPP_

#include <cv.h>
#include <highgui.h>

using namespace cv;

void show(Mat& img, const string& name) {
	namedWindow( name, WINDOW_NORMAL );
	resizeWindow(name, 700, 1000);
	imshow( name, img );
}

Mat findColorRel(Mat& _img, int thresh, int color) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i< img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j)[color] > img(i,j)[(color+1)%2] + thresh && img(i,j)[color] > img(i,j)[(color+2)%2] + thresh) {
				result(i,j) = Vec3b(255,255,255);
			}
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
				result(i,j) = Vec3b(255,255,255);
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

bool myComp(cv::Vec3b elem1, cv::Vec3b elem2) {
    return elem1[0]+elem1[1]+elem1[2] < elem2[0]+elem2[1]+elem2[2];
}


Mat medianFilter(Mat& _img, int size) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	int rank = size*size / 2 + 1;

	std::vector<cv::Vec3b> values;


	for (int i = size / 2; i < img.rows - size / 2; ++i){
		if(i % 200 == 0) std::cout << "Wiersz " << i << '\r' << std::flush;
		for (int j = size / 2; j < img.cols - size / 2; ++j) {
			values.clear();
			for (int k = -size / 2; k <= size / 2; ++k)
				for (int l = -size / 2; l <= size / 2; ++l) {
					values.push_back(cv::Vec3b(img(i + k, j + l)));

				}

            std::sort(values.begin(), values.end(), myComp);
			//values = algHoara(values, 5);



			cv::Vec3b finalPoint = values[rank];

			result(i, j) = finalPoint;

			}
		}


	return result;
}

Mat clone(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			result(i,j) = img(i,j);
		}
	return result;
}

Mat dilate(Mat& _img, int size, int iterations) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;
	bool white;

	for(int iter = 0; iter < iterations; ++iter) {
		std::cout<<"iteracja: "<<iter<<std::endl;
		for (int i = size / 2; i < img.rows - size / 2; ++i){
				for (int j = size / 2; j < img.cols - size / 2; ++j) {
					white = false;
					for (int k = -size / 2; k <= size / 2; ++k) {
						for (int l = -size / 2; l <= size / 2; ++l) {
							if(img(i+k,j+l)[0] + img(i+k,j+l)[1] + img(i+k,j+l)[2] == 765) {
								white = true;
								break;
							}

						}
						if(white)
							break;
					}



					if(white)
						result(i, j) = Vec3b(255,255,255);

					}
				}
		img = clone(result);
		result = clone(res); //.clone();

	}




	return result;
}



Mat erode(Mat& _img, int size, int iterations) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;
	bool black;

	for(int iter = 0; iter < iterations; ++iter) {
		std::cout<<"iteracja: "<<iter<<std::endl;
		for (int i = size / 2; i < img.rows - size / 2; ++i){
				for (int j = size / 2; j < img.cols - size / 2; ++j) {
					black = false;
					for (int k = -size / 2; k <= size / 2; ++k) {
						for (int l = -size / 2; l <= size / 2; ++l) {
							if(img(i+k,j+l)[0] + img(i+k,j+l)[1] + img(i+k,j+l)[2] == 0) {
								black = true;
								break;
							}

						}
						if(black)
							break;
					}



					if(!black)
						result(i, j) = Vec3b(255,255,255);


					}
				}
		img = clone(result);
		result = clone(res); //.clone();

	}




	return result;
}

Mat merge(Mat& _img1, Mat& _img2) {
	Mat res(_img1.rows, _img1.cols, CV_8UC3);
	Mat_<cv::Vec3b> img1 = _img1;
	Mat_<cv::Vec3b> img2 = _img2;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img1.rows; ++i)
		for(int j = 0; j < img1.cols; ++j) {
			if((img1(i,j) == Vec3b(255,255,255)) || (img2(i,j) == Vec3b(255,255,255)))
				result(i,j) = Vec3b(255,255,255);
		}
	return result;
}

Mat findWhite(Mat& _img, int thresh, int thresh2) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j)[0] > thresh && img(i,j)[1] > thresh && img(i,j)[2] > thresh)
				if(abs(img(i,j)[0] - img(i,j)[1]) < thresh2 && abs(img(i,j)[0] - img(i,j)[2]) < thresh2)
					result(i,j) = Vec3b(255,255,255);
		}



	return result;
}

Mat krawedzie(Mat& _img, int size) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for (int i = size / 2; i < img.rows - size / 2; ++i){
		for (int j = size / 2; j < img.cols - size / 2; ++j) {

			for (int k = -size / 2; k <= size / 2; ++k) {
				for (int l = -size / 2; l <= size / 2; ++l) {


				}

			}

			}
		}



	return result;
}

Mat reduceResolution(Mat& _img, int times) {
	Mat res(_img.rows / times, _img.cols / times, CV_8UC3);

	if((_img.rows % times != 0) || (_img.cols % times != 0)) {
		std::cout << "error";
		return res;
	}


	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < result.rows; ++i)
		for(int j = 0; j < result.cols; ++j) {
			result(i,j) = img(i * times, j * times);
		}



	return result;
}

Mat restoreResolution(Mat& _reduced, Mat& _ori, int times) {
	Mat res(_ori.rows, _ori.cols, CV_8UC3);

	Mat_<cv::Vec3b> ori = _ori;
	Mat_<cv::Vec3b> result = res;
	Mat_<cv::Vec3b> reduced = _reduced;

	Mat_<cv::Vec3b> biggerReduced = dilate(reduced, 3, 5);

	for(int i = 0; i < ori.rows; ++i)
		for(int j = 0; j < ori.cols; ++j) {
			if(biggerReduced(i/times, j/times) == Vec3b(255,255,255)) {
				result(i,j) = ori(i,j);
			}
		}



	return result;
}

Mat labels(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < result.rows; ++i)
		for(int j = 0; j < result.cols; ++j) {
			result(i,j) = Vec3b(0,0,0);
		}

	int L = 1;
	Vec3b A, B, C, D, X;

	int tab[255];
	for(int i = 0; i < sizeof(tab)/sizeof(*tab); ++i)
		tab[i] = 0;

	for(int i = 1; i < img.rows-1; ++i)
		for(int j = 1; j < img.cols-1; ++j) {
			A = img(i-1, j-1);
			B = img(i-1, j);
			C = img(i-1, j+1);
			D = img(i, j-1);

			if(img(i,j)[0] + img(i,j)[1] + img(i,j)[2] != 0) {
				if(A[0]+A[1]+A[2] + B[0]+B[1]+B[2] + C[0]+C[1]+C[2] + D[0]+D[1]+D[2] == 0) {
					int k = 1;
					for(k = 50; k < sizeof(tab) && tab[k] != 0; k = k +5);
					tab[k] = k;

					L+=1;
					//result(i, j) = Vec3b(L,L,L);
					result(i, j) = Vec3b(k,k,k);
				}
				else {
					int L1 = 255;
					int L2 = 0;
					if(A[0]+A[1]+A[2] > 0) {
						if(result(i-1, j-1)[0] < L1)
							L1 = result(i-1, j-1)[0];
						if(result(i-1, j-1)[0] > L2)
							L2 = result(i-1, j-1)[0];
					}
					if(B[0]+B[1]+B[2] > 0) {
						if(result(i-1, j)[0] < L1)
							L1 = result(i-1, j)[0];
						if(result(i-1, j)[0] > L2)
							L2 = result(i-1, j)[0];
					}
					if(C[0]+C[1]+C[2] > 0) {
						if(result(i-1, j+1)[0] < L1)
							L1 = result(i-1, j+1)[0];
						if(result(i-1, j+1)[0] > L2)
							L2 = result(i-1, j+1)[0];
					}
					if(D[0]+D[1]+D[2] > 0) {
						if(result(i, j-1)[0] < L1)
							L1 = result(i, j-1)[0];
						if(result(i, j-1)[0] > L2)
							L2 = result(i, j-1)[0];
					}
					//result(i, j) = Vec3b(oldL,oldL,oldL);
					tab[L2] = L1;
					result(i, j) = Vec3b(L1,L1,L1);
				}
			}




		}

	for(int i = 0; i < result.rows; ++i)
		for(int j = 0; j < result.cols; ++j) {
			if(result(i,j)[0] + result(i,j)[1] + result(i,j)[2] != 0) {
				int color = tab[result(i,j)[0]];
				result(i,j)[0] = color;
				result(i,j)[1] = color;
				result(i,j)[2] = color;
			}
		}
	for(int i = 0; i < sizeof(tab)/sizeof(*tab); ++i)
			std::cout<<i<<"\t"<<tab[i]<<std::endl;


	return result;
}

Mat templateFunction(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {

		}



	return result;
}

#endif /* SRC_BASIC_HPP_ */
