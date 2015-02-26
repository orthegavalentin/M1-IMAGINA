import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;


public class KnowledgeBase {
	
	private ArrayList<Atome> baseFaits;
	private ArrayList<Rule> baseRegles;
	
	public ArrayList<Atome> getBaseFaits() {
		return baseFaits;
	}

	public void setBaseFaits(ArrayList<Atome> baseFaits) {
		this.baseFaits = baseFaits;
	}

	public ArrayList<Rule> getBaseRegles() {
		return baseRegles;
	}

	public void setBaseRegles(ArrayList<Rule> baseRegles) {
		this.baseRegles = baseRegles;
	}

	//constructeur vide qui cree une base vide
	public KnowledgeBase(){
		this.baseFaits = new ArrayList<Atome>();
		this.baseRegles = new ArrayList<Rule>();
	}
	
	//constructeur qui cree une base a partir d'un chemin vers un fichier texte
	public KnowledgeBase(String cheminFichier){
		this();
		try {
			BufferedReader reader = new BufferedReader (new FileReader(cheminFichier));
			//System.out.println("Lecture du fichier " + cheminFichier);
			Integer currentChar = Integer.parseInt(reader.readLine());
			for(int i = 0; i<currentChar; i++){
				Atome a = new Atome(reader.readLine());
				addFait(a);
			}
			currentChar = Integer.parseInt(reader.readLine());
			for(int i =0; i<currentChar; i++){
				Rule regle = new Rule(reader.readLine());
				addRule(regle);
			}
			reader.close();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	//accesseur a la base de faits
	public Atome accesseurBaseFaits(int nb){
		return this.baseFaits.get(nb);
	}
	
	//accesseur a la base de reles
	public Rule accesseurBaseRegles(int nb){
		return this.baseRegles.get(nb);
	}
	
	//Methode d'ajout d'une regle
	public void addRule(Rule regle){
		baseRegles.add(regle);		
	}
	
	//methode d'ajout d'un fait
	public void addFait(Atome fait){
		baseFaits.add(fait);
	}
	
	public String toString(){
		String affichage = "Base de faits : ";
		int i = 0;
		for(Atome a : baseFaits){
			if(i<baseFaits.size()-1){
				affichage = affichage + a.toString()+";";
			}
			else{
				affichage = affichage + a.toString();
			}
			i++;
		}
		
		affichage += "\nBase de regles : ";
		i=0;
		for(Rule r : baseRegles){
			if(i<baseRegles.size()-1){
				affichage = affichage + r.toString()+";";
			}
			else{
				affichage = affichage + r.toString();
			}
			i++;
		}
		return affichage;
	}
	
//	public void saturation(){
//		ArrayList<Atome> aTraiter = (ArrayList<Atome>) baseFaits.clone();
//		HashMap<Rule,Integer> compteur = new HashMap<Rule,Integer>();
//		int i;
//		for(Rule r : baseRegles){
//			compteur.put(r, r.getNbHyp());
//		}
//		while(!aTraiter.isEmpty()){
//			Atome a = aTraiter.remove(0);
//			for(Rule r : baseRegles){
//				if(r.contenir(a)){
//					i=compteur.get(r);
//					compteur.put(r, i--);
//					if(compteur.get(r) == 0){
//						if(!baseFaits.contains(r.getConclusion())){
//							baseFaits.add(r.getConclusion());
//							aTraiter.add(r.getConclusion());
//						}
//					}
//				}
//			}
//		}
		
//		boolean fin = false;
//		while(!fin){
//			ArrayList<Atome> nouveau = new ArrayList<Atome>();
//			for(Rule regle : this.baseRegles){
//				ArrayList<Atome> h = regle.getHypothese();
//				Atome c = regle.getConclusion();
//				Homomorphismes homo = new Homomorphismes(h, baseFaits);
//				for(HashMap<String, Object> s : homo.getHomo()){
//					Atome a = 
//				}
//			}
//		}
		
		public void saturation(){
	        boolean fin = false;
	        while(!fin){
	            ArrayList<Atome> n = new ArrayList<Atome>();
	            for(Rule regle : baseRegles){
	                Homomorphismes h = new Homomorphismes(regle.getHypothese(), this.baseFaits);
	                Solver mySolver = new Solver(h.homToCSP());
	                HashSet<HashMap<String,Object>> solutions = mySolver.getSolutions();
	                for(HashMap<String,Object> solution : solutions){
	                    String strAtome = regle.getConclusion().getLabel()+"(";
	                    for(Terme thet : regle.getConclusion().getListeTermes()){
	                        if(thet.estVariable()){
	                            strAtome += "'"+solution.get(thet.getLabel())+"',";
	                        }else{
	                            strAtome += "'"+thet.getLabel()+"',";
	                        }
	                    }
	                    strAtome = strAtome.substring(0, strAtome.length() - 1);
	                    strAtome += ")";
	                     
	                    Atome a = new Atome(strAtome);
	                    boolean present = false;
	                    for(Atome an : n){
	                        if(a.equals(an)){
	                            present = true;
	                        }
	                    }
	                    for(Atome af : baseFaits){
	                        if(a.equals(af)){
	                            present = true;
	                        }
	                    }
	                    if(!present){
	                        n.add(a);
	                    }
	                }
	                for(Atome a : n){
	                    this.baseFaits.add(a);
	                }
	            }
	             
	            if(n.size() == 0){
	                fin = true;
	            }
	        }
	        System.out.println(this.baseFaits);
	    }
	}
	
//}
