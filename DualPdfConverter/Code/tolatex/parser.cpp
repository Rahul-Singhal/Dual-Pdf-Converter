/*definitions for the methods of the class parser*/

#include "parser.h"
using namespace std;

  //constructor, read the first letter and handles the control to readText()
	parser::parser(string fileName){
		offset = 0;
		lineStartXCoord = -1;
		bulletPossiblity = false;
		pdfData = fopen(fileName.c_str() , "r");
		bodyString = "";
		float pageHeight;
    
    //read the page height and width from the top of pdfdata file
		fscanf(pdfData , "%f %f\n" , &pageWidth , &pageHeight);

		char c;
		c = fgetc(pdfData);
		
		//if negative character , it is a multicharacter symbol , read until you get a positive ascii value character
		if((int)c < 0) {bodyString += c; while((int)(c = fgetc(pdfData)) < 0) bodyString += c;
			c = bodyString[bodyString.length()-1];
			bodyString = bodyString.substr(0 , bodyString.length() -1);
		}
		
		//set the previous letter and the current font objects according to the letter details read
		float xCoord,yCoord,width,space,fontSize;
		string family,style,weight , fontType;
		fscanf(pdfData," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);

		fontType = extractFont(pdfData);
		processFontType(fontType,family,style,weight);
		currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
		prevLetter.setLastLetter(c,xCoord,yCoord,width);
		bodyString += c;
		lineStartXCoord = xCoord;
		
  
		if(bodyString == "•"){
		//it is a bullet , call start bullet from parser handler object and push the x coordinate of the starting of bullet in the stack and 
		//itemize in bulletType stack
				bulletStack.push(xCoord);
				bulletType.push("itemize");
				offset = xCoord - lineStartXCoord;
				pHandler.startBullet(0); //0 for items
				prevLetter.setLastLetter(c,xCoord,yCoord,width);
				bodyString = "";
				readText();
			}

		if(c == '('){
		//start enumeratiom of type (a) , (b)...., push the x coord in the bullet stack.
			bulletStack.push(xCoord);
			if(checkalphabeticBullet()){
				readText();
			}
			else{
		  //bullet check failed , pop the top element of the bulletStack , since bullet check has failed
				bulletStack.pop();
				readText();
			}
		}

		if(c == 'A'){
		//start enumeration of type A. , B., C.,.... in the same way as commented above
			bulletStack.push(xCoord);
			if(checkAlphabeticBullet()){
				readText();
			}
			else{
				bulletStack.pop();
				readText();
			}
		}

		if(c == 'i'){
		//start enumeration of type i. , j. , k. ... 
			bulletStack.push(xCoord);
			if(checkIJKBullet()){
				readText();
			}
			else{
				bulletStack.pop();
				readText();
			}
		}

		
  
		if(c > '9' || c < '0'){
				readText();
			}

			//bullet may start // implement the algo for bullet.

		else{
		//start enumeration of type 1. , 2. , 3. ....
			bulletStack.push(xCoord);
			bulletType.push("enumerate");
			if(!bulletORSection(bodyString)) {bulletStack.pop() ; bulletType.pop(); readText();}
		}
	}
	
	
  //check if there are alphabetic bullets like (a), (b)...
  //read the three characters and find if it is like "(X)" typewhere X is a small alphabet
	bool parser::checkalphabeticBullet(){
		char c;
		c = fgetc(pdfData);
		float xCoord,yCoord,width,space,fontSize;
		string family,style,weight , fontType;
		fscanf(pdfData," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(pdfData);

		if((c >= 'a' && c <= 'z')){
			bodyString += c;
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
  
      
			c = fgetc(pdfData);
			fscanf(pdfData," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);

			if(c != ')'){
				bodyString += c;
				prevLetter.setLastLetter(c,xCoord,yCoord,width);
				return false;
			}
			else{
					pHandler.startBullet(2);
					bulletType.push("alphabetic");
					bodyString = "";
					c = fgetc(pdfData);
					fscanf(pdfData," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);
					fontType = extractFont(pdfData);
					bodyString += c;
					prevLetter.setLastLetter(c,xCoord,yCoord,width);
					processFontType(fontType,family,style,weight);
					currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
					return true;
			}	

		}
		else{
			bodyString += c;
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			return false;
		}

	}
  //check if there are Alphabetic bullets like A,B...
  //read the first two characters and check if they are like "A." type for Alphabetic enumeration
	bool parser::checkAlphabeticBullet(){
		char c;
		c = fgetc(pdfData);
		float xCoord,yCoord,width,space,fontSize;
		string family,style,weight , fontType;
		fscanf(pdfData," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(pdfData);
		if(c == '.'){
			pHandler.startBullet(3);
			bulletType.push("Alphabetic");

			bodyString = "";
			c = fgetc(pdfData);
			fscanf(pdfData," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);
			bodyString += c;
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			processFontType(fontType,family,style,weight);
			currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
			return true;

		}
		else{
			bodyString += c;
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			return false;
		}
	}
	
	
  //check if bullets are of type i,j,k
  //read the first two characters from the pdf data and check if they are of type "i."
	bool parser::checkIJKBullet(){
		char c;
		c = fgetc(pdfData);
		float xCoord,yCoord,width,space,fontSize;
		string family,style,weight , fontType;
		fscanf(pdfData," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(pdfData);
		if(c == '.'){
			pHandler.startBullet(4);
			//yes it is a bullet , push "ijk" in bulletType stack
			//read the next character and set the previous letter and currentFont and continue readText()
			bulletType.push("ijk");

			bodyString = "";
			c = fgetc(pdfData);
			fscanf(pdfData," %f %f %f %f %f ",&yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);
			bodyString += c;
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			processFontType(fontType,family,style,weight);
			currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
			return true;

		}
		else{
			bodyString += c;
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			return false;
		}
	}
  //recursively reads the letters from the pdf data file and calls the corresponding method in parser handler class
	void parser::readText(){
		char c ;
		//get letter from the file
		c = fgetc(pdfData);
		
		//check for the end of file
		if(c == EOF){
			pHandler.processSimpleText(bodyString , currentFont);
			pHandler.writeToFile(getAlignment(prevLetter.getXCoord() , currentFont.getSpaceWidth()));
			pHandler.endFile(); 
			exit(0);
		}
		
		string specialC = "";
		//if the character has negative ascii value , it is a multicharacter symbol , read till next positive character
		if((int)c < 0) {specialC += c; 
			while((int)(c = fgetc(pdfData)) < 0) specialC += c; 
			c = specialC[specialC.length()-1];
			specialC = specialC.substr(0 , specialC.length() -1);
		}
		float xCoord,yCoord,width,space,fontSize;
		string family,style,weight , fontType;

		fscanf(pdfData," %f %f %f %f %f\n",&yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(pdfData);
		processFontType(fontType,family,style,weight);
		nextFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
		
		if(yCoord == prevLetter.getYCoord()){
		//the two character are in the same line
			if(checkWordContinuity(prevLetter.getXCoord(),xCoord,prevLetter.getLetterWidth())) {	
				//the two characters are of the same word , add to body string and continue reading
				if((int)c < 0){bodyString += specialC;}
				bodyString += c;
				prevLetter.setLastLetter(c,xCoord,yCoord,width);
				readText();
			}
			else {
			//the two letter are seperated by some distance but are on the same line , add spaces corresponding to the gap
				addSpaces((xCoord - prevLetter.getXCoord() - prevLetter.getLetterWidth())/currentFont.getSpaceWidth());
      //if fonts of both characters are same , add the character to the bodystring and continue reading
				if(currentFont == nextFont){
					if((int)c < 0){bodyString += specialC;}
					bodyString += c;
					prevLetter.setLastLetter(c,xCoord,yCoord,width);
					readText();
				}
				else{
			//different fonts , process the string formed uptil now and reinitialize the bodystring and continue reading
					pHandler.processSimpleText(bodyString , currentFont);
					bodyString = "";
					if((int)c < 0){bodyString += specialC;}
					bodyString += c;
					prevLetter.setLastLetter(c,xCoord,yCoord,width);
					currentFont = nextFont;
					readText();
				}
			}
		}
		else{
			pHandler.processSimpleText(bodyString , currentFont);
			// y coord has changed get alignment and write to the output latex file
			
			pHandler.writeToFile(getAlignment(prevLetter.getXCoord(),prevLetter.getLetterWidth()));
			if(abs(pageWidth/2 - xCoord) <= 2 * fontSize){
			//page number it is. skip
				bodyString = "";
				readText();
			}
			
			lineStartXCoord = xCoord;
			bodyString = "";
			if((int)c < 0){bodyString += specialC;}
			bodyString += c;
			bool bl;
			//check if some bullet object has terminated
			if(!bulletStack.empty()) { bl = checkBulletEnd(xCoord);}
			
			//add breaklines to the latex code corresponding to the gap between the two characters' y coordinate
			pHandler.breakLines((int)((yCoord - prevLetter.getYCoord())/(1.5*fontSize)));
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			currentFont = nextFont;
			
			if(bodyString == "•"){
			//start itemizing the text 	
				bulletStack.push(xCoord);
				bulletType.push("itemize");
				offset = xCoord - lineStartXCoord;
				pHandler.startBullet(0); //0 for items
				prevLetter.setLastLetter(c,xCoord,yCoord,width);
				bodyString = "";
				readText();
			}

			if(c == '('){
			//start enumerating the text as (a) , (b)...
				bulletStack.push(xCoord);
				if(checkalphabeticBullet()){
					readText();
				}
				else{
					bulletStack.pop();
					readText();
				}
			}

			if(c == 'A'){
			//start enumerating the text as A. B. ....
			bulletStack.push(xCoord);
			if(checkAlphabeticBullet()){
				readText();
			}
			else{
				bulletStack.pop();
				readText();
			}
		}

			if(c == 'i'){
			//start enumerating the text as i. j. k. .....
				bulletStack.push(xCoord);
				if(checkIJKBullet()){
					readText();
				}
				else{
					bulletStack.pop();
					readText();
				}

			}

			if(c > '9' || c < '0'){
				readText();
			}
			else{
			//start enumerating the text as 1. 2. 3. ....
				bulletStack.push(xCoord);
				bulletType.push("numeric");
				
				if(!bulletORSection(bodyString)) {bulletStack.pop() ; readText();}
			}


		}

	}
  //checks if the bullets have ended
  //if the x coordinate of the first character of this line is equal to that of top of the bulllet stack , start next bullet
  //if x coordinate  > top of bullet stack  , start a new bullet or section
  //if x coordinate < top of bullet stack , pop the top item from the bulletStack and bulletType , end that bullet and check for the next item in stack
	bool parser::checkBulletEnd(float x){
		
		while(!bulletStack.empty() && bulletStack.top() + 1.5 >= x){
		if(abs(x - bulletStack.top()) < 1.5)  {skipBulletText(); pHandler.nextBullet(); readText(); return true;}
		if(x < bulletStack.top()){  pHandler.endBullet(); bulletStack.pop(); bulletType.pop();}
		}
		return false;
	}

  
  //if there is a next bullet coresponding to the current bullet level , this methods skips the bullet text and calls the parser  
  //handler to create a next bullet
	void parser::skipBulletText(){
  
		if(bulletType.top() == "itemize") {bodyString = "" ; return;}
	  string family , style , weight;
		int i = 1;
		float xCoord,yCoord,width,space,fontSize;
		string fontType;
		char c;

		if(bulletType.top() == "alphabetic"){
		//skip the bullet text of type (a) , (b) , .... by reading the next three characters 		
			fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);
			fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);
			fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			processFontType(fontType , family , style , weight);
			currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
			bodyString = "";
			bodyString += c;
			return;

		}

		if(bulletType.top() == "ijk" || bulletType.top() == "Alphabetic"){
		//skip the bullet text of type i. j. k. and A. B. ....
			fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);
			fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			processFontType(fontType , family , style , weight);
			currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
			bodyString = "";
			bodyString += c;
			
			return;

		}

		fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(pdfData);

		prevLetter.setLastLetter(c,xCoord,yCoord,width);
		fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(pdfData);
		
		while(xCoord < (prevLetter.getXCoord() + currentFont.getSpaceWidth() + prevLetter.getLetterWidth()) && c != ' '){
			
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
			fontType = extractFont(pdfData);
		}
		bodyString = "";
		bodyString += c;
		prevLetter.setLastLetter(c,xCoord,yCoord,width);
		processFontType(fontType , family , style , weight);
		currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");


	}

  //gets alignment of the line by finding the x coordinate of mid point of the line and compares it with the 
	//mid point of the page
	string parser::getAlignment(float x , float letterWidth){
		
		if((x + letterWidth + lineStartXCoord)/2 < 
				(pageWidth/2 + offset) - currentFont.getSpaceWidth()/2){
				//left alignment
				return("left");
			}
			else if((x + letterWidth + lineStartXCoord)/2 > (pageWidth/2 + offset) + currentFont.getSpaceWidth()/2){
				//right alignment
				return("right");
			}
			else return("center");
	}
	
	
  //check if there is a bullet or section
  //if it is a bullet it wil be of type 1.2.3. , 1. , 1.2.3.4. but there will always be a '.' at the end
  //if it is a section it will be of type 1.2 , 1 , 1.3.4 etc , there will not be any '.' at the end
	bool parser::bulletORSection(string & str){
		char c;
		int i = 1;
		float xCoord,yCoord,width,space,fontSize;
		string fontType;
		fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);
		fontType = extractFont(pdfData);

		while(xCoord < (prevLetter.getXCoord() + currentFont.getSpaceWidth() + prevLetter.getLetterWidth()) && c != ' '){
			if(yCoord == prevLetter.getYCoord()){
			bodyString += c;
			if(i%2 == 1 && c != '.'){
				return false;
			}
			if(i%2 == 0 && (c < '0' || c > '9')){
				return false;
			}
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			fscanf(pdfData,"%c %f %f %f %f %f ",&c , &yCoord,&xCoord,&fontSize,&width,&space);	
			fontType = extractFont(pdfData);
		}
		else{
			pHandler.processSimpleText(bodyString , nextFont);
			string family , style , weight;
			processFontType(fontType , family , style , weight);
			currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
			pHandler.processSimpleText(bodyString , currentFont);
			pHandler.writeToFile(getAlignment(prevLetter.getXCoord() , currentFont.getSpaceWidth()));
			bodyString = "";
			bodyString += c;
			return false;

		}
		i++;
		}
		string family , style , weight;
		processFontType(fontType , family , style , weight);
		currentFont.set(space,family,fontSize,weight,style,"rgb(0,0,0)");
		bodyString = "";
		bodyString += c;
		if(prevLetter.getLetter() == '.'){
		//it is a bullet, keep the starting x coord in bullet stack
		//lineStartXCoord = xCoord;
			offset = xCoord - lineStartXCoord;
			pHandler.startBullet(1); //0 for items
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			readText();
			return true;
		}
		else {
			//it is a new section
			bulletStack.pop();
			bulletType.pop();
			//start the new section
			pHandler.startSection((i-1)/2);
			prevLetter.setLastLetter(c,xCoord,yCoord,width);
			readText();
			return true;
		}

	}

  //add spaces according to the gap between the words
	void parser::addSpaces(float n){
		int numSpaces;
		if(n > 0.7 && n <= 1) numSpaces = 1;
		else numSpaces = floor(n);
		for(int i = 0 ; i < numSpaces ; i++) bodyString += ' ';
	}

  //process font string and get style , weight and family
	void parser::processFontType(string & fontType,string & fontFamily,string & style,string & weight){
		int i = 0 ;
		style = ""; weight = "";
		while(i < fontType.length()){
			if(fontType[i] == '+'){fontFamily = ""; i++; continue;}
			if(fontType[i] == '-') break;
			fontFamily += fontType[i];
			i++;
		}
		if(fontFamily == "CMBX10" || fontFamily == "CMBX12"){
			weight = "bold";
		}
		else if(fontFamily == "CMTI10"){
			style = "italics";
		}
		if(i == fontType.length()){return;}
		i++;
		if((fontType[i] == 'b'|| fontType[i] == 'B') && fontType[i+1] == 'o') {
			weight = "bold"; 
			i += 4;
			if((fontType[i] == 'i' || fontType[i] == 'I') && fontType[i+1] == 't'){
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

  //reads font string from the file
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
	 //check if the word is continuos
	bool parser::checkWordContinuity(double prePos,double newPos,double width){
		if(abs((newPos - width) - prePos) <= 0.5){
			return true;
		}
		else{
			return false;
		}
	}
