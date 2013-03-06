/*contains main code to combine the top and bottom formal syntax of latex to the latex 
file output.tex which contains latex code without this syntax and write the final processed file in final.tex.
this file reads output.tex line by line and also processes the string once again to remove some errors which 
got into this latex code and could not be removed during parsing.

the errors were:

{\item 
\\this is an item
}

{\raggedleft
\\text
}

{\centering
\\text
}

{
\\text
}

and 

syntax like "\\ \\ \\ \\ \\ ...."
*/

#include"parser.h"
#include<string>
#include <fstream>
#include <iostream>
using namespace std;

int main(){
	ofstream fileout;
	ifstream filein;

	filein.open("output.tex");
	fileout.open ("final.tex");
	
	//add the top syntax to final.tex
	string str = "";
	str += "\\documentclass[a4paper,11pt]{article}\n\\usepackage{ulem}\n\\usepackage{a4wide}\n\\usepackage{enumitem}\n";
	str += "\\usepackage[dvipsnames,svgnames]{xcolor}\n\\usepackage[pdftex]{graphicx}\n\\newcommand{\\tab}{\\hspace*{1em}}\n";
	str += "\\begin{document}\n";
	fileout << str;
	string line;
	
	//now read the file output.tex line by line , check for errors and write the processed line to final.tex i.e the finalized output of latex converter
	
	if(filein.is_open()){
		while(filein.good()){
			getline(filein,line);
			line += '\n';
			if(line == "\\\\ {\n"){
				fileout << "{\n";
				continue;
			}

			if(line == "\\item\n" || line == "\\raggedleft\n" || line == "\\centering\n"||line== "{\n"){
				fileout << line;
				getline(filein,line);
				line += '\n';
				if(line[0] == '\\' && line[1] == '\\'){
					line = line.substr(2,line.length() - 2);
					fileout << line;
				}
				else{
					fileout <<line;
				}	
			}
			else if(line.substr(0,5) == "\\\\ \\\\"){
				int i= 0;
				while(line[i]=='\\' || line[i] == ' '){
					i++;
				}
				line = line.substr(i , line.length()-i);
				fileout  << line;
			}
			else{
				fileout << line;
			}
		}	
	}
	filein.close();
	line = "\\end{document}";
	fileout << line;
	fileout.close();
	return 0;
}


