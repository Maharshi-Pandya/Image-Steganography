// Driver code for the Image-Stegano header
#include <iostream>
#include "include/ImageStegano.hpp"

int main(int argc, char const *argv[])
{
  // init
  ImageStegano image("/mnt/sda1/Pictures/Wallpapers/PatrickShocked.jpg", "Hello World! 💟");
  // print the class information
  image.printInfo();

  return 0;
}
