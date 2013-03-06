	// startPage EndPage password filename
//sample args[]  = -startPage <pageNumber> -endPage<pageNumber> -password<Password> filename

public class ExtractTextAndImage{
	
	/*private static final String PASSWORD = "-password";
	private static final String STARTPAGE = "-startPage";
	private static final String ENDPAGE = "-endPage";
	private static final String CONSOLE = "-console";
			
	
	public static void main(String[] args){
		String password = "";
		String startPage = "1";
		String endPage = "";
		String toConsole = "false";
		String pdfFile = null;
        String outputFile = null;
        
		for( int i=0; i<args.length; i++ )
        {
            if( args[i].equals( PASSWORD ) )
            {
                i++;
                if( i >= args.length )
                {
                    errorMessage();
                }
                password = args[i];
            }
            else if( args[i].equals( STARTPAGE ) )
            {
                i++;
                if( i >= args.length )
                {
                    errorMessage();
                }
                startPage = args[i];
            }
            else if( args[i].equals( ENDPAGE ) )
            {
                i++;
                if( i >= args.length )
                {
                    errorMessage();
                }
                endPage = args[i];
            }
            else if( args[i].equals( CONSOLE ) )
            {
                toConsole = "true";
            }
            else
            {
                if( pdfFile == null )
                {
                    pdfFile = args[i];
                }
                else
                {
                    outputFile = args[i];
                }
            }
        }
		
        String[] textExtractorArgs = {password , toConsole , startPage , endPage , pdfFile , outputFile}; 
        String[] imageExtractorArgs = {password , startPage , endPage , pdfFile};
		ExtractImages imageExtractor = new ExtractImages(imageExtractorArgs);
		ExtractText textExtractor = new ExtractText(textExtractorArgs);
		}
	

    private static void errorMessage(){
        System.err.println( "wrong parameters passed!! Error!!\n" +
            "ExtractText(String[] {\"-password\" \"XYZ\" \"-console\" \"-startPage\" \"i\" \"-endPage\" \"j\" \"ABC.pdf\" \"out.txt})");
        System.exit( 1 );
    }*/
	
	public static void main(String[] args){
		System.out.println(args[0] + " " + args[1] + " " + args[2]);
		try{
			PrintImageLocations pil = new PrintImageLocations();
			pil.process(args[0],Integer.parseInt(args[1]) , Integer.parseInt(args[2]));
			PrintTextLocations ptl = new PrintTextLocations();
			ptl.process(args[0],Integer.parseInt(args[1]) , Integer.parseInt(args[2]));
			
		}
		catch(Exception e){
			e.printStackTrace();
			System.out.println("Cannot process file");
		}		
	}
	}

	
	
	