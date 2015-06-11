/*
 * Basic.hpp
 *
 *  Created on: 18 maj 2015
 *      Author: anna
 */

#ifndef SRC_BASIC_HPP_
#define SRC_BASIC_HPP_

#include "Colors.hpp"
#include "ColorProcessor.hpp"
#include <algorithm>
#include <queue>
#include "Element.hpp"
#include <vector>

using namespace cv;



void show(Mat& img, const string& name) {
	namedWindow( name, WINDOW_NORMAL );
	resizeWindow(name, 700, 1000);

	imshow( name, img );
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

Mat clear(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			result(i,j) = BLACK;
		}
	return result;
}

Mat dilate(Mat& _img, int size, int iterations) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = clone(_img);
	Mat_<cv::Vec3b> result = clone(res);
	result = clear(result);
	bool white;

	for(int iter = 0; iter < iterations; ++iter) {
		//std::cout<<"iteracja: "<<iter<<std::endl;
		for (int i = size / 2; i < img.rows - size / 2; ++i){
				for (int j = size / 2; j < img.cols - size / 2; ++j) {
					white = false;
					for (int k = -size / 2; k <= size / 2; ++k) {
						for (int l = -size / 2; l <= size / 2; ++l) {
							if(img(i+k,j+l)[0] + img(i+k,j+l)[1] + img(i+k,j+l)[2] != 0) {
								white = true;
								break;
							}

						}
						if(white)
							break;
					}



					if(white)
						result(i, j) = WHITE;
					else
						result(i,j) = BLACK;


					}
				}
		img = clone(result);
		//result = clone(res); //.clone();

	}




	return result;
}


Mat erode(Mat& _img, int size, int iterations) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = clone(_img);
	Mat_<cv::Vec3b> result = clone(res);
	result = clear(result);
	bool black;

	for(int iter = 0; iter < iterations; ++iter) {
		//std::cout<<"iteracja: "<<iter<<std::endl;
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
						result(i, j) = WHITE;


					}
				}
		img = clone(result);
		//result = clone(res); //.clone();

	}




	return result;
}

Mat OR_image(Mat& _img1, Mat& _img2) {
	Mat res(_img1.rows, _img1.cols, CV_8UC3);
	Mat_<cv::Vec3b> img1 = _img1;
	Mat_<cv::Vec3b> img2 = _img2;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img1.rows; ++i)
		for(int j = 0; j < img1.cols; ++j) {
			if((img1(i,j) == WHITE) || (img2(i,j) == WHITE))
				result(i,j) = WHITE;
		}
	return result;
}

Mat AND_image(Mat& _img1, Mat& _img2) {
	Mat res(_img1.rows, _img1.cols, CV_8UC3);
	Mat_<cv::Vec3b> img1 = _img1;
	Mat_<cv::Vec3b> img2 = _img2;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img1.rows; ++i)
		for(int j = 0; j < img1.cols; ++j) {
			if((img1(i,j) == WHITE) && (img2(i,j) == WHITE))
				result(i,j) = WHITE;
			else
				result(i,j) = BLACK;
		}
	return result;
}

Mat NOT_image(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == WHITE)
				result(i,j) = BLACK;
			else
				result(i,j) = WHITE;
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

	//Mat_<cv::Vec3b> biggerReduced = dilate(reduced, 3, 5);

	for(int i = 0; i < ori.rows; ++i)
		for(int j = 0; j < ori.cols; ++j) {
			if(reduced(i/times, j/times) == GREEN) {
				result(i,j) = ori(i,j);
			}
		}



	return result;
}




Point getCenter(Mat& _img, Vec3b color) {

	Mat_<cv::Vec3b> img = _img;


	int left = img.cols-1;
	int right = 0;
	int top = img.rows - 1;
	int bottom = 0;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == color) {
				if(i > bottom)
					bottom = i;
				if(i < top)
					top = i;
				if(j > right)
					right = j;
				if(j < left)
					left = j;
			}
		}

	Point result = Point((bottom - top)/2+top, (right - left)/2+left);
	return result;
}

Point getBox(Mat& _img, Vec3b color) {

	Mat_<cv::Vec3b> img = _img;


	int left = img.cols-1;
	int right = 0;
	int top = img.rows - 1;
	int bottom = 0;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == color) {
				if(i > bottom)
					bottom = i;
				if(i < top)
					top = i;
				if(j > right)
					right = j;
				if(j < left)
					left = j;
			}
		}

	Point result = Point(right - left, bottom - top);
	return result;
}

float getDiagonal(Mat& _img, Vec3b color) {

	Mat_<cv::Vec3b> img = _img;


	int left = img.cols-1;
	int right = 0;
	int top = img.rows - 1;
	int bottom = 0;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == color) {
				if(i > bottom)
					bottom = i;
				if(i < top)
					top = i;
				if(j > right)
					right = j;
				if(j < left)
					left = j;
			}
		}

	float width = (float)(right - left);
	float height = (float)(bottom - top);
	return sqrt(pow(width, 2.0) + pow(height, 2.0));
}



Mat getROI(Mat& _img, Vec3b color) {

	Mat_<cv::Vec3b> img = _img;


	int left = img.cols-1;
	int right = 0;
	int top = img.rows - 1;
	int bottom = 0;

	for(int i = 1; i < img.rows-1; ++i)
		for(int j = 1; j < img.cols-1; ++j) {
			if(img(i,j) == color) {
				if(i > bottom)
					bottom = i+1;
				if(i < top)
					top = i-1;
				if(j > right)
					right = j+1;
				if(j < left)
					left = j-1;
			}
		}

	Mat res(bottom - top, right - left, CV_8UC3);
	Mat_<cv::Vec3b> result = res;
	int i, ii, j, jj;
	for(i = 0, ii = top; i < result.rows; ++i, ++ii)
		for(j = 0, jj = left; j < result.cols; ++j, ++jj) {
			result(i,j) = img(ii,jj);
		}

	return result;
}


int count_S(Mat& _img, Vec3b color) {

	Mat_<cv::Vec3b> img = _img;
	int sum = 0;




	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == color) {
				sum++;

			}
		}
	//std::cout<<"\tpole: "<<sum<<std::endl;
	//show(result, "object");
	return sum;
}

int count_L(cv::Mat& _I, Vec3b obiekt) {

	cv::Mat_<cv::Vec3b> I = _I;


	int suma = 0;

	cv::Vec3b tlo = cv::Vec3b(0,0,0);



	for(int i = 1; i < I.rows - 1; ++i) {
        for(int j = 1; j < I.cols - 1; ++j) {

            if(I(i,j) == obiekt) {
                if(I(i-1,j) == tlo || I(i,j-1) == tlo || I(i+1,j) == tlo || I(i,j+1) == tlo) {
                    suma++;

                }


            }

        }
    }
	//std::cout<<"\t\tobwod: "<<suma<<std::endl;

	//show(result, "fsedfges");
	return suma;
}

double W1(cv::Mat& _I, Vec3b color) {

	double S = (double)count_S(_I, color);
	return 2 * sqrt(S / 3.14159265359);
}

double W3(cv::Mat& _I, Vec3b color) {
	double S = (double)count_S(_I, color);
	double L = (double)count_L(_I, color);

	return L / (2 * sqrt(3.14159265359 * S)) - 1;

}

double moment(double p, double q, cv::Mat& _I, Vec3b color) {

	cv::Mat_<cv::Vec3b> I = _I;

	double m = 0.0;

	for (int i = 1; i < I.rows; ++i)
		for (int j = 1; j < I.cols; ++j) {
		if (I(i, j) == color)
			m += (pow((double)i, p)) * (pow((double)j, q));
		}

	return m;

}

double MOMENT(int p, int q, cv::Mat& _I, Vec3b color) {
	double M = 0.0;
	cv::Mat_<cv::Vec3b> I = _I;

	double ii = moment(1, 0, _I, color) / (double)count_S(_I, color);
	double jj = moment(0, 1, _I, color) / (double)count_S(_I, color);

	for (int i = 1; i < I.rows; ++i)
		for (int j = 1; j < I.cols; ++j) {
		if (I(i, j) == color)
			M += (pow(i - ii,p)) * (pow(j - jj,q));
		}
	return M;
}

double M8(cv::Mat& _I, Vec3b color) {
	double M30 = MOMENT(3, 0, _I, color);
	double M12 = MOMENT(1, 2, _I, color);
	double M21 = MOMENT(2, 1, _I, color);
	double M03 = MOMENT(0, 3, _I, color);
	double M00 = (double)count_S(_I, color);

	return (M30 * M12 + M21 * M03 - pow(M12, 2.0) - pow(M21, 2.0)) / pow(M00, 5.0);

}

double M3(cv::Mat& _I, Vec3b color) {

	double M30 = MOMENT(3, 0, _I, color);
	double M12 = MOMENT(1, 2, _I, color);
	double M21 = MOMENT(2, 1, _I, color);
	double M03 = MOMENT(0, 3, _I, color);
	double M00 = (double)count_S(_I, color);

	return (pow(M30 - 3.0 * M12, 2.0) + pow(3.0 * M21 - M03, 2.0)) / pow(M00, (double)5);

}

double M7(cv::Mat& _I, Vec3b color) {

	double M20 = MOMENT(2, 0, _I, color);
	double M02 = MOMENT(0, 2, _I, color);
	double M11 = MOMENT(1, 1, _I, color);
	double M00 = (double)count_S(_I, color);

	return (M20 * M02 - pow(M11, 2)) / pow(M00, 4);
}




bool noWhite(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == WHITE)
				return false;
		}
	return true;

}

void floodQ(Mat& _img, int x, int y, Vec3b color) {

	Mat_<cv::Vec3b> img = _img;
	std::queue<std::pair<int,int> > pozycje;
	std::pair<int,int> pozycja;
	pozycje.push(std::pair<int,int>(x,y));
	while(!pozycje.empty()) {

		pozycja = pozycje.front();
		pozycje.pop();
		if(pozycja.first >= 0 && pozycja.second >= 0  && pozycja.first < img.rows && pozycja.second < img.cols
				&& img(pozycja.first, pozycja.second) == WHITE) {
			img(pozycja.first, pozycja.second) = color;
			pozycje.push(std::pair<int,int>(pozycja.first - 1, pozycja.second));
			pozycje.push(std::pair<int,int>(pozycja.first + 1, pozycja.second));
			pozycje.push(std::pair<int,int>(pozycja.first, pozycja.second - 1));
			pozycje.push(std::pair<int,int>(pozycja.first, pozycja.second + 1));
		}
	}

	return;
}

void flood(Mat& _img, int x, int y, Vec3b color) {
	static int recursion = 0;
	Mat_<cv::Vec3b> img = _img;

	if(x < 0 || x >= img.rows || y < 0 || y >= img.cols)
		return;
	if(img(x,y) != WHITE || recursion > 10000)
		return;


	img(x,y) = color;
	flood(img, x - 1, y, color);
	//flood(img, x - 1, y - 1, color);
	flood(img, x + 1, y, color);
	//flood(img, x + 1, y - 1, color);
	flood(img, x, y - 1, color);
	//flood(img, x - 1, y + 1, color);
	flood(img, x, y + 1, color);
	//flood(img, x + 1, y + 1, color);

	return;
}

Mat checkSize(Mat& _img, Vec3b color) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	int suma = 0;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == color)
				suma++;
		}
	if(suma < 100) {
		for(int i = 0; i < img.rows; ++i)
			for(int j = 0; j < img.cols; ++j) {
				if(img(i,j) == color)
					result(i,j) = BLACK;
				else
					result(i,j) = img(i,j);
			}
		return result;
	}
	else
		return img;

}



void changeColors(Mat& _img, Vec3b color1, Vec3b color2) {

	Mat_<cv::Vec3b> img = _img;


	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == color1)
				img(i,j) = color2;

		}




}

std::vector<Element> znajdzKola(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;
	Mat temp;

	int licznik = 0;
	//int znalezione = 0;

	std::vector<Element> obiekty;
	Element ob;


	while(!noWhite(img)) {

		for(int i = 0; i < img.rows; ++i) {
			if((i % 100) == 0)
				std::cout << "KOLA: " << ((float)i) / ((float)img.rows) * 100.0 << " %" << std::endl;
			for(int j = 0; j < img.cols; ++j) {

				if(img(i,j) == WHITE) {

					//std::cout<<"FLOOD " << licznik << std::endl;

					floodQ(img, i, j, RED);
					//temp = getROI(img, RED);
					float w3 = W3(img, RED);
					float S = count_S(img, RED);

					if(S > 100 && w3 < 0.03 && w3 > -0.15) {
						ob.center = getCenter(img, RED);
						ob.diag = getDiagonal(img, RED);
						ob.box = getBox(img, RED);
						ob.scale = S / 1000.0;
						ob.type = "KOLO";
						obiekty.push_back(ob);
						changeColors(img, RED, GREEN);
						std::cout<<"KOLO: " << S<<std::endl;
						/*znalezione++;
						if(znalezione > 1) {
							changeColors(img, WHITE, BLACK);
							break;
						}*/

					}
					else
						changeColors(img, RED, BLACK);

					//img = checkSize(img, RED);

					licznik++;
					//if(licznik > 100) break;
					/*if(znalezione > 1) break;*/




				}
				//if(licznik > 100) break;
				/*if(znalezione > 1) break;*/




			}
		//if(licznik > 100) break;
		/*if(znalezione > 0) break;*/

		}



	}
	//std::cout<<licznik<<std::endl;



	return obiekty;
}

std::vector<Element> znajdzLiteryBiale(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;
	Mat temp;

	bool P, K, O;

	int licznik = 0;
	//int znalezione = 0;

	std::vector<Element> obiekty;

	while(!noWhite(img)) {

		for(int i = 0; i < img.rows; ++i) {
			if((i % 100) == 0)
				std::cout << "LITERY: " << ((float)i) / ((float)img.rows) * 100.0 << " %" << std::endl;
			for(int j = 0; j < img.cols; ++j) {

				if(img(i,j) == WHITE) {
					P = false;
					K = false;
					O = false;
					//std::cout<<"FLOOD "<< licznik << std::endl;

					licznik++;

					floodQ(img, i, j, RED);
					Mat temp = getROI(img, RED);
					float S = count_S(temp, RED);
					if(S > 900 && S < 30000) {


						float m8 = M8(img, RED);
						float m3 = M3(img, RED);
						float m7 = M7(img, RED);

						Element ob;

						if(m3 > 0.016 && m3 < 0.039
								&& m8 > -0.0027 && m8 < -0.0017
								&& m7 > 0.018 && m7 < 0.025) {
							P = true;
							ob.scale = S / 4000.0;
						}
						if(m3 > 0.0000086 && m3 < 0.000089
								&& m8 > -0.0001 && m8 < -0.0000005
								&& m7 > 0.008 && m7 < 0.015) {
							K = true;
							ob.scale = S / 2000.0;
						}
						if(m3 > 0.000075 && m3 < 0.00055
								&& m8 > -0.000053 && m8 < -0.000009
								&& m7 > 0.0081 && m7 < 0.013) {
							O = true;
							ob.scale = S / 2000.0;
						}


						if(P || O || K) {
							ob.center = getCenter(img, RED);
							ob.diag = getDiagonal(img, RED);
							ob.box = getBox(img, RED);

							if(P && !K && !O) {
								ob.type = "P";
								changeColors(img, RED, BLUE);
								//std::cout<<"P"<<std::endl;
							}
							if(!P && K && !O) {
								ob.type = "K";
								changeColors(img, RED, MAGENTA);
								//std::cout<<"K"<<std::endl;
							}
							if(!P && !K && O) {
								ob.type = "O";
								changeColors(img, RED, YELLOW);
								//std::cout<<"O"<<std::endl;
							}
							if(!P && K && O) {
								ob.type = "KO";
								changeColors(img, RED, PURPLE);
								//std::cout<<"KO"<<std::endl;
							}

							obiekty.push_back(ob);

							//std::cout<<"m8: "<<m8<<std::endl;
							//std::cout<<"m3: "<<m3<<std::endl;
							//std::cout<<"m7: "<<m7<<std::endl<<std::endl;
							//std::cout<<"center: " << ob.center <<std::endl;
							//std::cout<<"S: " << ob.scale <<std::endl;
							//std::cout<<"diag: " << ob.diag <<std::endl;
						}
						else {
							changeColors(img, RED, BLACK);
							/*std::cout<<"zLE m8: "<<m8<<std::endl;
							std::cout<<"zLE m3: "<<m3<<std::endl;
							std::cout<<"zLE: m7: "<<m7<<std::endl;*/

						}

						//std::cout<<"S: "<<S<<std::endl;

						//std::cout<<"w3: "<<w3<<std::endl;



						//if(licznik > 100) break;

					}
					else
						changeColors(img, RED, BLACK);

				}

				//if(licznik > 100) break;
			}
		//if(licznik > 100) break;
		}

	}
	//std::cout<<licznik<<std::endl;
	return obiekty;
}


Mat open(Mat& _img, int iterations) {


	Mat_<cv::Vec3b> img = clone(_img);

		img = erode(img, 3, iterations);
		img = dilate(img, 3, iterations);

	return clone(img);
}

Mat close(Mat& _img, int iterations) {


	Mat_<cv::Vec3b> img = clone(_img);

		img = dilate(img, 3, iterations);
		img = erode(img, 3, iterations);

	return clone(img);
}

Mat open2(Mat& _img, int iterations) {


	Mat_<cv::Vec3b> img = clone(_img);

	for(int i = 0; i < iterations; ++i) {
		img = erode(img, 3, iterations);
		img = dilate(img, 3, iterations);
	}


	return clone(img);
}

Mat close2(Mat& _img, int iterations) {


	Mat_<cv::Vec3b> img = clone(_img);

	for(int i = 0; i < iterations; ++i) {
		img = dilate(img, 3, iterations);
		img = erode(img, 3, iterations);
	}


	return clone(img);
}


int avgWhite(Mat& _img) {

	Mat_<cv::Vec3b> img = _img;
	float avg = 0;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			avg += (float)(img(i,j)[0] + img(i,j)[1] + img(i,j)[2]) / (float)(3 * img.rows * img.cols);
		}

	//avg /= img.rows * img.cols;



	return (int)avg;
}

Mat andFinal(Mat& _img1, Mat& _img2) {
	Mat res(_img1.rows, _img1.cols, CV_8UC3);
	Mat_<cv::Vec3b> img1 = _img1;
	Mat_<cv::Vec3b> img2 = _img2;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img1.rows; ++i)
		for(int j = 0; j < img1.cols; ++j) {
			if(img1(i,j) != BLACK)
				result(i,j) = img1(i,j);
			else
				result(i,j) = img2(i,j);
		}



	return result;
}

Mat mask(Mat& _img, Mat& _mask) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> mask = _mask;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(mask(i,j) == WHITE)
				result(i,j) = img(i,j);
			else
				result(i,j) = BLACK;
		}



	return result;
}

Mat removeSmall(Mat& _img, int dist) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			if(img(i,j) == WHITE) {
				int left = j;
				int right = j;
				int top = i;
				int bottom = i;
				while(img(bottom,j) == WHITE && bottom < img.rows && !(bottom - i > dist))
					bottom++;
				while(img(top,j) == WHITE && top > 0 && !(i - top > dist))
					top--;
				while(img(i,right) == WHITE && right < img.rows && !(right - j > dist))
					right++;
				while(img(i,left) == WHITE && left > 0 && !(j - left > dist))
					left--;

				if((right - left) + (bottom - top) > dist)
					result(i,j) = WHITE;
				else
					result(i,j) = BLACK;
			}
		}


	return result;
}

Mat drawRectangle(Mat& _img, Point p, float s, float ss, Vec3b color) {

	Mat_<cv::Vec3b> img = _img;
	int size1 = (int)s;
	int size2 = (int)ss;


	for(int i = max(p.x - size2/2, 0); i < min(p.x + size2/2, img.rows-1); ++i) {
		img(i,max(p.y - size1/2,0)) = color;
		img(i,max(p.y + 1 - size1/2,1)) = color;
		img(i,max(p.y + 2 - size1/2,2)) = color;

		img(i,min(p.y + size1/2, img.cols - 1)) = color;
		img(i,min(p.y - 1 + size1/2, img.cols - 2)) = color;
		img(i,min(p.y - 2 + size1/2, img.cols - 3)) = color;
	}

	for(int j = max(p.y - size1/2, 0); j < min(p.y + size1/2, img.cols-1); ++j) {
		img(max(p.x - size2/2, 0), j) = color;
		img(max(p.x + 1 - size2/2, 1), j) = color;
		img(max(p.x + 2 - size2/2, 2), j) = color;

		img(min(p.x + size2/2, img.rows - 1), j) = color;
		img(min(p.x - 1 + size2/2, img.rows - 2), j) = color;
		img(min(p.x - 2 + size2/2, img.rows - 3), j) = color;
	}



	return img;
}

Mat findLogos(Mat& _img, std::vector<Element> obiekty) {

	Mat_<cv::Vec3b> img = _img;

	std::vector<Element> KOLA;
	std::vector<Element> P;
	std::vector<Element> K;
	std::vector<Element> O;

	if(obiekty.size() == 0) return img;


	for(unsigned int i = 0; i < obiekty.size(); ++i) {
		if(obiekty[i].type == "KOLO")
			KOLA.push_back(obiekty[i]);
		if(obiekty[i].type == "P")
			P.push_back(obiekty[i]);
		if(obiekty[i].type == "K" || obiekty[i].type == "KO")
			K.push_back(obiekty[i]);
		if(obiekty[i].type == "O" || obiekty[i].type == "KO")
			O.push_back(obiekty[i]);
	}

	std::cout<<"Kola: "<<KOLA.size() << " K: " <<K.size() << " P: " << P.size() << " O: " <<O.size() << std::endl;


	for(unsigned int i = 0; i < KOLA.size(); ++i) {
		for(unsigned int j = 0; j < P.size(); ++j) {
			if(P[j].scale < 0.57 * KOLA[i].scale || P[j].scale > 1.76 * KOLA[i].scale
					|| abs(P[j].center.x - KOLA[i].center.x) > P[j].diag)
				continue;
			for(unsigned int k = 0; k < K.size(); ++k) {
				if(K[k].scale < 0.57 * KOLA[i].scale || K[k].scale > 1.76 * KOLA[i].scale
						|| K[k].scale < 0.57 * P[j].scale || K[k].scale > 1.76 * P[j].scale
						|| abs(K[k].center.x - KOLA[i].center.x) > P[j].diag)
					continue;
				for(unsigned int l = 0; l < O.size(); ++l) {
					if(O[l].scale < 0.57 * KOLA[i].scale || O[l].scale > 1.76 * KOLA[i].scale
							|| O[l].scale < 0.57 * P[j].scale || O[l].scale > 1.76 * P[j].scale
							|| O[l].scale < 0.57 * K[k].scale || O[l].scale > 1.76 * K[k].scale
							|| abs(O[l].center.x - KOLA[i].center.x) > P[j].diag)
						continue;
					else {
						drawRectangle(img, KOLA[i].center, KOLA[i].box.x, KOLA[i].box.y, GREEN);
						drawRectangle(img, P[j].center, P[j].box.x, P[j].box.y, BLUE);
						drawRectangle(img, K[k].center, K[k].box.x, K[k].box.y, MAGENTA);
						drawRectangle(img, O[l].center, O[l].box.x, O[l].box.y, YELLOW);
						//drawRectangle(img, Point(139,135), 10);
						//std::cout<<"JEST!\n" << KOLA[i].diag/2;
					}

				}
			}
		}
	}



	return img;
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
