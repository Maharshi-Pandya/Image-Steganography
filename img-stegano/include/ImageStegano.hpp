// The Image-Stegano class for generating steganographic images
#pragma once
#if !defined(_IMAGE_STEGANO_)
#define _IMAGE_STEGANO_

// dependencies
#include <iostream>
#include <cstring>
#include <SFML/Graphics/Image.hpp>  // for dealing with images

#include "Utils.hpp"

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

  bool _wannaEncode = true, _doneEncoding = false;
  sf::Image _inputImage, _outputImage;
  uint _messLen;
  uint _inputImageSizeX, _inputImageSizeY;
  std::string _inputImagePath, _inputText;
  std::string _inputTextBin;

public:
  // overload for decoding
  ImageStegano(std::string, uint);
  ImageStegano(std::string, std::string);
  // conversions
  void inputTextToBinStr(void);
  // set the input text if want to encode
  void setTextToEncode(std::string);
  void setLenToDecode(uint);
  void createOutputImage(void);
  // encode and decode methods
  void encodeImage(void);
  std::string decodeImage(void);
  // save image
  void saveEncodedImage(std::string pathToSave);
  void printInfo(void);
  ~ImageStegano();
};

// ------------------- Implementation ---------------------- //
//-----------------------------------------------------------------------------------
ImageStegano::ImageStegano(std::string inputImagePath, uint messLen)
{
  this->_inputImagePath = inputImagePath;
  this->_messLen = messLen;

  if(!this->_messLen)
  {
    // raise error for 0 message length
    std::cerr<<"::-> Error: The message to be decoded must have length greater than 0\n";
    exit(1);
  }
  if(!this->_inputImage.loadFromFile(this->_inputImagePath))
  {
    // raise error for invalid path
    std::cerr<<"::-> Error opening the image file. Make sure the path is correct\n";
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
    std::cerr<<"::-> Error: Input text to hide cannot be empty\n";
    exit(1);
  }
  if(_inputImagePath.empty() || _inputImagePath.length() == 0)
  {
    // raise an error for empty path
    std::cerr<<"::-> Empty path for the image file is not allowed\n";
    exit(1);
  }
  if(!_inputImage.loadFromFile(_inputImagePath))
  {
    // error opening the file
    std::cerr<<"::-> Error opening the image file. Make sure the path is correct\n";
    exit(1);
  }

  // set the text bin str
  this->inputTextToBinStr();

  // from the size create the output image
  this->_inputImageSizeX = this->_inputImage.getSize().x;
  this->_inputImageSizeY = this->_inputImage.getSize().y;
  this->_wannaEncode = true;
  this->_doneEncoding = false;
}

//----------------------------------------------------------------------------------------------
// convert to bin set
void ImageStegano::inputTextToBinStr(void)
{
  this->_inputTextBin = "";   // empty the string first
  for(size_t i=0; i<_inputText.length(); i++)
  {
    this->_inputTextBin.append(utils::toBinStr((uint)_inputText[i]).to_string());
  }
  // printf("The binstr is: %s\n", _inputTextBin.c_str());
}

// -------------------------------------------------------------------------------------------

void ImageStegano::createOutputImage(void)
{
  // set the pixels from input image
  if(_wannaEncode)
  {
    this->_outputImage.create(_inputImageSizeX, _inputImageSizeY, sf::Color::Black);
    for(uint y=0; y<_inputImageSizeY; y++)
      for(uint x=0; x<_inputImageSizeX; x++)
      {
        _outputImage.setPixel(x, y, _inputImage.getPixel(x, y));
      }
  }
  else
  {
    // create a 0 x 0 empty image
    this->_outputImage.create(0, 0);
  }
}

//----------------------------------------------------------------------------------------------

void ImageStegano::setTextToEncode(std::string inputText)
{
  this->_inputText = inputText;
  this->_messLen = this->_inputText.length();
  if(inputText.empty() || this->_messLen == 0)
  {
    // raise error for empty text
    std::cerr<<"::-> Error: The input text to hide cannot be empty\n";
    exit(1);
  }
  // set the input text bin
  this->inputTextToBinStr();
  this->_wannaEncode = true;
  this->_doneEncoding = false;
}

//-----------------------------------------------------------------------------------------

void ImageStegano::setLenToDecode(uint messLen)
{
  this->_messLen = messLen;
  if(this->_messLen <= 0)
  {
    // raise error if mess len is zero
    std::cerr<<"::-> Error: The message length to decode cannot be zero\n";
    exit(1);
  }
  // unset the input text and bin str
  this->_inputText = "";
  this->_inputTextBin = "";

  this->_wannaEncode = false;
}

//------------------------------------------------------------------------------------

void ImageStegano::encodeImage(void)
{
  if(_wannaEncode)
  {
    createOutputImage();

    uint bitsEncoded = 0;
    uint temp_bit = 0; int next_bit;  // for encoding
    uint totalBitsToEncode = _messLen * 8;
    // 0: red, 1: green, 2: blue
    uint8_t col_lsbs[3]; 
        
    // loop through the image pixels
    for(uint y=0; y<_inputImageSizeY; y++)
    {
      for(uint x=0; x<_inputImageSizeX; x++)
      {
        if(bitsEncoded >= totalBitsToEncode)
        {
          _doneEncoding = true;
          return;
        }
        // get the red, green, blue channels at pixel P(x, y)
        sf::Color curr_pixel = _inputImage.getPixel(x, y);
        col_lsbs[0] = curr_pixel.r;
        col_lsbs[1] = curr_pixel.g;
        col_lsbs[2] = curr_pixel.b;
        
        // TODO: get the next bit from input text bin and set lsbs
        for(int i=0; i<3; i++)
        {
          // get the next bit and compare with the lsb
          next_bit = (uint8_t)utils::getNextBitFrom(_inputTextBin);
          if(next_bit != -1)  
          { // bits still remain to encode
          
            temp_bit = (col_lsbs[i] & 1) ^ next_bit;  // xor compare
            col_lsbs[i] += temp_bit;
            bitsEncoded++;
          }
        }
        // set the output image pixel
        sf::Color out_col = sf::Color(col_lsbs[0], col_lsbs[1], col_lsbs[2], curr_pixel.a);
        _outputImage.setPixel(x, y, out_col);
      }
    }
  }
}

//---------------------------------------------------------------------------------------
void ImageStegano::saveEncodedImage(std::string pathToSave)
{
  if(pathToSave.empty() || pathToSave.length() == 0)
  {
    std::cerr<<"::-> Error: Dude! The given path is empty. Try again\n";
    exit(1);
  }
  if(!_doneEncoding)
  {
    std::cerr<<"::-> Error: Dude, how can you save the image without encoding? Go get a life!\n";
    exit(1);
  }
  if(!_outputImage.saveToFile(pathToSave))
  {
    // error saving to disk
    std::cerr<<"::-> Some error occurred while saving...Try again with valid path and/or file extension\n";
    exit(1);
  }
}

//-----------------------------------------------------------------------------------------

void ImageStegano::printInfo(void)
{
  std::cout<<"Input image path: "<<_inputImagePath<<"\n";
  std::cout<<"The message to extract/encode, has length: "<<_messLen<<"\n";
  if(!_inputText.empty())
  {
    std::cout<<"Input text to hide: "<<_inputText<<"\n";
    std::cout<<"Input text binary form: "<<_inputTextBin<<"\n";
  }
  std::cout<<"Size of input image: "<<_inputImageSizeX<<" x "<<_inputImageSizeY<<"\n";
}

//-----------------------------------------------------------------------------------------

ImageStegano::~ImageStegano()
{
  // clean up
}

#endif  // _IMAGE_STEGANO_
