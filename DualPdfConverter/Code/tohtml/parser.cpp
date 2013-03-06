#include<iostream>
#include"parser.h"
#include<cmath>
#include<cstdlib>
using namespace std;

	//constructor reads the first character and forwards the further reading control to redText()
	parser::parser(int divNo){
		fpOut = fopen("body.txt","a");
		html_class temphClass(divNo);
		hClass = temphClass;
		fpIn = fopen("textLocations.txt","r");
		
		bodyString = "";
		float xCoord,yCoord,width,space,fontSize;
		
		string fontType;
		char c;

		float f1 , f2;
		fscanf(fpIn , "%g %g\n" , &f1 , &f2);
		string specialC = "";

		//the first character read
		c = fgetc(fpIn);
		//if the character is negative, it is a multicharacter special symbol. read until 
		//the complete symbol is read and store it in specialC string
		if((int)c < 0) {specialC += c; 
		while((int)(c = fgetc(fpIn)) < 0) specialC += c; 
			c = specialC[specialC.length()-1];
			specialC = specialC.substr(0 , specialC.length()-1);
		}

		//read the x coord , y coord , fontsize , width and space from the input file
		fscanf(fpIn," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(fpIn);
		prevLetter.setLastLetter(c,xCoord,yCoord,width);

		//set the current font using the data read above and add the class to the head file if the 
		//class corresponding to the current class doesn't exist uptil now
		string family,style,weight;
		processFontType(fontType,family,style,weight);
		currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)"); 
		int classNo = hClass.isPresent(currentFont);
  
		if(classNo == -1){
			classNo = hClass.addClass(currentFont);
		}

		//start the first div line for the character read.
		char tempDivLine[200];
		sprintf(tempDivLine,"<div style=\" position:absolute; left:%gpx; top:%gpx;\" class=\"class_%d\">",
		xCoord,yCoord , classNo);
		bodyString = tempDivLine;
		bodyString += specialC;
		bodyString += c;
		return;

	}

	//reads the textLocations.txt file line by line and forms new divs accordingly
	void parser::readText(){
		float xCoord,yCoord,width,space,fontSize;
		string fontType;
		char c;
		//read the next character in c
		c = fgetc(fpIn);
		
		//if file ends return
		if(c == EOF){  prevLetter.setLetter(EOF); terminateDiv(); hClass.closeFile(); return;}
		
		//if special multicharacter symbol, read the symbol in string specialC.
		string specialC = "";
		if((int)c < 0) {specialC += c; 
			while((int)(c = fgetc(fpIn)) < 0) specialC += c; 
			c = specialC[specialC.length()-1];
			specialC = specialC.substr(0 , specialC.length() -1);
		} 
		
		//read the attributes corresponding to the character read recently
		fscanf(fpIn," %f %f %f %f %f\n",&yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(fpIn);
		string family,style,weight;
		processFontType(fontType,family,style,weight);

		//set the next font object according to the information for the current character read
		nextFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
  
		if(yCoord == prevLetter.getYCoord()){
			//y coordinate of bothe the characters same, implies they are in teh same line

			if(checkWordContinuity(prevLetter.getXCoord(),xCoord,prevLetter.getLetterWidth())) {
				//both characters belong to the same word
				if((int)c < 0){bodyString += specialC;}
				bodyString += c;
				prevLetter.setLastLetter(c,xCoord,yCoord,width);
				readText();
			}

			//characters belong to different words on same line , check if they form continuous words of same line
			else{
				if(checkDivContinuity(prevLetter.getXCoord(),xCoord,prevLetter.getLetterWidth(),currentFont.getSpaceWidth())){
					
					//chaarcters belong to consecutive words of the same line. check if they have same font.
					if(nextFont == currentFont) {
						//the two characters have same font, add a space between them and add the two characters to the
						//same line of same div
						bodyString += " "; 
						if((int)c < 0){bodyString += specialC;}
						bodyString += c;
						prevLetter.setLastLetter(c,xCoord,yCoord,width);
						readText();
					}

					else{
						//the two characters have different font , terminate the last div and start a new div
						prevLetter.setLastLetter(c,xCoord,yCoord,width);
						currentFont = nextFont;
						terminateDiv();
						if((int)c < 0){bodyString += specialC;}
						bodyString += c;
						readText();
						
					}
				}
				else{
					//there is a gap of more than one space in between two characters. 
					//form a new div for the next character and terminate the last div
					prevLetter.setLastLetter(c,xCoord,yCoord,width);
					if(hClass.isPresent(nextFont) == -1){
						hClass.addClass(nextFont);
					}

					currentFont = nextFont;
					terminateDiv();
					
					
					if((int)c < 0){bodyString += specialC;}
					bodyString += c;
					readText();
				}
			}
		}
		else{	
			//the two characters have different y coordinates, terminate the last div and form the new div stroing
			//the last character read
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			if(hClass.isPresent(nextFont) == -1){
				hClass.addClass(nextFont);
			}

			currentFont = nextFont;
			terminateDiv();
			
			if((int)c < 0){bodyString += specialC;}
			bodyString += c;
			readText();
		}
		return;
	}		

	//chaeck the div continuity , by comparing the x coordinates of the last two characters. 
	//if gap between them is about one space , the div is continuous return true else retuurn false
   	bool parser::checkDivContinuity(double prevPos,double newPos,double width,double space){
   		if(abs(newPos - width - prevPos) <= 2*space){
   			return true;
   		}
   		else{
   			return false;
   		}	
   	}
	
	//chaeck the word continuitty by comparing the x coordinates of the two characters
	bool parser::checkWordContinuity(double prePos,double newPos,double width){
		if((newPos - width) - prePos <= 0.5){
			return true;
		}
		else{
			return false;
		}
	}

	//terminate the div strign formed uptil now and start a new div string corresponding to the last read character
	void parser::terminateDiv(){
		
		//add </div> to bodyString formed uptil now and write it to the file
		bodyString += "</div>\n";
		writeBodySyntax(bodyString);
		
		//check if the class for the last read chacter present in the head file formed yet
		int p = hClass.isPresent(currentFont);
		if(p == -1){
			p = hClass.addClass(currentFont);
		}
		
		//start a new div syntax
		char tempDivLine[150]; 
		sprintf(tempDivLine,"<div style=\"position:absolute;left:%gpx;top:%gpx;\" class=\"class_%d\">",
		prevLetter.getXCoord(), prevLetter.getYCoord(),p); bodyString +=
		tempDivLine; 
	
		if(prevLetter.getLetter() == EOF) { 
			fprintf(fpOut,"%s\n","\n</div>");
			fclose(fpOut); fclose(fpIn);}
		return;
	}

	//write the string formed to the output file
	void parser::writeBodySyntax(string & str){
		fprintf(fpOut , "%s\n" , str.c_str());
		str = "";
		return;
	}

	//process font string extracted from the pdf and recognize the font type , weight and style
	void parser::processFontType(string & fontType,string & fontFamily,string & style,string & weight){
		int i = 0 ;
		style = "";
		weight = "";
		while(i < fontType.length()){
			if(fontType[i] == '+'){fontFamily = ""; i++; continue;}
			if(fontType[i] == '-') break;
			fontFamily += fontType[i];
			i++;
		}
		if(i == fontType.length()){return;}
		i++;
		if(fontType[i] == 'b' && fontType[i+1] == 'o') {
			weight = "bold"; 
			i += 4;
			if(fontType[i] == 'i' && fontType[i+1] == 't'){
				style = "italics";
				return;
			}
			else return;
		}
		if(fontType[i] == 'i' && fontType[i+1] == 't'){
				style = "italics";
				return;
			}
	}

	//read the font string from the input file
	string parser::extractFont(FILE * fp){
		string str = "";
		char c = fgetc(fp);
		c = fgetc(fp);
		while(c!='\n'){
			
			str += c;
			c = fgetc(fp);
		}
		return str;
	}
