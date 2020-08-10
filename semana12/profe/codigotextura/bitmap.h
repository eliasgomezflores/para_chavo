#ifndef __BITMAP__
#define __BITMAP__

#include <string>
#include <cstdio>
#include <windows.h>
#include <wingdi.h>

using namespace std;

typedef unsigned char Pixel;

/* helper function */

inline Pixel toByte(double value){
  if(value>255.0)   value = 255.0;
  else if(value<0.0)  value = 0.0;
  return (Pixel)(value+0.5); // rounded
}

/* Bitmap class */

class Bitmap{
  public:
    /* constructor */
    Bitmap():_f(NULL){}
    Bitmap(const string& fn, const char* flags){
      if(!open(fn, flags))perror("File open failed");
    }

    /* buffers: pixel in ONE row */
    Pixel y[1920];
    Pixel u[1920];
    Pixel v[1920];

    // open("xxx.bmp", "rb")
    //
    bool open(const string& filename, const char* flags);
    bool close();
    bool eof();

    void readHeader();
    void copyHeaderFrom(Bitmap b){
      _file_header = b._file_header;
      _info_header = b._info_header;
    }
    void writeHeader();
    void printHeader();

    bool readRow();
    bool writeRow();

    FILE* getFileHandle(){
      return _f;
    }

  private:
    BITMAPFILEHEADER _file_header;
    BITMAPINFOHEADER _info_header;
    FILE *_f;
};

#endif // __BITMAP__