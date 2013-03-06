/*A class that takes care of various html classes that are formed due to
different types of div styling in html code*/


#ifndef HTML_CLASS_H
#define HTML_CLASS_H

#include<string>
#include<map>
#include<cstdio>
#include<utility>
#include<iostream>
#include "font.h"
using namespace std;



class html_class{
	map<font , int> fontClassNumMap;	//A map storing the class number corresponding to the font.
	int numOfClasses;					//number of different html classes formed uptil now
	FILE * headFile;					//the file named head.txt storing the class declaration for the final html code
	int divNo;							//this gives us the div number corresponding to the page number of the pdf which
										//is currently being processed

public:

	html_class(){

	}

	html_class(int div){
		divNo = div;
		numOfClasses = 0;
		headFile = fopen("head.txt" , "a");
	}


	/*check if the class is already present in the map. if yes return its map otherwise return -1*/
	int isPresent(font f){
		map<font , int>::iterator it;
		it = fontClassNumMap.find(f);
		if(it == fontClassNumMap.end()) return -1;
		else {
			return it->second;
		}
	}

	/*add a new class to the map and hence to the html code being generated*/
	int addClass(font & f){
		fontClassNumMap.insert(pair<font , int>(f , numOfClasses));
		numOfClasses++;
		writeHeadSyntax(f);
		return (numOfClasses-1);
	}

	int getCurrentSize(){
		return numOfClasses;
	}

	/*write the syntax for the class styling in the file head.txt which 
	will actually form the head of our final html file */
	void writeHeadSyntax(font f){
		char chr[4];
		sprintf(chr , "%d" , (numOfClasses-1)); 
		char temp[10];
		sprintf(temp , "#div_%d" , divNo);
		string str = temp;
		str += " .class_";
		str += chr;
		str += "{font-family:";
		string temstr  = (f.getFamily()).substr(0,13);
		if(temstr == "TimesNewRoman") str += "Times New Roman";
		else str += f.getFamily();
		str += ",Times New Roman";
		str += ";font-style:";
		if(f.getStyle() != ""){
			str += f.getStyle();
		}
		else str += "normal";
		str += ";font-weight:";
		if(f.getWeight() != ""){
			str += f.getWeight();
		}
		else str += "normal";
		if(f.getColor() != ""){
			str += ";color:";
			str += f.getColor();
		}
		str += ";font-size:";
		char ch[20];
		sprintf(ch , "%gpx;}\n", f.getSize());
		fprintf(headFile , "%s%s\n", str.c_str() , ch );
	}

	void closeFile(){
		fclose(headFile);
		
	}

};

#endif
