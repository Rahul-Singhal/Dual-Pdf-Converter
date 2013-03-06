/*writes the syntax for the images of that page inside div in the body of the html file*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

class imageParser{
private:
	ifstream fpIn;
 	FILE* fpOut;
 	//int div;	
	
public:
	
	imageParser(){
		fpIn.open("imageLocations.txt");
		fpOut = fopen("body.txt","a");
		
	}
	void readImage(int divNo){
		int num = 0;
		float xWidth,yWidth;
		FILE * fpInT;

		//firstly read the page width and height from the first line of textLocations extracted using java code
		//and initialize a div of this height and width
		fpInT = fopen("textLocations.txt" , "r");
		fscanf(fpInT,"%f %f",&xWidth,&yWidth);
		fprintf(fpOut,"<div id = \"div_%d\" style='position:absolute;left:50%c;margin-left:-%fpx;top:%fpx;width:%fpx;height:%fpx;border-style:outset;overflow:hidden'>\n",divNo , '%',
			xWidth/2,divNo*(yWidth + 10),xWidth,yWidth);
		fclose(fpInT);

		//now open the file containing the image locations , their name , width and height extracted using java code
		//read the image info one by one and add the corresponding syntax to the body.txt file
		if(fpIn.is_open()){
			string line;
			while(fpIn.good()){
				//image line read in the string line
				getline(fpIn,line);
				int num;
				float xCoord,yCoord,width,height;
				sscanf(line.c_str(),"%d %f %f %f %f\n" ,&num,&xCoord,&yCoord,&width,&height);
				//print the corresponding syntax in body.txt file.
				fprintf( fpOut,"<img src='images/%d-%d.jpg' style = 'position:absolute;left:%fpx;top:%fpx' width='%f' height='%f'>\n",divNo,
				num,xCoord,yCoord,width,height);
			}
		}
		fpIn.close();
		fclose(fpOut);
		return;
	}

};
