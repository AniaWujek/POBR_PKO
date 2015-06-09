/*
 * PKO_logo.cpp
 *
 *  Created on: 18 maj 2015
 *      Author: anna
 */

#include "Basic.hpp"

using namespace cv;



int main( int argc, char** argv )
{
  Mat image;




  /*Mat reduced = reduceResolution(image, 4);

  Mat median = medianFilter(reduced, 3);
  Mat white = findWhite(median, 90, 100);
  Mat red = findColorRel(median, 10, 2);
  Mat both = OR_image(white, red);

  Mat eroded = erode(both, 3, 2);
  Mat dilated = dilate(eroded, 3, 2);

  Mat original = restoreResolution(dilated, image, 4);

  Mat median1 = medianFilter(original, 3);
  Mat white1 = findWhite(median1, 90, 100);
  Mat red1 = findColorRel(median1, 10, 2);
  Mat both1 = OR_image(white1, red1);

  Mat eroded1 = erode(both1, 3, 2);
  Mat dilated1 = dilate(eroded1, 3, 2);

  Mat final = restoreResolution(dilated1, image, 1);
  Mat label = labels(dilated1);*/

  /*Mat hsv = BGR2HSV(image);

  Mat filt = filterHsv(hsv, 0,120, 40,100, 0,100);

  Mat eroded = erode(filt, 5, 3);*/

  //Mat reduced = reduceResolution(image, 4);

  image = imread( "images/t17.jpg" );


    if( !image.data )
      {
        printf( "No image data \n" );
        return -1;
      }
    //Mat hist = histogram(image);


    /*
    ZNAJDOWANIE KOLEK DOBRE
    Mat reduced = reduceResolution(image, 2);
    Mat red = findColorRel(image, 35, 2);
    Mat hsv = BGR2HSV(image);
    Mat opencvHsv;
    Mat filt = filterHsv(hsv, 0,5, 130,180,0,255, 0,255);
    Mat and_red = AND_image(filt, red);
    Mat op = open(and_red, 1);
    Mat cl = close(op, 1);
    std::vector<Element> obiekty = znajdzKola(cl);
    for(int i = 0; i < obiekty.size(); ++i) {
    	std::cout<<obiekty[i].type << std::endl;
    }
    //Mat final = restoreResolution(roz, image, 1);

    */
    Mat median = medianFilter(image, 3);
    Mat contrast = adjustContrast(median, 2.0);
    Mat white = findWhite(contrast, 40, 180);
    Mat hsv = BGR2HSV(contrast);
    Mat filt = filterHsv(hsv, 80,135, 0,0,0,75, 70,255);
    Mat and_white = AND_image(filt, white);
    Mat op = open(and_white, 1);
    Mat cl = close(op, 1);
    Mat cll = clone(cl);
    std::vector<Element> obiekty = znajdzLiteryBiale(cl);
    for(int i = 0; i < obiekty.size(); ++i) {
        	std::cout<<obiekty[i].type << std::endl;
        }



  //show(opencvHsv, "opencvHsv");
  show(image, "image");
  show(cll, "cll");
  show(cl, "cl");
  //show(final, "final");
  //show(dilated1, "dilate");







  waitKey(0);

  return 0;
}



