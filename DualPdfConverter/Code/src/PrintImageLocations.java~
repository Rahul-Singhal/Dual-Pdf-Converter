
import org.apache.pdfbox.cos.COSName;
import org.apache.pdfbox.cos.COSStream;
import org.apache.pdfbox.exceptions.InvalidPasswordException;
import org.apache.pdfbox.exceptions.WrappedIOException;

import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.pdmodel.PDPage;
import org.apache.pdfbox.pdmodel.PDResources;
import org.apache.pdfbox.pdmodel.graphics.PDGraphicsState;
import org.apache.pdfbox.pdmodel.graphics.xobject.PDXObject;
import org.apache.pdfbox.pdmodel.graphics.xobject.PDXObjectForm;
import org.apache.pdfbox.pdmodel.graphics.xobject.PDXObjectImage;
import org.apache.pdfbox.util.Matrix;
import org.apache.pdfbox.util.PDFOperator;
import org.apache.pdfbox.util.PDFStreamEngine;
import org.apache.pdfbox.util.ResourceLoader;

import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import java.util.List;
import java.util.Map;

public class PrintImageLocations extends PDFStreamEngine
{
    
    private static final String INVOKE_OPERATOR = "Do";
    private static int imgNo = 0;
    private static String fname = null;
    private static FileWriter fstream = null;
    private static BufferedWriter outp = null;
    private static int startPage = 0;
    private static int endPage = 0;
   
    
    public PrintImageLocations() throws IOException
    {
        super( ResourceLoader.loadProperties(
                "org/apache/pdfbox/resources/PDFTextStripper.properties", true ) );
    }


    public void process( String fname , int sp , int ep) throws Exception
    {

            PDDocument document = null;
            try
            {
                document = PDDocument.load( fname );
                clearDirectory(new File("../pdfData/images"));
                fstream = new FileWriter("../pdfData/imageLocations.txt");
        		outp = new BufferedWriter(fstream);
        		startPage = sp;
        		endPage = ep;
        		
          
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
                PrintImageLocations printer = new PrintImageLocations();
                List allPages = document.getDocumentCatalog().getAllPages();
                for( int i=startPage; i<allPages.size() && i<=endPage; i++ )
                {
                    PDPage page = (PDPage)allPages.get( i );
                    printer.processStream( page, page.findResources(), page.getContents().getStream() );
                }
            }
            finally
            {
                if( document != null )
                {
                    document.close();
                    outp.close();
                    changeImageExtensions(new File("../pdfData/images"));
                }
            }
        
    }
    
    public static void  clearDirectory(File folder){
    	File[] files = folder.listFiles();
        if(files!=null) {
            for(File f: files) {
                    f.delete();
                }
            }
    }
    
    public static void changeImageExtensions(File folder){
    	File[] files = folder.listFiles();
    	if(files!=null){
    		for(File f:files){
    			String str = f.getName();
    			
    			str = str.subSequence(0, str.indexOf('.')) + ".jpg";
    			str = "../pdfData/images/" + str;
    			File fp = new File(str);
    			f.renameTo(fp);
    		}
    	}
    }


    protected void processOperator( PDFOperator operator, List arguments ) throws IOException
    {
        String operation = operator.getOperation();
        if( INVOKE_OPERATOR.equals(operation) )
        {
            COSName objectName = (COSName)arguments.get( 0 );
            Map<String, PDXObject> xobjects = getResources().getXObjects();
            PDXObject xobject = (PDXObject)xobjects.get( objectName.getName() );
            if( xobject instanceof PDXObjectImage )
            {
                PDXObjectImage image = (PDXObjectImage)xobject;
                
                image.write2file("../pdfData/images/" + imgNo);
                imgNo++;
                PDPage page = getCurrentPage();
                int imageWidth = image.getWidth();
                int imageHeight = image.getHeight();
                double pageHeight = page.getMediaBox().getHeight();
                //System.out.println("*******************************************************************");
                //System.out.println("Found image [" + objectName.getName() + "]");
        
                Matrix ctmNew = getGraphicsState().getCurrentTransformationMatrix();
                float yScaling = ctmNew.getYScale();
                float angle = (float)Math.acos(ctmNew.getValue(0, 0)/ctmNew.getXScale());
                if (ctmNew.getValue(0, 1) < 0 && ctmNew.getValue(1, 0) > 0)
                {
                    angle = (-1)*angle;
                }
                ctmNew.setValue(2, 1, (float)(pageHeight - ctmNew.getYPosition() - Math.cos(angle)*yScaling));
                ctmNew.setValue(2, 0, (float)(ctmNew.getXPosition() - Math.sin(angle)*yScaling));
                // because of the moved 0,0-reference, we have to shear in the opposite direction
                ctmNew.setValue(0, 1, (-1)*ctmNew.getValue(0, 1));
                ctmNew.setValue(1, 0, (-1)*ctmNew.getValue(1, 0));
                AffineTransform ctmAT = ctmNew.createAffineTransform();
                ctmAT.scale(1f/imageWidth, 1f/imageHeight);

                outp.write((imgNo-1)  +" " + ctmNew.getXPosition() + " " + ctmNew.getYPosition()
                        + " " + ctmNew.getXScale()  + " " + ctmNew.getYScale() + "\n");
           
            }
            else if(xobject instanceof PDXObjectForm)
            {
                // save the graphics state
                getGraphicsStack().push( (PDGraphicsState)getGraphicsState().clone() );
                PDPage page = getCurrentPage();
                
                PDXObjectForm form = (PDXObjectForm)xobject;
                COSStream invoke = (COSStream)form.getCOSObject();
                PDResources pdResources = form.getResources();
                if(pdResources == null)
                {
                    pdResources = page.findResources();
                }

                
                Matrix matrix = form.getMatrix();
                if (matrix != null) 
                {
                    Matrix xobjectCTM = matrix.multiply( getGraphicsState().getCurrentTransformationMatrix());
                    getGraphicsState().setCurrentTransformationMatrix(xobjectCTM);
                }
                processSubStream( page, pdResources, invoke );
                
                // restore the graphics state
                setGraphicsState( (PDGraphicsState)getGraphicsStack().pop() );
            }
            
        }
        else
        {
            super.processOperator( operator, arguments );
        }
    }

    

}
