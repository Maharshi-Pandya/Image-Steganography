// Driver code for the Image-Stegano header
#include <iostream>
#include "include/ImageStegano.hpp"

int main(int argc, char const *argv[])
{
  // init
  ImageStegano decodeImage("/mnt/sda1/Pictures/Wallpapers/PatrickShocked.jpg", 190);
  
  decodeImage.setTextToEncode("Hello World!");
  decodeImage.printInfo();

  decodeImage.setLenToDecode(360);
  decodeImage.printInfo();

  return 0;
}
