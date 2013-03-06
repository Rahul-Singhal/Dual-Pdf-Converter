#ifndef FONT_H
#define FONT_H

#include<string>
using namespace std;

class font{
	double spaceWidth;
	string family;
	double size;
	string color;
	string weight;
	string style;

public:

	font(){
		spaceWidth = 0;
		family = "";
		size = 0;
		weight = "";
		style = "";
		color = "";
	}

	font(double spW , string fam , double sz , string wt , string sty , string clr){
		spaceWidth = spW;
		family = fam;
		size = sz;
		weight = wt;
		style = sty;
		color = clr;
	}

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
		//cout<<size<<"meowww"<<endl;
	}

	bool operator<(const font & f1) const{
		return (spaceWidth < f1.getSpaceWidth());
	}

	bool operator==(const font & f1) const{
		return(spaceWidth == f1.getSpaceWidth() && family == f1.getFamily() && size == f1.getSize() 
			&& weight == f1.getWeight() && style == f1.getStyle() && color == f1.getColor());
	}
};

#endif
