public void charger(String path) {
	try {
		System.setOut(new PrintStream(new FileOutputStream("fichier.arff")));
	} catch (FileNotFoundException e) {
		e.printStackTrace();
	}
	System.out.println("@relation yolo_SWAG");
	System.out.println("");
	System.out.println("@attribute document_name string");
	System.out.println("@attribute document_content string");
	System.out.println("@attribute document_class string [A,St,Sp]");
	System.out.println("@data");
	System.out.println("");
	File repertoire = new File("/home/cedric/Dropbox/Public/M1_DECOL/S8/EC/projet/corpus");
	String [] listefichiersTemp,listefichiers;
	listefichiersTemp=repertoire.list();
	listefichiers = new String[listefichiersTemp.length];
// On recup les noms de fichiers
	for(int i=0;i<listefichiersTemp.length;i++){
		if(listefichiersTemp[i].endsWith(".txt")==true){
			listefichiers[i] = listefichiersTemp[i].substring(0,listefichiersTemp[i].length()-4);
		}
	}
	String document_name,document_content,document_class;
	for(int i=0;i<listefichiers.length;i++)
	{
		if(listefichiers[i]!=null)
		{
			document_name = listefichiers[i].split("_")[1];
			document_content = "";
			document_class = listefichiers[i].split("_")[0];
// JOptionPane.showMessageDialog(null,"LET’S GO ! pour le fichier "+document_name);
			String line;
			BufferedReader buff = null;
			try {
				4
				buff = new BufferedReader(new FileReader("/home/cedric/Dropbox/Public/M1_DECOL/S8/EC/projet/tt/"+listefichiers[i]+".txt"));
				while((line = buff.readLine()) != null)
				{
					String[] lineSplit = line.split("\t");
					if((lineSplit[1].equals("ADJ") || lineSplit[1].equals("NOM")) && !lineSplit[2].equals("<unknown>")) {
						document_content += lineSplit[2]+" ";
					}
				}
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
				try {
					buff.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			System.out.println(document_name+", \""+document_content+"\","+document_class);
			System.out.println("");
		}
	}
	System.out.println("\n");
}