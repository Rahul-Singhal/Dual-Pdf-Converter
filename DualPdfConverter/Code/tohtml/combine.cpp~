#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "parser.h"
#include "imageparser.h"

int main(){

	/*this code opens the two files body.txt containing the body of the html output file and head.txt containing the
	head syntax of the output html file , adds top meta , html , style tags to the final file named 
	final.html, adds the data from the two opened files to this final.html and thus forms the final output, i.e final.html*/
	FILE* fpIn1;
	FILE* fpIn2;
	FILE* fpIn3;
	FILE* fpOut;


	fpIn1 = fopen("head.txt","r");
	fpIn2 = fopen("body.txt","r");
	fpOut = fopen("final.html","a");

	//html and meta tags being added
	string head = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>\n\n<style type='text/css'><!--\n" ;
	fprintf(fpOut,"%s\n",head.c_str());
	char c ;
	
	//data from head.txt being copies inside style tag of final.html
	c = fgetc(fpIn1);
	while(c != EOF){
		fputc(c,fpOut);
		c = fgetc(fpIn1);
	}
	fclose(fpIn1);

	string style = "--></style>\n<style type='text/css'></style><script>window[\"_GOOG_TRANS_EXT_VER\"] = '1';</script></head>\n\n<body>\n";
	
	//head.txt copied. now copy body.txt inside body tags
	fprintf(fpOut,"%s\n",style.c_str());
	c = fgetc(fpIn2);
	while(!feof(fpIn2)){
		
		fputc(c,fpOut);
		c = fgetc(fpIn2);
	}
	fclose(fpIn2);
	fprintf(fpOut,"%s\n","\n</body>");
	fclose(fpOut);
	return 0;
}
