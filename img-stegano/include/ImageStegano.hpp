// The Image-Stegano class for generating steganographic images
#pragma once
#if !defined(_IMAGE_STEGANO_)
#define _IMAGE_STEGANO_

// dependencies
#include <iostream>
#include <cstring>
#include <SFML/Graphics/Image.hpp>  // for dealing with images

// ---------------- Definitions --------------------- //
class ImageStegano
{
private:
  /*
      Input/Output image: sf::Image
      Input image path: std::string
      Input text: std::string
      *SizeX and *SizeY: unsigned int 
  */

  sf::Image _inputImage, _outputImage;
  uint _inputImageSizeX, _inputImageSizeY;
  std::string _inputImagePath, _inputText;

public:
  ImageStegano(std::string, std::string);
  void printInfo(void);
  ~ImageStegano();
};

// ------------------- Implementation ---------------------- //
ImageStegano::ImageStegano(std::string inputImagePath, std::string inputText)
{
  this->_inputImagePath = inputImagePath;
  this->_inputText = inputText;

  if(_inputImagePath.empty() || _inputImagePath.length() == 0)
  {
    // raise an error for empty path
    printf("::-> Empty path for the image file is not allowed\n");
    exit(1);
  }

  if(!_inputImage.loadFromFile(_inputImagePath))
  {
    // error opening the file
    printf("::-> Error opening the image file. Make sure the path is correct\n");
    exit(1);
  }

  // from the size create the output image
  this->_inputImageSizeX = this->_inputImage.getSize().x;
  this->_inputImageSizeY = this->_inputImage.getSize().y;
  // set the color to Black
  this->_outputImage.create(this->_inputImageSizeX, this->_inputImageSizeY,
  sf::Color::Black);
}

void ImageStegano::printInfo(void)
{
  std::cout<<"Input image path: "<<_inputImagePath<<"\n";
  std::cout<<"Input text to hide: "<<_inputText<<"\n";
  std::cout<<"Size of input image: "<<_inputImageSizeX<<" x "<<_inputImageSizeY<<"\n";
  std::cout<<"Output image size: "<<(uint)_outputImage.getSize().x<<" x "<<
  (uint)_outputImage.getSize().y<<"\n";
}

ImageStegano::~ImageStegano()
{
  // clean up
}

#endif  // _IMAGE_STEGANO_
