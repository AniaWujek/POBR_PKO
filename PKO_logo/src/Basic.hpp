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
		std::cout<<"iteracja: "<<iter<<std::endl;
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

	int tab[254];
	for(int i = 0; i < sizeof(tab)/sizeof(*tab); ++i)
		tab[i] = 0;

	for(int i = 1; i < img.rows-1; ++i)
		for(int j = 1; j < img.cols-1; ++j) {
			if(img(i,j) == WHITE) {
				A = img(i-1, j-1);
				B = img(i-1, j);
				C = img(i-1, j+1);
				D = img(i, j-1);

				if((img(i,j)[0] + img(i,j)[1] + img(i,j)[2] != 0) && result(i,j) == BLACK) {
					if(A[0]+A[1]+A[2] + B[0]+B[1]+B[2] + C[0]+C[1]+C[2] + D[0]+D[1]+D[2] == 0) {
						int k;
						for(k = 1; k < sizeof(tab)/sizeof(*tab) && tab[k] != 0; k++);
						if(k < sizeof(tab)/sizeof(*tab)) {
							tab[k] = k;


							result(i, j) = Vec3b(k,k,k);
						}
						else
							result(i,j) = BLACK;

					}
					else {
						int L1 = 255;
						int L2 = 1;
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

						tab[L2] = L1;
						result(i, j) = Vec3b(L1,L1,L1);
					}
				}
			}

		}

	for(int i = 0; i < sizeof(tab)/sizeof(*tab); ++i) {
		tab[i] = tab[tab[i]];
		std::cout<<i<<" "<<tab[i]<<std::endl;
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

	Point result = Point(bottom - top, right - left);
	return result;
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
		for(int j = 0, jj = left; j < result.cols; ++j, ++jj) {
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
	double val;
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



Mat histogram(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;

	float pR[256];
	float pG[256];
	float pB[256];
	for(int i = 0; i < 256; ++i) {
		pR[i] = 0;
		pG[i] = 0;
		pB[i] = 0;

	}

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			pB[img(i,j)[0]]++;
			pG[img(i,j)[1]]++;
			pR[img(i,j)[2]]++;

		}
	for(int i = 255; i >= 0; --i) {
		for(int j = 0; j < i; ++j) {
			pB[i] += pB[j];
			pG[i] += pG[j];
			pR[i] += pR[j];
		}
	}

	int N = img.cols * img.rows;
	for(int i = 0; i < 256; ++i) {
			pR[i] /= N;
			pG[i] /= N;
			pB[i] /= N;

		}
	float D0R = 0;
	float D0G = 0;
	float D0B = 0;
	for(int i = 0; i < 256; ++i) {
		std::cout<<pR[i]<<" "<<pG[i]<<" "<<pB[i]<<std::endl;
	}

	int licznik = 0;
	while(pR[licznik] == 0){
		licznik++;
	}
	D0R = pR[licznik];
	licznik = 0;
	while(pG[licznik] == 0) {
		licznik++;
	}
	D0G = pG[licznik];
	licznik = 0;
	while(pB[licznik] == 0) {
		licznik++;
	}
	D0B = pB[licznik];

	for(int i = 0; i < img.rows; ++i)
		for(int j = 0; j < img.cols; ++j) {
			Vec3b color = img(i,j);
			result(i,j)[0] = ((float)pB[color[0]] - D0B) / (1.0 - D0B) * 255.0;
			result(i,j)[1] = ((float)pG[color[1]] - D0G) / (1.0 - D0G) * 255.0;
			//result(i,j)[2] = ((float)pR[color[2]] - D0R) / (1.0 - D0R) * 255.0;
			//result(i,j)[0] = color[0];
			result(i,j)[2] = color[2];
		}




	return result;
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
	int znalezione = 0;

	std::vector<Element> obiekty;
	Element ob;


	while(!noWhite(img)) {

		for(int i = 0; i < img.rows; ++i)
			for(int j = 0; j < img.cols; ++j) {
				if(img(i,j) == WHITE) {

					//std::cout<<"FLOOD " << licznik << std::endl;
					floodQ(img, i, j, RED);
					//temp = getROI(img, RED);
					float w3 = W3(img, RED);
					float S = count_S(img, RED);
					std::cout<<w3<<std::endl;
					if(S > 100 && w3 < 0.03 && w3 > -0.15) {
						ob.p = getCenter(img, RED);
						ob.scale = S;
						ob.type = "KOLO";
						obiekty.push_back(ob);
						changeColors(img, RED, GREEN);
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
	std::cout<<licznik<<std::endl;



	return obiekty;
}

std::vector<Element> znajdzLiteryBiale(Mat& _img) {
	Mat res(_img.rows, _img.cols, CV_8UC3);
	Mat_<cv::Vec3b> img = _img;
	Mat_<cv::Vec3b> result = res;
	Mat temp;

	int licznik = 0;
	int znalezione = 0;

	std::vector<Element> obiekty;



	while(!noWhite(img)) {

		for(int i = 0; i < img.rows; ++i)
			for(int j = 0; j < img.cols; ++j) {
				if(img(i,j) == WHITE) {


					floodQ(img, i, j, RED);
					Mat temp = getROI(img, RED);
					float S = count_S(temp, RED);
					if(S > 900) {
						float w1 = W1(temp, RED);
						float w3 = W3(temp, RED);
						float m3 = M3(img, RED);
						float m7 = M7(img, RED);
						Element ob;

						std::cout<<"S: "<<S<<std::endl;
						std::cout<<"w1: "<<w1<<std::endl;
						std::cout<<"w3: "<<w3<<std::endl;
						std::cout<<"m3: "<<m3<<std::endl;
						std::cout<<"m7: "<<m7<<std::endl<<std::endl;

						if(m3 < 0.00006 && m3 > 0.0 && w3 > 0.25 && w3 < 1.1 && m7 > 0.008 && m7 < 0.015) {
							ob.p = getCenter(img, RED);
							ob.scale = S;
							ob.type = "K";
							obiekty.push_back(ob);
							changeColors(img, RED, GREEN);


						}
						else if(m7 > 0.015 && m7 < 0.030 && m3 > 0.015 && m3 < 0.03 && w3 > 0.6 && m3 < 1.2) {
							ob.p = getCenter(img, RED);
							ob.scale = S;
							ob.type = "P";
							obiekty.push_back(ob);
							changeColors(img, RED, GREEN);
						}
						else if(m3 > 0.00006 && m3 < 0.0003 && w3 > 0.1 && w3 < 1.0 && m7 > 0.005 && m7 < 0.015) {
							ob.p = getCenter(img, RED);
							ob.scale = S;
							ob.type = "O";
							obiekty.push_back(ob);
							changeColors(img, RED, GREEN);

						}
						else
							changeColors(img, RED, BLACK);


						licznik++;
						//if(licznik > 100) break;

					}
					else
						changeColors(img, RED, BLACK);
				}
				//if(licznik > 100) break;
			}
		//if(licznik > 100) break;

	}
	std::cout<<licznik<<std::endl;
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
