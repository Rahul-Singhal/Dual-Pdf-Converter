echo "Type the file name you want to convert to HTML/PDF"

read filename

echo "type starting and end page no."

read x
read y

echo "type the format(html/latex) that you want to convert to :"

cp="-classpath .:../lib/pdfbox-app-1.7.1.jar"

read format

if test "$format" = "latex"
then
	cd ../tolatex
	g++ parserHandler.h -std=c++0x
	g++ -o latexBody parser.cpp main.cpp -std=c++0x
	g++ -o finalize finalize.cpp -std=c++0x
	cd ../src
	while [ $x -le $y ]
	do	
		java $cp ExtractTextAndImage ../samplePdf/"$filename" "$x" "$x"
		cd ..
		cp pdfData/textLocations.txt tolatex/
		cd tolatex
		./latexBody
		x=$(( $x + 1 ))
		cd ../src
	done
	cd ../tolatex
	./finalize
	rm output.tex
	rm textLocations.txt
	mv final.tex ../LatexOutput
		
else
  cd ..
  cd htmlOutput
  rm final.html
  rm -r images
	cd .. 
	cd tohtml
	rm textLocations.txt
	rm imageLocations.txt
	rm head.txt
	rm body.txt
	i=0
	cd ..
  	cd pdfData
	rm -r images
	mkdir images
	cd ../tohtml
	mkdir images
	g++ -o combine combine.cpp
	g++ -o tohtml parser.cpp main1.cpp
	while [ $x -le $y ]
	do
  		cd ../src
  		java $cp ExtractTextAndImage ../samplePdf/"$filename" "$x" "$x"
  		cd ..
  		cp pdfData/textLocations.txt tohtml/
  		cp pdfData/imageLocations.txt tohtml/
  		cd tohtml
  		./tohtml "$i"
  		cd ../pdfData/images
  		j=0
  		s=$(ls)
  		if test "$s" = ""
  		then 
  			echo "No image for this page"
		else	
			for file in *.jpg
			do
	  			mv "$file" ../../tohtml/images/"$i-$j.jpg"
				j=$(( $j + 1 ))
			done
		fi
  		cd ..
  		i=$(( $i + 1 ))
  		x=$(( $x + 1 ))
	done
	cd ../tohtml
	./combine
	mv  images ../htmlOutput
	mv final.html ../htmlOutput	
fi

