#include "Image.h"
#include <cmath>


void cs225::Image::lighten(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
        if (pixel.l + 0.1 > 1){
          pixel.l = 1;
        }
        else{
          pixel.l = pixel.l + 0.1;
        }
    }
  }
}
void cs225::Image::lighten(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.l + amount > 1){
        pixel.l = 1;
      }
      else{
        pixel.l = pixel.l + amount;
      }
    }
  }
}
void cs225::Image::darken(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.l - 0.1 < 0){
        pixel.l = 0;
      }
      else{
        pixel.l = pixel.l - 0.1;
      }
    }
  }
}
void cs225::Image::darken(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.l - amount < 0){
        pixel.l = 0;
      }
      else{
        pixel.l = pixel.l - amount;
      }
    }
  }
}
void cs225::Image::saturate(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.s + 0.1 > 1){
        pixel.s = 1;
      }
      else{
        pixel.s = pixel.s + 0.1;
      }
    }
  }
}
void cs225::Image::saturate(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.s + amount > 1){
        pixel.s = 1;
      }
      else{
        pixel.s = pixel.s + amount;
      }
    }
  }
}
void cs225::Image::desaturate(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.s - 0.1 < 0){
        pixel.s = 0;
      }
      else{
        pixel.s = pixel.s - 0.1;
      }
    }
  }
}
void cs225::Image::desaturate(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.s - amount < 0){
        pixel.s = 0;
      }
      else{
        pixel.s = pixel.s - amount;
      }
    }
  }
}
void cs225::Image::grayscale(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}
void cs225::Image::rotateColor(double degrees){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      double cur = pixel.h + degrees;
      while (cur < 0){
        cur = cur + 360;
      }
      while (cur > 360){
        cur = cur - 360;
      }
      pixel.h = cur;
    }
  }
}
void cs225::Image::illinify(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      
      int IlliniOrange = 11;
      int IlliniBlue = 216;
      // calculate the distance to illini orange and blue
      double dtoOrange = fmin(abs(pixel.h-IlliniOrange),(360-abs(pixel.h-IlliniOrange)));
      double dtoBlue = fmin(abs(pixel.h-IlliniBlue),(360-abs(pixel.h-IlliniBlue)));
      // set hue of the pixel
      if (dtoOrange>dtoBlue){
        pixel.h = IlliniBlue;
      }
      else{
        pixel.h = IlliniOrange;
      }
    }
  }
}
void cs225::Image::scale(double factor){
  cs225::PNG copy = PNG(*this);
  resize(unsigned(width()*factor),unsigned(height()*factor));
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & oldPixel = copy.getPixel(unsigned(x/factor), unsigned(y/factor));
      HSLAPixel & curPixel = this->getPixel(x,y);
      curPixel = oldPixel;
    }
  }
}

void cs225::Image::scale(unsigned w, unsigned h){
  double factor = fmin(double(w)/double(width()),double(h)/double(height()));
  scale(factor);
}
