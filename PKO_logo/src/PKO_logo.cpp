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

  image = imread( "images/testy/3.jpg" );


    if( !image.data )
      {
        printf( "No image data \n" );
        return -1;
      }

    //drawRectangle(image, Point(100,100), 100);

    Mat hsv = BGR2HSV(image);

    //ZNAJDOWANIE KOLEK DOBRE
    Mat red = findColorRel(image, 35, 2);

    Mat filt = filterHsv(hsv, 0,5, 130,180,0,255, 0,255);
    Mat and_red = AND_image(filt, red);
    Mat small = removeSmall(and_red, 20);
    Mat op = open(small, 1);
    Mat cl = close(op, 1);
    Mat cll = clone(cl);
    std::vector<Element> obiekty = znajdzKola(cl);


    //ZNAJDOWANIE BIALYCH LITER DOBRE
    std::cout<<"BIALE" << std::endl;
    //Mat median = medianFilter(image, 3);
    Mat contrast = adjustContrast(image, 2.0);
    Mat white = findWhite(contrast, 40, 180);
    Mat hsv2 = BGR2HSV(contrast);
    Mat filt2 = filterHsv(hsv2, 80,135, 0,0,0,75, 70,255);
    Mat and_white = AND_image(filt2, white);
    Mat small2 = removeSmall(and_white, 25);
    Mat op2 = erode(small2, 3, 2);
    Mat cl2 = dilate(op2, 3, 1);
    Mat cll2 = clone(cl2);
    std::vector<Element> obiekty2 = znajdzLiteryBiale(cl2);


    //ZNAJDOWANIE NIEBIESKICH LITER DOBRE
    std::cout<<"NIEBIESKIE" << std::endl;
    Mat notWhite = NOT_image(and_white);
    Mat image2 = mask(image, notWhite);
    Mat blue = findColorRel(image2, 15, 0);
    Mat hsv3 = BGR2HSV(image2);
    Mat filt3 = filterHsv(hsv3, 95,130, 0,0,30,255, 1,170);
    Mat small3 = removeSmall(filt3, 25);
    Mat op3 = open(small3, 1);
    Mat cl3 = close(op3, 1);
    Mat cll3 = clone(cl3);
    std::vector<Element> obiekty3 = znajdzLiteryBiale(cl3);



    obiekty.insert(obiekty.end(), obiekty2.begin(), obiekty2.end());
    obiekty.insert(obiekty.end(), obiekty3.begin(), obiekty3.end());

    for(unsigned int i = 0; i < obiekty.size(); ++i) {
        	std::cout<< " typ: " << obiekty[i].type << " skala: " << obiekty[i].scale << std::endl;
        }





    Mat finalTemp = andFinal(cl, cl2);
    Mat final = andFinal(finalTemp, cl3);
    Mat finalfinal = andFinal(final, image);
    findLogos(image, obiekty);




  //show(opencvHsv, "opencvHsv");
  //show(cll3, "cll3");
  show(finalfinal, "finalfinal");
  show(image, "image");
  //show(cll3, "cll3");
  //show(small, "small");
  //show(finalfinal, "finalfinal");







  waitKey(0);

  return 0;
}



