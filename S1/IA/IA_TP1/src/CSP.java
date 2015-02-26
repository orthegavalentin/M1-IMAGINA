
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;

// Choix de codage 
//		Variable = String
//      Valeur = Object
//		un domaine = TreeSet<Object>
//		les couples (variable, domaine) = HashMap<String,TreeSet<Object>>
//		les contraintes = ArrayList<Constraint>

public class CSP {
	
	private HashMap<String,TreeSet<Object>> varDom; // table de hachage associant a chaque variable son domaine
	private ArrayList<Constraint> constraints; // liste des contraintes
	
	// initialise un CSP avec des structures vides
	public CSP() {
		varDom = new HashMap<String,TreeSet<Object>>();
		constraints = new ArrayList<Constraint>();
	}

	// initialise un CSP a partir d'un fichier texte
	public CSP(String fileName) {
		try {
			varDom = new HashMap<String,TreeSet<Object>>();
			constraints = new ArrayList<Constraint>();
			
			//lecture fichier
			BufferedReader lectureFichier = new BufferedReader (new FileReader(fileName));
			System.out.println("Lecture du fichier " + fileName);
			//variables
			String s = lectureFichier.readLine();
			int nbVar = Integer.parseInt(s);
			for(int i=0; i<nbVar; i++){
				s = lectureFichier.readLine();
				String[] traitPhrase = s.split(";");
				addVariable(traitPhrase[0]);
				for(int j=1; j<traitPhrase.length;j++){
					addValue(traitPhrase[0], traitPhrase[j]);
				}
			}
			
            //contraintes
			ArrayList<String> varTuple;
            ArrayList<Object> valTuple = null;
            s = lectureFichier.readLine();
            int nbCont = Integer.parseInt(s);
            for(int i = 0; i < nbCont; i++){
                    s = lectureFichier.readLine();
                    String[] tab = s.split(";");
                    varTuple = new ArrayList<String>(tab.length);
                    for(int k = 0; k < tab.length; k++){
                            varTuple.add(k, tab[k]);
                    }
                    Constraint c = new Constraint(varTuple);
                    int nbTuplesContrainte = Integer.parseInt(lectureFichier.readLine());
                    for(int j = 0; j < nbTuplesContrainte; j++){
                            s = lectureFichier.readLine();
                            tab = s.split(";");
                            valTuple = new ArrayList<Object>(tab.length);
                            for(int k = 0; k < tab.length; k++){
                                    valTuple.add(k,tab[k]);
                            }
                            c.addTuple(valTuple);
                    }
                    this.addConstraint(c);
            }
            lectureFichier.close();
		
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	// ajoute une variable
	public void addVariable(String var) {
		if(varDom.get(var)==null) varDom.put(var, new TreeSet<Object>());
		else System.err.println("Variable " + var + " deja existante");
	}

	// ajoute une valeur au domaine d'une variable
	public void addValue(String var, Object val) {
		if(varDom.get(var)==null) System.err.println("Variable " + var + " non existante");
		else {
			TreeSet<Object> dom = varDom.get(var);
			if (!dom.add(val)) /*varDom.put(var, dom);
			else */System.err.println("La valeur " + val + " est deja dans le domaine de la variable " + var); 
		}
	}
	
	// ajoute une contrainte
	public void addConstraint(Constraint c) {		
		// on ne verifie pas que les valeurs des contraintes sont "compatibles" avec les domaines
		if(!varDom.keySet().containsAll(c.getVariables())) System.err.println("La contrainte "+ c.getName() + " contient des variables ("+ c.getVariables() +") non declarees dans le CSP dont les variables sont " + varDom.keySet());
		else constraints.add(c);
	}
	
	public int getVarNumber() {
		return varDom.size();
	}

	public int getDomSize(String var) {
		return varDom.values().size();
	}
	
	public int getConstraintNumber(){
		return constraints.size();
	}
	
	public Set<String> getVar() {
		return varDom.keySet();
	}

	public TreeSet<Object> getDom(String var) {
		return varDom.get(var);
	}
	
	public HashMap<String,TreeSet<Object>> getDom() {
		return varDom;
	}

	public ArrayList<Constraint> getConstraints() {
		return constraints;
	}
	
	// retourne l'ensemble des contraintes contenant la variable pass�e en param�tre
	public ArrayList<Constraint> getConstraintsContaining(String var) {
		ArrayList<Constraint> selected = new ArrayList<Constraint>();
		for(Constraint c : constraints) {
			if(c.getVariables().contains(var)) selected.add(c);
		}
		return selected;
	}
		
	public String toString() {
		return "Var et Dom : " + varDom + "\nConstraints :" + constraints;
	}
	
	public static void main(String[] args){
		CSP monCSP = new CSP();
		// les variables
		String v1 = new String("x"); // la variable v1 a pour nom x
		String v2 = new String("y");
		String v3 = new String("z");
		monCSP.addVariable(v1); // ajout de la variable v1 au CSP
		monCSP.addVariable(v2);
		monCSP.addVariable(v3);
		monCSP.addVariable("x");
		// les domaines
		monCSP.addValue(v1,1); // ajout de la valeur 1 aud omaine de v1
		monCSP.addValue(v1,2);
		monCSP.addValue(v1,3);
		monCSP.addValue(v2,"as");
		monCSP.addValue(v2,"tutu");
		monCSP.addValue(v3,2);
		monCSP.addValue(v3,4);
		monCSP.addValue(v3,6);
		monCSP.addValue(v3,0);
		monCSP.addValue(v3,2);
		// les contraintes
		ArrayList<String> varTuple;
		ArrayList<Object> valTuple;
		// c1 : <x,y> : <2,"if"> <2,"as">,<4,"tutu">
		varTuple= new ArrayList<String>(2);
		varTuple.add(0,"x") ;
		varTuple.add(1,"y") ;
		Constraint c1 = new Constraint(varTuple);
		valTuple = new ArrayList<Object>(2);
		valTuple.add(0,2);
		valTuple.add(1,"if");
		c1.addTuple(valTuple);
		valTuple = new ArrayList<Object>(2);
		valTuple.add(0,2);
		valTuple.add(1,"as");
		c1.addTuple(valTuple);
		valTuple = new ArrayList<Object>(2);
		valTuple.add(0,4);
		valTuple.add(1,"tutu");
		c1.addTuple(valTuple);
		monCSP.addConstraint(c1);  

		// c2 : <y,x,z> : <"as",1,3> <"toto",3,5>
		varTuple= new ArrayList<String>(3);
		varTuple.add(0,"y") ;
		varTuple.add(1,"x") ;
		varTuple.add(2,"z") ;
		Constraint c2 = new Constraint(varTuple);
		valTuple = new ArrayList<Object>(3);
		valTuple.add(0,"as");
		valTuple.add(1,1);
		valTuple.add(2,3);
		c2.addTuple(valTuple);
		valTuple = new ArrayList<Object>(3);
		valTuple.add(0,"toto");
		valTuple.add(1,3);
		valTuple.add(2,5);
		c2.addTuple(valTuple);
		valTuple = new ArrayList<Object>(2);
		valTuple.add(0,4);
		valTuple.add(1,"tutu");
		c2.addTuple(valTuple);
		valTuple = new ArrayList<Object>(3);
		valTuple.add(0,"as");
		valTuple.add(1,1);
		valTuple.add(2,3);
		c2.addTuple(valTuple);
		monCSP.addConstraint(c2);
		
		//c3 : <w> : <1> <2>
		varTuple= new ArrayList<String>(1);
		varTuple.add(0,"w") ;
		Constraint c3 = new Constraint(varTuple);
		valTuple = new ArrayList<Object>(1);
		valTuple.add(0,1);
		c3.addTuple(valTuple);
		valTuple = new ArrayList<Object>(1);
		valTuple.add(0,2);
		c3.addTuple(valTuple);
		monCSP.addConstraint(c3);

		System.out.println("\nMon CSP " + monCSP);
	}
	
}

