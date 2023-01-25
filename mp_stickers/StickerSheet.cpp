#include "StickerSheet.h"

Sticker::Sticker(){
  image_= NULL;
  x = 0;
  y = 0;
}

Sticker::Sticker(Sticker& other){
  image_= new Image(*(other.image_));
  x = other.x;
  y = other.y;
}


Sticker::Sticker(Image& sticker,int xc, int yc){
  image_= new Image(sticker);
  x = xc;
  y = yc;
}

Sticker::~Sticker(){
  delete image_;
}

//----------------------------------------------------------------------------------------

Image* StickerSheet::get_base()const{
  return base_;
}
unsigned StickerSheet::get_max()const{
  return max_;
}
vector<Sticker*>* StickerSheet::get_stickers()const{
  return stickers_;
}


StickerSheet::StickerSheet(const Image& picture, unsigned max){
   base_ = new Image(picture);
   max_ = max;
   stickers_ = new vector<Sticker*>;
}


StickerSheet::StickerSheet(const StickerSheet& other){
  base_ = new Image(*(other.get_base()));
  max_ = other.get_max();
  stickers_ = new vector<Sticker*>;
  for(unsigned i = 0; i < other.get_stickers()->size(); i++){
    (*stickers_).push_back(new Sticker(*((*other.get_stickers())[i])));
  }
}

StickerSheet::~StickerSheet(){
  delete base_;
  for(unsigned i = 0; i < stickers_->size();i++){
    delete (*stickers_)[i];
  }
  delete stickers_;
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y){
  if((*stickers_).size() >= max_){
    return -1;
  }
  else{
    Sticker* s = new Sticker(sticker,x,y);
    (*stickers_).push_back(s);
    return 0;
  }
}

void StickerSheet::changeMaxStickers(unsigned max){
  if(max < (*stickers_).size()){
    for(unsigned i = max; i < (*stickers_).size(); i++){
      delete (*stickers_)[i];
    }
    (*stickers_).resize(max);
  }
  max_= max;
}

Image* StickerSheet::getSticker(unsigned index){
  if(index < (*stickers_).size()){
    return (*stickers_)[index]->image_;
  }
  else{
    return NULL;
  }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
  delete base_;
  for(unsigned i = 0; i < stickers_->size();i++){
    delete (*stickers_)[i];
  }
  delete stickers_;
  base_ = new Image(*(other.get_base()));
  max_ = other.get_max();
  stickers_ = new vector<Sticker*>;
  for(unsigned i = 0; i < other.get_stickers()->size(); i++){
    (*stickers_).push_back(new Sticker(*((*other.get_stickers())[i])));
  }
  return *(this);
}

void StickerSheet::removeSticker(unsigned index){
  delete (*stickers_)[index];
  (*stickers_).erase((*stickers_).begin()+index);
}

Image StickerSheet::render()const{
  Image rendered = Image(*base_);
  for(unsigned i = 0; i < stickers_->size(); i++){
    Sticker* curSticker = (*stickers_)[i];
    for (unsigned x = curSticker->x; x < curSticker->x+curSticker->image_->width(); x++) {
      if(curSticker->x+curSticker->image_->width()>rendered.width()){
        rendered.resize(curSticker->x+curSticker->image_->width(),rendered.height());
      }
      for (unsigned y = curSticker->y; y < curSticker->y+curSticker->image_->height(); y++) {
        if(curSticker->y+curSticker->image_->height()>rendered.height()){
          rendered.resize(rendered.width(),curSticker->y+curSticker->image_->height());
        }
        cs225::HSLAPixel & secondpixel = curSticker->image_->getPixel(x-curSticker->x, y-curSticker->y);
        if(secondpixel.a == 0){
          continue;
        }
        cs225::HSLAPixel & firstpixel = rendered.getPixel(x, y);
        firstpixel = secondpixel;
      }
    }
  }
  return rendered;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(index > (*stickers_).size() ||(*stickers_)[index]->image_ == NULL){
    return false;
  }
  (*stickers_)[index]->x = x;
  (*stickers_)[index]->y = y;
  return true;
  
}




