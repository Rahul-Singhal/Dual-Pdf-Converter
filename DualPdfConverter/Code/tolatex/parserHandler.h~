#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<stack>
#include<unordered_map>
#include"font.h"

using namespace std;

class parserHandler{
	FILE* fpOut; //final output file in which we write latex code with proper syntax 
	string str;  //contains current string which has come as input from parser.cpp with latex syntax added to it 
	int bullet;  //contains no. of bullets that are currently being written ( ex stores 2 if two levels of bullets are being written currently
	int bulletType; //contains type of bullet 0 -> spherical bullet(itemize), 1-> arabic(1.,2.,..), 2-> small case alph((a),(b)..),3->big case alph(A.,B.,..)
	                //4->roman((i),(ii),(iii)...) 
	unordered_map<string,string> specialChar;//stores latex representation of special and math characters
	unordered_map<string,string> greekChar; //stores latex representation of greek characters
	bool section;   //becomes true if a section is added so that at the end of section '}' 
	stack<string> sectionBegin; //stores latex syntax that has to be added at beginning of section. 
	string prevAlign;   //stores prevAlign( left, right, center) so that if alignment changes then proper latex syntax can be added
	stack<string> bulletStack;  //stores latex syntax that has to be added at the end of bullet after all bullets has been processed. 
	stack<string> bulletBeginStack; //stores latex syntax that has to be added at the beginning of bullets.
	string greekCharString;   //helps in checking whether a greek char is present in the map that has been used or not
	bool greekCharContinue;   //helps in storing char in greekCharString,needed because every greek char consits of either 3 or 2 chars( with negative ascii), 
	font prevFont;            //stores prevFont that has been used for text 
	bool enterAfterSection;   //becomes true when section syntax has been added but '}' isn't added after section, helps in ignoring breakline ( "\\") just
	                          //after section
public:

	parserHandler(){
		
		fpOut = fopen("output.tex","a");
		string str = "\\begin{flushleft}\n"; //sets default alignment to left
		fprintf(fpOut , "%s" , str.c_str());
		str = "";
		bullet = 0;
		//map for special characters and math characters
		unordered_map<string,string> s{{"{","\\{"},{"<","$<$"},{">","$>$"},{"}","\\}"},{"_","\\_"},{"@","\\textasciicircum @"},{"$","\\$"},{"&","\\&"},{"\\","$\\backslash$"},{"~","\\textasciitilde"},{"\%","\\%"}};
		specialChar = s;
		//map for greek characters
		unordered_map<string,string> g{{"α", "$\\alpha$"},{"η", "$\\eta$"},{"ν", "$\\nu$"},{"τ", "$\\tau$"},
									{"β", "$\\beta$"},{"θ", "$\\theta$"},{"ξ","$\\xi$"},{"υ", "$\\upsilon$"},
									{"γ", "$\\gamma$"},{"ι","$\\iota$"},{"φ" ,"$\\phi$"},{"δ","$\\delta$"},
									{"κ","$\\kappa$"},{"π","$\\pi$"},{"χ","$\\chi$"},{"ε","$\\epsilon$"},
									{"λ","$\\lambda$"},{"ρ" ,"$\\rho$"},{"ψ", "$\\psi$"},{"ζ","$\\zeta$"},
									{"µ","$\\mu$"},{"σ","$\\sigma$"},{"ω","$\\omega$"},{"∆","$\\Delta$"},
									{"Θ","$\\Theta$"},{"Γ","$\\Gamma$"},{"Υ","$\\Upsilon$"},{"Λ","$\\Lambda$"},
									{"Ξ","$\\Xi$"},{"Ω","$\\Omega$"},{"Φ","$\\Phi$"},{"ℵ","$\\aleph$"},
									{"Π","$\\Pi$"},{"i","$\\beth$"},{"Ψ","$\\Psi$"},{"k","$\\daleth$"},
									{"Σ","$\\Sigma$"},{"ג","$\\gimel$"},{"≤","$\\leq$"},{"≥","$\\geq$"},
									{"≡","$\\equiv$"},{"≺","$\\prec$"},{"∼","$\\sim$"},{"'","$\\simeq$"},
									{"⊃","\\supset"},{"≈","$\\approx$"},{"./","$\\bowtie$"},{"⊆","\\subseteq"},
									{"⊇","\\supseteq"},{"^","$\\smile$"},{"∈","$\\in$"},{"∞","$\\infty$"}};

		greekChar = g;
		prevAlign = "";
		section = false;
		enterAfterSection =false;
		greekCharContinue = false;
		greekCharString = "";
	}


	void setPageLayout(float width,float height){
		fprintf(fpOut,"\\usepackage[ paperwidth=%fpx, paperheight=%fpx]{geometry}\n",width,height); 
	}

	void endFile(){
		if(str.length() > 0)fprintf(fpOut, "%s",str.c_str());
		
		//if(bulletStack.empty()) fprintf(fpOut, "%s","\\\\}\n");
		while(!bulletStack.empty()){
			fprintf(fpOut , "%s" , bulletStack.top().c_str());
			bulletStack.pop();
		}
		if(bullet==0) fprintf(fpOut, "%s","}\n");
		//fprintf(fpOut, "%s\n","\\end{flushleft}\n\\end{document}" );
		fprintf(fpOut, "%s\n","\\end{flushleft}\n\\newpage" );
		fclose(fpOut);
		return;
	}

	void writeToFile(string align){
		
		if(str != ""){
			
			if(bullet > 0){//sets align to left if a bullet is on ( all bullets are assumed to be left aligned)
				align = "left";
			}
			
			if(align != prevAlign){
				if(prevAlign != ""){
					
					fprintf(fpOut,"%s\n","}");//ending the scope of previous alignment if alignment is changed.
				}

				prevAlign = align;
				string str1,str2,str3;
				str1 = "{\n\\" ;
				//str3 = "\\end";
				if(align == "center"){
					str2 = "centering\n"; 
				}
				else if(align == "left"){
					//str2 = "raggedright\n";
					str2= "";
					str1 = "{\n";
				}
				else{
					str2 = "raggedleft\n";
				}
				fprintf(fpOut, "%s%s",str1.c_str(),str2.c_str() );//writes syntax for new alignment
				while(!sectionBegin.empty()){//writes syntax for start of section
					fprintf(fpOut,"%s",sectionBegin.top().c_str());
					sectionBegin.pop();
					enterAfterSection = true;
				}
				while(!bulletBeginStack.empty()){//writes syntax for start of bullet
					fprintf(fpOut , "%s" , bulletBeginStack.top().c_str());
					bulletBeginStack.pop();
				}
				fprintf(fpOut, "%s",str.c_str() );//writes the current string after insertion of proper syntax 
				if(!section) fprintf(fpOut, "%s","\n");
				str = "";
				//fprintf(fpOut, "%s%s",str3.c_str(),str2.c_str());
			}
			else{
				while(!sectionBegin.empty()){ //writes syntax for start of section
					fprintf(fpOut,"%s",sectionBegin.top().c_str());
					sectionBegin.pop();
					enterAfterSection = true;
				}
				while(!bulletBeginStack.empty()){  //writes syntax for start of bullet
					fprintf(fpOut , "%s" , bulletBeginStack.top().c_str());
					bulletBeginStack.pop();
				}
				fprintf(fpOut,"%s",str.c_str());   //writes the current string after insertion of proper syntax 
				if(!section) fprintf(fpOut, "%s","\n");
				str = "";//empties string so that new string can be stored in processSimpleText
			}
			/*if(section){
				fprintf(fpOut, "%s","}\n");
				section = false;
			}*/
		}
		return;
	}

	void processSimpleText(string s,font f){
		if(enterAfterSection){ //helps in checking if a section has ended so that breakline can be ignored if section is continued
			enterAfterSection = false;
			fprintf(fpOut, "%s","}\n");
			section = false;
		}
		
		char prevchar;
		
		if(s == "") return;
		prevchar = s[0];
		if(!(section)){//checks for if font is "bold" or "italics" so that proper synatx can be added before the text to be bolded or italicised 
			
			if(f.getWeight() == "bold"){
				str += "\\textbf{";	
			}
			if(f.getStyle() == "italics"){
				str += "\\textit{";
			}
		}
		unordered_map<string,string>::iterator itr;
		for(int i=0;i<=s.length();i++){
			
			string str1 = "";
			string specialCharString = "";//string that helps in checking for math and special characters in the specialChar map
			specialCharString += s[i];
			itr = specialChar.find(specialCharString);
			if(itr != specialChar.end()){
				
				str += itr->second;
				
				prevchar = s[i];
			}
			else if((int)s[i] < 0){ //stores the char(having negative ascii) so that at the end of negative chars the formed string can be looked up in greekChar map
				
				greekCharString += s[i];//it is assumed that no two greek char can be contnuous
				
				greekCharContinue = true;
				prevchar = s[i];
			}
			else if((int)s[i]>=0 && greekCharContinue){
				
				greekCharContinue = false;
				itr = greekChar.find(greekCharString);//looks for greekCharString in greekChar map 
				if(itr != greekChar.end()){

					str += itr->second;
				}
				
				if(s[i]>0){ str += s[i];}
				prevchar = s[i];
				greekCharString = "";
			}
			else if(s[i] == '\n'){
				str += "\\\\"; // "\\" to break the line in latex
			}
			else if(s[i] == ' ' && prevchar == ' '){
				str = str.substr(0, str.length()-1);
				str += "\\space ";
				prevchar = ' ';
			}
			else if(s[i]>0){
				
				str += s[i];
				prevchar = s[i];
			}
		}
		if(!(section)){//checks for if font is "bold" or "italics" so that its scope can be ended 
			if(f.getWeight() == "bold"){
				str += "}";	
			}
			if(f.getStyle() == "italics"){
				str += "}";
			}
		}
		prevFont = f;
		/*if(bullet == 0){
			str += "\\\\";
		}*/
	}


	void startBullet(int i){
		// 0 for itemize , 1 for numbering , 2 for a,b,c and 3 for A,B,C
		
		//adds latex syntax needed to start bullet 
		bulletType = i;
		string str1;
		if(i > 0){
			if(bullet == 0) str1 = "}\n";
			str1 += "\\begin{enumerate}";
			string str2 ;
			switch(i){ //to decide which type of bullet is it and then adds syntax according to it
				case 1: {str2 = "[label = \\arabic*.]";
						break;}
				case 2: {str2 = "[label = (\\alph*)]";
						break;}
				case 3: {str2 = "[label = \\Alph*.]";
						break;}
				case 4: {str2 = "[label = (\\roman*)]";
						break;}
				default: {str2 = "";
						break;}
			}
			string str3 = "{\n\\item\n";
			//fprintf(fpOut, "%s",str1.c_str());
			string str4 = str1 + str2;
			str4 += str3;
			bulletBeginStack.push(str4);
			bulletStack.push("}\\end{enumerate}\n");
		}
		else{
			if( bullet == 0) str1 = "}\n";
			str1 += "\\begin{itemize}{\n\\item\n";
			//fprintf(fpOut, "%s",str1.c_str() );	
			bulletBeginStack.push(str1);
			bulletStack.push("}\\end{itemize}\n");
		}
		bullet++;
		return;
	}

	void nextBullet(){//adds syntax for next bullet
		
		fprintf(fpOut, "%s\n","\\item" );
	}

	void endBullet(){ // adds syntax to end bullets
		/*if(bullet){
			if(bulletType == 1){
				string str1 = "\\end{enumerate}\n";
				fprintf(fpOut, "%s",str1.c_str() );
			}
			else{
				string str1 = "\\end{itemize}\n";
				fprintf(fpOut, "%s",str1.c_str() );	
			}
			return;
		}
		else{
			return ;
		}*/
		bullet--;
		if( bullet == 0) prevAlign ="" ;
		fprintf(fpOut , "%s" , bulletStack.top().c_str());
		bulletStack.pop();
	}
	
void breakLines(int num_lines){ //adds syntax to leave vertical space i.e. if a line is ended or if there is gap of 2 or more lines
	if(enterAfterSection){
		
		//enterAfterSection = false;
		return ;
	}
	
	if(num_lines <= 1) {fprintf(fpOut , "\\\\ "); return;}
	char str1[100];
	if(num_lines>1){
		fprintf(fpOut ,"\\vspace{%dem}",1);
		fprintf(fpOut , "\\\\ ");
	}
	//for(int i = 1 ; i <= num_lines; i++){
		
	//}
}

void startSection(int i){//adds syntax for starting of section
	
	string tempStr = "";
	while((i--)>0){
		tempStr += "sub";
	}
	tempStr += "section";
	//fprintf(fpOut, "\\%s{",tempStr.c_str());
	tempStr = "\\" + tempStr;
	tempStr += "{";
	
	sectionBegin.push(tempStr);
	section = true;
}

};
