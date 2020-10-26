// Driver code for the Image-Stegano header
#include <iostream>
// #include "include/ImageStegano.hpp"
#include "include/Utils.hpp"

int main(int argc, char const *argv[])
{
//   // init
//   ImageStegano decodeImage("/mnt/sda1/Pictures/Wallpapers/PatrickShocked.jpg", "Hello World! 🎧");

//   decodeImage.printInfo();

//   decodeImage.setLenToDecode(90);

//   decodeImage.printInfo();

//   decodeImage.setTextToEncode("Changed the text ➕");

//   decodeImage.printInfo();

  // test utils
  std::string mystr = "10110111";
  int byteNum = 1;

  int byte = utils::byteFromBinStr(mystr, byteNum);

  std::cout<<"The byte is: "<<byte<<std::endl;

  return 0;
}
