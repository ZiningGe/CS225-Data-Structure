/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include "vector"
using cs225::Image;
using std::vector;

class Sticker{
public:
  Image* image_;
  unsigned x;
  unsigned y;
  
  Sticker();
  Sticker(Sticker& other);
  Sticker(Image& sticker,int xc, int yc);
  ~Sticker();
  
};


class StickerSheet{
public:
  StickerSheet(const Image& picture, unsigned max);
  StickerSheet(const StickerSheet& other);
  ~StickerSheet();
  
  Image* get_base()const;
  unsigned get_max()const;
  vector<Sticker*>* get_stickers()const;
  
  int addSticker(Image& sticker, unsigned x, unsigned y);
  void changeMaxStickers(unsigned max);
  Image* getSticker(unsigned index);
  const StickerSheet& operator=(const StickerSheet& other);
  void removeSticker(unsigned index);
  Image render()const;
  bool translate(unsigned index, unsigned x, unsigned y);
private:
  Image* base_;
  unsigned max_;
  vector<Sticker*>* stickers_;
};
 
