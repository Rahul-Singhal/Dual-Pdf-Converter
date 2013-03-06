/*a class which store the information about the last 
character read by the parser*/

#ifndef LAST_LETTER_H
#define LAST_LETTER_H


class lastLetter{

	char letter;
	double xCoord;
	double yCoord;
	double letterWidth;

public:

	void setLastLetter(char let , double X , double Y , double W){
		letter = let;
		xCoord = X;
		yCoord = Y;
		letterWidth = W;
	}

	char getLetter(){
		return letter;
	}

	double getXCoord(){
		return xCoord;
	}

	double getYCoord(){
		return yCoord;
	}

	double getLetterWidth(){
		return letterWidth;
	}

	void setLetter(char c){
		letter = c;
	}

};

#endif
