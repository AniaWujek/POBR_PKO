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

  image = imread( "images/w5.jpg" );


    if( !image.data )
      {
        printf( "No image data \n" );
        return -1;
      }
    //Mat hist = histogram(image);

    Mat reduced = reduceResolution(image, 2);

    Mat red = findColorRel(reduced, 10, 2);
    Mat hsv = BGR2HSV(reduced);
    Mat filt = filterHsv(hsv, 50,120,10,100, 0,100);
    Mat and_red = AND_image(filt, red);
    Mat op = open(and_red, 3);
    Mat dil = dilate(op, 3, 1);
    Mat final = restoreResolution(dil, image, 2);

    Mat red2 = findColorRel(final, 10, 2);
    Mat hsv2 = BGR2HSV(final);
    Mat filt2 = filterHsv(hsv2, 50,120,10,100, 0,100);
    Mat and_red2 = AND_image(filt2, red2);
    Mat op2 = open(and_red2, 3);
    Mat cl2 = close(op2, 3);

    Mat label = rozrost(op);

    //Mat roz = rozrostObszaru(final);




    //Mat adjust = adjustRed(hist);


   /* Mat red2 = findColorRel(final, 10, 2);
    Mat hsv2 = BGR2HSV(final);
    Mat filt2 = filterHsv(hsv2, 50,120, 10,100, 0,100);
    Mat and_red2 = AND_image(filt2, red2);
    //Mat eroded2 = erode(and_red2, 3, 3);
    //Mat dilated2 = dilate(eroded2, 3, 3);
    Mat label = labels(and_red2);*/

  /*Mat red = findColorRel(image, 10, 2);
  Mat hsv = BGR2HSV(image);
  Mat filt = filterHsv(hsv, 0,120, 40,100, 0,100);
  //Mat white = filterHsv(hsv, 0,360, 0,30, 40,100);
  //Mat white2 = findWhite(image, 240);
  //Mat and_white = AND_image(white, white2);
  Mat and_red = AND_image(filt, red);
  //Mat andd = OR_image(and_white, and_red);
  Mat eroded = erode(and_red, 3, 1);
  Mat dilated = dilate(eroded, 3, 1);
  Mat label = labels(dilated);*/

  //Mat object = retrieveObject(label, Vec3b(17,17,17));
  //Mat remove = removeSmallObjects(label);
  //analyzeObjects(object);
  //Mat final = restoreResolution(andd, image, 4);

  /*Mat red1 = findColorRel(andd, 10, 2);
  Mat hsv1 = BGR2HSV(andd);
  Mat filt1 = filterHsv(hsv1, 0,120, 40,100, 0,100);
  Mat andd1 = AND_image(filt1, red1);
  Mat eroded1 = erode(andd1, 3, 3);
  Mat goodRED = dilate(eroded1, 3, 3);

  Mat label = labels(goodRED);*/







  //show(op, "open");
  show(cl2, "cl2");
  show(image, "image");
  show(label, "label");
  show(and_red2, "and_red2");
  //show(dilated2, "dilated2");
  //show(remove, "remove");
  //show(andd1, "image");
  //show(dilated1, "dilate");







  waitKey(0);

  return 0;
}



