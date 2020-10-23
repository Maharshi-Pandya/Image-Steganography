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

  bool _wannaEncode = true;
  sf::Image _inputImage, _outputImage;
  uint _messLen;
  uint _inputImageSizeX, _inputImageSizeY;
  std::string _inputImagePath, _inputText;

public:
  // overload for decoding
  ImageStegano(std::string, uint);
  ImageStegano(std::string, std::string);
  // set the input text if want to encode
  void setTextToEncode(std::string);
  void setLenToDecode(uint);
  void createOutputImage(void);
  // encode and decode methods
  void encodeImage(void);
  std::string decodeImage(void);
  void printInfo(void);
  ~ImageStegano();
};

// ------------------- Implementation ---------------------- //
ImageStegano::ImageStegano(std::string inputImagePath, uint messLen)
{
  this->_inputImagePath = inputImagePath;
  this->_messLen = messLen;

  if(!this->_messLen)
  {
    // raise error for 0 message length
    std::cout<<"::-> Error: The message to be decoded must have length greater than 0\n";
    exit(1);
  }
  if(!this->_inputImage.loadFromFile(this->_inputImagePath))
  {
    // raise error for invalid path
    std::cout<<"::-> Error opening the image file. Make sure the path is correct\n";
    exit(1);
  }
  // set the size
  this->_inputImageSizeX = this->_inputImage.getSize().x;
  this->_inputImageSizeY = this->_inputImage.getSize().y;
  this->_wannaEncode = false;
}

ImageStegano::ImageStegano(std::string inputImagePath, std::string inputText)
{
  this->_inputImagePath = inputImagePath;
  this->_inputText = inputText;
  this->_messLen = this->_inputText.length();

  if(_inputText.empty() || this->_messLen == 0)
  {
    // raise error for empty input text
    std::cout<<"::-> Error: Input text to hide cannot be empty\n";
    exit(1);
  }
  if(_inputImagePath.empty() || _inputImagePath.length() == 0)
  {
    // raise an error for empty path
    std::cout<<"::-> Empty path for the image file is not allowed\n";
    exit(1);
  }
  if(!_inputImage.loadFromFile(_inputImagePath))
  {
    // error opening the file
    std::cout<<"::-> Error opening the image file. Make sure the path is correct\n";
    exit(1);
  }

  // from the size create the output image
  this->_inputImageSizeX = this->_inputImage.getSize().x;
  this->_inputImageSizeY = this->_inputImage.getSize().y;
  this->_wannaEncode = true;
}

void ImageStegano::createOutputImage(void)
{
  // set the color to black
  if(_wannaEncode)
    this->_outputImage.create(_inputImageSizeX, _inputImageSizeY, sf::Color::Black);
  else
  {
    // create a 0 x 0 empty image
    this->_outputImage.create(0, 0);
  }
}

void ImageStegano::setTextToEncode(std::string inputText)
{
  this->_inputText = inputText;
  this->_messLen = this->_inputText.length();
  if(inputText.empty() || this->_messLen == 0)
  {
    // raise error for empty text
    std::cout<<"::-> Error: The input text to hide cannot be empty\n";
    exit(1);
  }
  this->_wannaEncode = true;
}

void ImageStegano::setLenToDecode(uint messLen)
{
  this->_messLen = messLen;
  this->_inputText = "";
  if(this->_messLen <= 0)
  {
    // raise error if mess len is zero
    std::cout<<"::-> Error: The message length to decode cannot be zero\n";
    exit(1);
  }
  this->_wannaEncode = false;
}

void ImageStegano::printInfo(void)
{
  this->createOutputImage();

  std::cout<<"Input image path: "<<_inputImagePath<<"\n";
  std::cout<<"The message to extract/encode, has length: "<<_messLen<<"\n";
  if(!_inputText.empty())
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
