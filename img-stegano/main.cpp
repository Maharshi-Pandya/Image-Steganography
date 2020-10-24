// Driver code for the Image-Stegano header
#include <iostream>
#include "include/ImageStegano.hpp"

int main(int argc, char const *argv[])
{
  // init
  ImageStegano decodeImage("/mnt/sda1/Pictures/Wallpapers/PatrickShocked.jpg", "Hello World! 🎧");

  decodeImage.printInfo();

  decodeImage.setLenToDecode(90);

  decodeImage.printInfo();

  decodeImage.setTextToEncode("Changed the text ➕");

  decodeImage.printInfo();

  return 0;
}
