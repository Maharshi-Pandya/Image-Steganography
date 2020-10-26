// Driver code for the Image-Stegano header
#include <iostream>
#include "include/ImageStegano.hpp"

int main(int argc, char const *argv[])
{
  // init
  ImageStegano encImage("../assets/PatrickShocked.jpg", "💟");

  encImage.setTextToEncode("Hello World! 💟✋");  // overwrite the previous text
  encImage.encodeImage();   // encode
  encImage.saveEncodedImage("SteganoOutput.jpg"); // save in the given path

  return 0;
}
