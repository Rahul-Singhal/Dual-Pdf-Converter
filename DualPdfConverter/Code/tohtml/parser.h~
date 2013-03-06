#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include"lastLetter.h"
#include"html_class.h"

using namespace std;

class parser{
	
   private:
	
	string bodyString;		  //the string that will extract text from the pdf and will get written to the body.txt file.
	font currentFont;		    //font of the last character read
	font nextFont;			    //font of the current character being read
	lastLetter prevLetter;	//object for the last letter that was read. stores information about the last letter like
						            	//letter width , character , x coordinate , y coordinate etc
	html_class hClass ;		  //the html class object to control class formation for the html code
	string divLine;			    //string for the div text for the current body
	FILE* fpIn;				      //the input file that was extracted using the java code and 
							            //contains information character by character
   	FILE* fpOut;			    //the output file to which the output is being written i.e body.txt

   public:
  //constructor reads the first character and forwards the further reading control to redText()
  parser(int divNo);

  //reads the textLocations.txt file line by line
  void readText();
   	
  //to check if the last two characters read were in the same word by looking at the gap between them
	bool checkWordContinuity(double prevPos,double newPos,double width);
	
	//check if the two characters have same font and are in the same div of the final html code
	bool checkDivContinuity(double prevPos,double newPos,double width,double space);
	
	//this will terminate the current div by enclosing the text read uptil now in this div and start a new div
	void terminateDiv();
	
	//write the div formed in the output file , i.e body.txt
	void writeBodySyntax(string & str);

	//processes the string of font extracted from the pdf and extracts font family , weight and style from that string
	void processFontType(string & fontType,string & fontFamily,string & style,string & weight);

	//extracts the font string from the input file
	string extractFont(FILE * fp);

   	
};

#endif
