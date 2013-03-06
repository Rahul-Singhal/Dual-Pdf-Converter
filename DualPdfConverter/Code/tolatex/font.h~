/*class containing the font details of the characters that are being read from the extracted pdf data.*/

#ifndef FONT_H
#define FONT_H

#include<string>
using namespace std;

class font{
	double spaceWidth;        //width of the space character according to the font
	string family;            //font family like , Arial , Times New Roman etc
	double size;              //font size
	string color;             //font color
	string weight;            //font weight
	string style;             //font style

public:

  //constructor
	font(){
		spaceWidth = 0;
		family = "";
		size = 0;
		weight = "";
		style = "";
		color = "";
	}
  //constructor with parameters
	font(double spW , string fam , double sz , string wt , string sty , string clr){
		spaceWidth = spW;
		family = fam;
		size = sz;
		weight = wt;
		style = sty;
		color = clr;
	}

  //get and set methods
	double getSpaceWidth() const{
		return spaceWidth;
	}

	string getFamily() const{
		return family;
	}

	double getSize() const{
		return size;
	}

	string getWeight() const{
		return weight;
	}

	string getStyle() const{
		return style;
	}

	string getColor() const{
		return color;
	}

	void set(double spW , string fam , double sz , string wt , string sty , string clr){

		spaceWidth = spW;
		family = fam;
		size = sz;
		weight = wt;
		style = sty;
		color = clr;
	}

  //operators < and == being overloaded. < overloaded to enable inserting as key in stl maps used later
	bool operator<(const font & f1) const{
		return (spaceWidth < f1.getSpaceWidth());
	}

	bool operator==(const font & f1) const{
		return(spaceWidth == f1.getSpaceWidth() && family == f1.getFamily() && size == f1.getSize() 
			&& weight == f1.getWeight() && style == f1.getStyle() && color == f1.getColor());
	}
};

#endif
