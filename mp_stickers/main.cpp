#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image base;     base.readFromFile("base.png");
  Image img1;     img1.readFromFile("1.png");
  Image img3;     img3.readFromFile("3.png");
  Image img4;     img4.readFromFile("4.png");
  
  StickerSheet sheet(base, 3);
  sheet.addSticker(img1, 20, 200);
  sheet.addSticker(img3, 700, 200);
  sheet.addSticker(img4, 500, 500);
  
  (sheet.render()).writeToFile("myImage.png");
  
  
  return 0;
}
