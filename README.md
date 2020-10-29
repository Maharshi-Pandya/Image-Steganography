## Image-Text Steganography

This is what Wikipedia says:

>**Steganography** is the practice of concealing a file, message, image, or video within another file, message, image, or video.

This C++ program allows to hide any text (including unicode characters and/or emojis) inside of any image provided that the text size is within the limit of the image size.

The procedure used here to generate steganographic images is `L.S.B` steganography i.e. steganography using the least significant bit of any data (pixels, in the case of images).

#### Sources to learn

- [L.S.B steganography in python](https://www.boiteaklou.fr/Steganography-Least-Significant-Bit.html)
- [Steganography using MATLAB](https://www.geeksforgeeks.org/lsb-based-image-steganography-using-matlab/)
- [Blog about L.S.B steganography](https://towardsdatascience.com/hiding-data-in-an-image-image-steganography-using-python-e491b68b1372)