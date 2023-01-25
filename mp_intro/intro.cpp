#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "cmath"
#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG image;
  // count the number of pixel that has been changed
  int count = 0;
  image.readFromFile(inputFile);
  // iterate through one half of the pixel
  for (unsigned x = 0; x < image.width()/2 + 1; x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      // when half of the pixels have been processed, break the loop
      if (unsigned(count++) == image.height()*image.width()/2){
        break;
      }
      
      double temph,temps,templ,tempa;
      // get two pixels at corresponding location
      cs225::HSLAPixel & pixel = image.getPixel(x, y);
      cs225::HSLAPixel & pixel2 = image.getPixel(image.width()-x-1, image.height()-y-1);
      
      // switch two pixels
      temph = pixel.h;
      temps = pixel.s;
      templ = pixel.l;
      tempa = pixel.a;
      
      pixel.h = pixel2.h;
      pixel.s = pixel2.s;
      pixel.l = pixel2.l;
      pixel.a = pixel2.a;
      
      pixel2.h = temph;
      pixel2.s = temps;
      pixel2.l = templ;
      pixel2.a = tempa;
    }
  }
  image.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // this program draw a rainbow
  // iterate all pixels in the image
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      // get the pixel at the location(x,y)
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      // calculate the distance from the pixel to the buttom middle of the image
      double distance = sqrt((x-width/2)*(x-width/2)+(y-height)*(y-height));
      // set the value to the pixel
      if ( distance > 400 || distance < 300){
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 1;
      }
      else{
        pixel.h = 300-double(300)/100*(distance-300);
        pixel.s = 1;
        pixel.l = 0.5;
      }
    }
  }

  return png;
}
