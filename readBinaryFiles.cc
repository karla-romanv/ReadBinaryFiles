/*
This program will read binary files and 
output a matrix of the read contents from the 
columns and row arrays set to gather what 
was in the ibinary file


 */

#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <string>
//#include "cdk.h"
#include <fstream>
#include <sstream>

//define global constants for
//the size of the matrix
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 18
//define the name of the matrix
#define MATRIX_NAME_STRING "Contents of the Binary File"
const int lengthOfString = 50;
using namespace std;


//create a class to hold the types to then be displayed in the matrix
class BinaryFile{

  //declare the values to be outputted to the matrix
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;


};

//create a class that will withold the length and
//and string contents
class BinaryFileRecords{

public:

  uint8_t stringLength;
  char stringBuffer[lengthOfString];

};


//within mai read the binary file ad convert to
//printable characters
//to then be appointed in a box inside the matrix

int main()
{


  //
  WINDOW*window;
  CDKSCREEN*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  //
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char *rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char *columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
   */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  ifstream binInfile("cs3377.bin",ios::in | ios::binary);


  BinaryFile *binaryHeader = new BinaryFile();
  BinaryFileRecords *binaryRecord = new BinaryFileRecords();


  binInfile.read((char *)binaryHeader, sizeof(BinaryFile));
  binInfile.read((char *)binaryRecord,sizeof(BinaryFileRecords));


  string magicNo, version,numRecords,strlenb,strlenB,strlenc,strlenC,strlend,strlenD, strlene, strlenE, seedMoney,leadership, entre, skillz;

  magicNo = "Magic: 0x";
  version = "Version: ";
  numRecords = "NumRecords: ";


  strlenB = "strlen: ";
  strlenC ="strlen: ";
  strlenC = "strlen: ";
  strlenD = "strlen: ";
  strlenE = "strlen: ";

  stringstream convert;

  convert << hex << uppercase << binaryHeader->magicNumber;
  magicNo += convert.str();
  convert.str("");


  convert << dec << binaryHeader->versionNumber;
  version += convert.str();
  convert.str("");


  convert << binaryHeader->numRecords;
  numRecords += convert.str();
  convert.str("");


  convert << binaryRecord->stringBuffer;
  strlenb = convert.str();
  convert.str("");
  convert << strlenb.length();
  strlenB += convert.str();
  convert.str("");


  binInfile.read((char *)binaryRecord,sizeof(BinaryFileRecords));
  convert << binaryRecord->stringBuffer;
  strlenc = convert.str();
  convert.str("");
  convert << strlenc.length();
  strlenC += convert.str();
  convert.str("");

  binInfile.read((char *)binaryRecord,sizeof(BinaryFileRecords));
  convert << binaryRecord->stringBuffer;
  strlend = convert.str();
  convert.str("");
  convert << strlend.length();
  strlenD += convert.str();
  convert.str("");


  binInfile.read((char *)binaryRecord,sizeof(BinaryFileRecords));
  convert << binaryRecord->stringBuffer;
  strlene = convert.str();
  convert.str("");
  convert << strlene.length();
  strlenE += convert.str();
  convert.str("");

  setCDKMatrixCell(myMatrix,1,1,magicNo.c_str());
  setCDKMatrixCell(myMatrix,1,2,version.c_str());
  setCDKMatrixCell(myMatrix,1,3,numRecords.c_str());
  setCDKMatrixCell(myMatrix,2,1,strlenB.c_str());
  setCDKMatrixCell(myMatrix,2,2,strlenb.c_str());
  setCDKMatrixCell(myMatrix,3,1, strlenC.c_str());
  setCDKMatrixCell(myMatrix,3,2,strlenc.c_str());
  setCDKMatrixCell(myMatrix,4,1,strlenD.c_str());
  setCDKMatrixCell(myMatrix,4,2,strlend.c_str());
  setCDKMatrixCell(myMatrix,5,1,strlenE.c_str());
  setCDKMatrixCell(myMatrix,5,2,strlene.c_str());

  drawCDKMatrix(myMatrix,true);

  unsigned char x;
  cin >> x;



// Cleanup screen
  endCDK( );
}

