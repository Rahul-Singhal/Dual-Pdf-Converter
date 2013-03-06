

import org.apache.pdfbox.exceptions.InvalidPasswordException;


import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.pdmodel.PDPage;
import org.apache.pdfbox.pdmodel.common.PDStream;
import org.apache.pdfbox.pdmodel.edit.PDPageContentStream;
import org.apache.pdfbox.util.PDFTextStripper;
import org.apache.pdfbox.util.TextPosition;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import java.util.List;


public class PrintTextLocations extends PDFTextStripper
{
	
	
		/*private static FileWriter fstream = new FileWriter("locations.txt");
		private static BufferedWriter outp = new BufferedWriter(fstream);*/
		
		private static FileWriter fstream =null;
		private static BufferedWriter outp = null;
		private static int startPage = 0;
	    private static int endPage = 0;    
    
	
   
    public PrintTextLocations() throws IOException
    {
        super.setSortByPosition( true );
       
    }
    
    

    public void process( String fname, int sp , int ep) throws Exception
    {
            PDDocument document = null;
            fstream = new FileWriter("../pdfData/textLocations.txt");
            outp = new BufferedWriter(fstream);
            startPage = sp;
            endPage = ep;            	
            	
            try
            {
                document = PDDocument.load( fname );
                
                if( document.isEncrypted() )
                {
                    try
                    {
                        document.decrypt( "" );
                    }
                    catch( InvalidPasswordException e )
                    {
                        System.err.println( "Error: Document is encrypted with a password." );
                        System.exit( 1 );
                    }
                }
                PrintTextLocations printer = new PrintTextLocations();
                List allPages = document.getDocumentCatalog().getAllPages();
                
                
                PDPage page = (PDPage)allPages.get(0);
                outp.write(page.getMediaBox().getWidth() + " " + page.getMediaBox().getHeight() + "\n");
                for( int i=startPage; i<allPages.size() && i<=endPage; i++ )
                {
                    page = (PDPage)allPages.get( i );
                    
                    PDStream contents = page.getContents();
                    if( contents != null )
                    {
                        printer.processStream( page, page.findResources(), page.getContents().getStream() );
                    }
                }
                outp.close();
            }
            finally
            {
                if( document != null )
                {
                    document.close();
                    
                }
            }
        
    }


    protected void processTextPosition( TextPosition text ) 
    {
        try { 
        	
        	
        	//Xpos YPos Fsize FFamily
        	String str = text.getCharacter();
        	//char[] ch = str.
        	if(str.charAt(0) == 'f' && str.length() == 2){
        		outp.write( str.charAt(0) + " " + text.getYDirAdj() + " " +
    			        text.getXDirAdj() + " " + text.getFontSize() + " " + text.getWidthDirAdj()/2 + " " + text.getWidthOfSpace()
    					  + " " + text.getFont().getBaseFont() + "\n");
        		outp.write( str.charAt(1) + " " + text.getYDirAdj() + " " +
    			        (text.getXDirAdj() + text.getWidthDirAdj()/2) + " " + text.getFontSize() + " " + text.getWidthDirAdj()/2 + " " + text.getWidthOfSpace()
    					  + " " + text.getFont().getBaseFont() + "\n");
        	}
            else if(str.charAt(0) == 'f' && str.length() == 3){
                
                outp.write( str.charAt(0) + " " + text.getYDirAdj() + " " +
                        text.getXDirAdj() + " " + text.getFontSize() + " " + text.getWidthDirAdj()/3 + " " + text.getWidthOfSpace()
                          + " " + text.getFont().getBaseFont() + "\n");
                outp.write( str.charAt(1) + " " + text.getYDirAdj() + " " +
                        (text.getXDirAdj() + text.getWidthDirAdj()/3) + " " + text.getFontSize() + " " + text.getWidthDirAdj()/3 + " " + text.getWidthOfSpace()
                          + " " + text.getFont().getBaseFont() + "\n");
                outp.write( str.charAt(1) + " " + text.getYDirAdj() + " " +
                        (text.getXDirAdj() + 2*text.getWidthDirAdj()/3) + " " + text.getFontSize() + " " + text.getWidthDirAdj()/3 + " " + text.getWidthOfSpace()
                          + " " + text.getFont().getBaseFont() + "\n");
            }
        	else{//System.out.println(text.getCharacter());
			outp.write( text.getCharacter() + " " + text.getYDirAdj() + " " +
			        text.getXDirAdj() + " " + text.getFontSize() + " " + text.getWidthDirAdj() + " " + text.getWidthOfSpace()
					  + " " + text.getFont().getBaseFont() + "\n");
        	}
			
		} catch (IOException e) {
			System.out.println("Cannot write text to file");
			//e.printStackTrace();
		}
    }

    /**
     * This will print the usage for this document.
     */
    

}
