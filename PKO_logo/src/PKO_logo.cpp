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
  image = imread( "images/test1.jpg" );

  if( !image.data )
    {
      printf( "No image data \n" );
      return -1;
    }

  /*Mat reduced = reduceResolution(image, 4);
  Mat median = medianFilter(reduced, 3);
  Mat white = findWhite(median, 90, 100);
  Mat red = findColorRel(median, 10, 2);
  Mat both = merge(white, red);

  Mat eroded = erode(both, 3, 2);
  Mat dilated = dilate(eroded, 3, 2);

  Mat original = restoreResolution(dilated, image, 4);

  Mat median1 = medianFilter(original, 3);
  Mat white1 = findWhite(median1, 90, 100);
  Mat red1 = findColorRel(median1, 10, 2);
  Mat both1 = merge(white1, red1);

  Mat eroded1 = erode(both1, 3, 2);
  Mat dilated1 = dilate(eroded1, 3, 2);

  Mat final = restoreResolution(dilated1, image, 1);*/

  Mat hsv = BGR2HSV(image);

  Mat filt = filterHsv(hsv, 0,120, 40,100, 0,100);

  //Mat label = labels(dilated1);



  show(image, "hsv");
  show(filt, "filt");
  //show(dilated1, "final");
  //show(dilated, "dil");
  //show(label, "label");






  waitKey(0);

  return 0;
}



