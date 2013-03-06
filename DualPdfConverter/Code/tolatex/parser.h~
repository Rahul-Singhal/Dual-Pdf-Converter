#ifndef PARSER_H
#define PARSER_H

/*the main parser file to read the pdf data letter by letter, utilize the font , x coordinate , y coordinate and other
attributes of this data to identify various objects of the latex code to be formed.after such identification 
this class calls parser handler object which creates the string containing the corresponding code and writes it to the output file*/

#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include"parserHandler.h"
#include"font.h"
#include"lastLetter.h"
#include<stack>
using namespace std;


class parser{

private:
	FILE * pdfData;               //the input file which was extracted using java code and is read letter by letter as in the pdf file.
	parserHandler pHandler;       //the parser handler object which creates the syntax of the generated output latex file and processes the string it is passed.
	font currentFont;             //the current font object corresponding to the last letter read.
	font nextFont;                //font object corresponding to the current letter that was read
	float pageWidth;              //the page width of the pdf page of which the data is being processed
	string bodyString;            //the string that is being formed as the letters from the pdfdata are read and passed to the parser handler for processing
	                              //and formation of final latex syntax
	lastLetter prevLetter;        //the lastLetter object containing the details about the last letter that was read from the pdf.
	int lineStartXCoord;          //the X coordinate of the character which is at the starting of the current line being read.
	bool bulletPossiblity;        //true if there is a possibility of bullet at the starting of line
	stack<float> bulletStack;     //stack containing the starting x coordinate of the bullets . This helps to check if the current bullets have ended or next
	                              //level of bullets have started
	stack<string> bulletType;     //stack containing the string representing the type of bullets
	                              // itemize for bullets , Alphabetic for A,B,C , alphabetic for (a),(b),(c) , numeric for 1,2,3
	float offset;                 //the offset from left margin of page , used for the calculation of the alignment of the text.
	
public:
	parser(string fileName);      //constructor, read the first letter and handles the control to readText()
	void readText();              //recursively reads the letters from the pdf data file and calls the corresponding method in parser handler class
	bool checkalphabeticBullet(); //check if there are alphabetic bullets like (a), (b)...
	bool checkAlphabeticBullet(); //check if there are Alphabetic bullets like A,B...
	bool checkIJKBullet();        //check if bullets are of type i,j,k
	bool checkBulletEnd(float x); //checks if the bullets have ended
	void skipBulletText();        //if there is a next bullet coresponding to the current bullet level , this methods skips the bullet text and calls the parser  
	                              //handler to create a next bullet
	string getAlignment(float x , float letterWidth); //gets alignment of the line by finding the x coordinate of mid point of the line and compares it with the 
	                                                  //mid point of the page
	bool bulletORSection(string & str); //check if there is a bullet or section
	void addSpaces(float n);      //add spaces according to the gap between the words
	void processFontType(string & fontType,string & fontFamily,string & style,string & weight); //process font string and get style , weight and family
	bool checkWordContinuity(double prePos,double newPos,double width); //check if the word is continuos
	string extractFont(FILE * fp);  //reads font string from the file
};

#endif
