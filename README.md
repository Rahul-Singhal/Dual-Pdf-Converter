Dual-Pdf-Converter
==================

A Program written in JAVA and C++ to convert pdf files to their equivalent LaTeX Source Code or HTML Source Code.


CONTENTS OF DIFFERENT FOLDERS:
  1. src - contains java files and java class files after compilation of java code and also shell scripts to run the whole program.
  2. lib - contains .jar file of library used by java code.
  3. pdfData - conatins output of java files i.e. files that contain extracted text and images ( textLocations.txt, imageLocation.txt, images)
  4. tolatex - conatins c++ code files used for latex code generation
  5. tohtml - conatins c++ code files used for html code generation
  6. samplePdf - folder in which contins pdf files that has to be converted to .tex or .html format
  7. htmlOutput -  folder in which output which contains html code for input pdf i.e. final.html will be kept and also images which were present in the pdf
  8. LatexOutput -  folder in which output which contains Latex code for input pdf i.e. final.tex will be kept.
  9. Demo - contains pdf files which we will use for our demo
  
HOW TO RUN:
  1. Put the .pdf file that you want to canvert to .html or .tex in samplePdf folder.
  2. Open terminal and change directory to src folder.
  3. execute compile.sh script which will compile all java files and store them in src folder. (command - ./compile.sh)
  4. keep the directory same and execute run.sh script. ( command - ./run.sh)
  5. follow the steps asked by run.sh file. 
     
      NOTE: --type full file name including .pdf like "sample.pdf".
            --type one less page no. that you want to convert to .html/.pdf like
              if you want to convert pages from 4 to 10 ( starting page = 3, end page = 9).
            --type "latex" for .tex conversion and "html" for .html conversion.
  6. If you want to generate Latex code the output code will go to LatexOutput folder with name "final.tex".
  7. If you want to generate html code the output code will go to htmlOutput folder with name "final.html".
  
                      "THANKS FOR USING OUR PROGRAM , HOPE YOU ENJOYED WORKING WITH IT"               
