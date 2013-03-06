#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "parser.h"
#include "imageparser.h"
using namespace std;


int main(int argc , char*argv[]){

	string str = argv[1];
	int divNo = 0;

	for(int i = 0 ; i< str.length() ; i++){

		divNo = 10*divNo + (int)(str[i] - '0');

	}
	
	imageParser Img;
	Img.readImage(divNo);

	parser Txt(divNo);
	Txt.readText();
	return 0;
}