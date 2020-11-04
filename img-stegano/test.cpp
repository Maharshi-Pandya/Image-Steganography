// Driver code for the Image-Stegano header
// Current file formats support: bmp, tga, png
#include <iostream>
#include "include/ImageStegano.hpp"

int main(int argc, char const *argv[])
{
  // init
  ImageStegano encImage("../../assets/PatrickShocked.jpg", "Hello World! 💟");

  // eg. text to encode
  std::string inputtext = "Wassup dude! Where you going? 🎧";

  encImage.setTextToEncode(inputtext);  // overwrite the previous text
  encImage.encodeImage();   // encode
  encImage.saveEncodedImage("SteganoOutput.bmp"); // save in the given path

  // decode the text from stegno image
  ImageStegano decImage("SteganoOutput.bmp", inputtext.length());
  std::string decStr = decImage.decodeTextFromImage();

  std::cout<<"The decoded text is: "<<decStr<<'\n';

  return 0;
}
