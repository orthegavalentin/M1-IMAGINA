import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

/*
 * Il y a : 4 solutions
 * qui sont : [{u=c, z=e, y=d, x=b}, {u=b, z=e, y=b, x=a}, {u=c, z=e, y=e, x=b}, {u=c, z=e, y=b, x=a}]
 */


public class Homomorphismes {
	ArrayList<Atome> A1;
	ArrayList<Atome> A2;
	
	public Homomorphismes(String S1, String S2){
		this.A1 = this.strToAtome(S1);
		this.A2 = this.strToAtome(S1);
	}
	
	public Homomorphismes(ArrayList<Atome> A1, ArrayList<Atome> A2){
        this.A1 = A1;
        this.A2 = A2;
	}
	
	public CSP homToCSP(){//NOT FINISHED
		
		CSP c = new CSP();
		
		ArrayList<String> tabConstante = new ArrayList<String>();
        for(int i = 0; i < this.A2.size(); i++){
            ArrayList<Terme> termes = this.A2.get(i).getListeTermes();
            for(int j = 0; j < termes.size(); j++){
                if(termes.get(j).estConstante()){
                    tabConstante.add(termes.get(j).getLabel());
                }
            }
        }
       
        //variables
        for(int i = 0; i < this.A1.size(); i++){
            ArrayList<Terme> termes = this.A1.get(i).getListeTermes();
            for(int j = 0; j < termes.size(); j++){
                if(termes.get(j).estVariable()){
                    c.addVariable(termes.get(j).getLabel());
                    for(int k = 0; k < tabConstante.size(); k++){
                        c.addValue(termes.get(j).getLabel(), tabConstante.get(k));
                    }
                }
            }
        }
        
        //contraintes
        for(int i = 0; i < this.A1.size(); i++){
            ArrayList<String> varTuple;
            ArrayList<Object> valTuple;
           
            ArrayList<Terme> termes = this.A1.get(i).getListeTermes();
            varTuple = new ArrayList<String>();
            for(int k = 0; k < termes.size(); k++){
                varTuple.add(k, termes.get(k).getLabel());
            }
            Constraint ct = new Constraint(varTuple);
           
            for(int j = 0; j < this.A2.size(); j++){
                valTuple= new ArrayList<Object>();
                if(this.A1.get(i).getLabel().equals(this.A2.get(j).getLabel())){
                    ArrayList<Terme> termes2 = this.A2.get(j).getListeTermes();
                    if(this.hasDoublon(this.A1.get(i))){
                        if(this.hasDoublon(this.A2.get(j))){
                            if(this.isValid( this.A1.get(i) , this.A2.get(j) )) {
                                for(int k = 0; k < termes2.size(); k++){
                                    valTuple.add(k, termes2.get(k).getLabel());
                                }
                            }
                        }
                           
                    }else{
                        for(int k = 0; k < termes2.size(); k++){
                            valTuple.add(k, termes2.get(k).getLabel());
                        }
                    }
                    ct.addTuple(valTuple);
                }
                   
            }
            c.addConstraint(ct);
           
        }
        
		
		return c;
	}
	
	public ArrayList<Atome> strToAtome(String s){
        ArrayList<Atome> tab = new ArrayList<Atome>();
        String[] t = s.split(";");
        for(int i = 0; i < t.length; i++){
                tab.add(new Atome(t[i]));
        }
        return tab;
	}
	
	public String toString(){
        return this.A1.toString()+"\n"+this.A2.toString();
	}
	
	private boolean hasDoublon(Atome a){
	    ArrayList<Terme> t = a.getListeTermes();
	    for(int i = 0; i < t.size(); i++){
            for(int j = 0; j < t.size(); j++){
                if(i != j && t.get(i).getLabel().equals(t.get(j).getLabel())){
                    return true;
                }
            }
	    }
	    return false;
	}

	private ArrayList<ArrayList> getDoublonPositions(Atome a){
        ArrayList<ArrayList> al = new ArrayList();
        ArrayList<Terme> t = a.getListeTermes();
        for(int i = 0; i < t.size(); i++){
            for(int j = i; j < t.size(); j++){
                if(i != j && t.get(i).getLabel().equals(t.get(j).getLabel())){
                    ArrayList tab = new ArrayList();
                    tab.add(0, i);
                    tab.add(1, j);
                    al.add(tab);
                }
            }
        }
        return al;
	}
	
	public boolean isValid(Atome a, Atome a2){
	    ArrayList<ArrayList> doublonA = this.getDoublonPositions(a);
	    ArrayList<ArrayList> doublonA2 = this.getDoublonPositions(a2);
	    if(doublonA.size() != doublonA2.size()){
            return false;
	    }
	    for(ArrayList posA : doublonA){
            for(ArrayList posA2 : doublonA2){
                if(posA.get(0) != posA2.get(0) || posA.get(1) != posA2.get(1)){
                    return false;
                }
            }
	    }
        return true;
	}
	
	public HashSet<HashMap<String, Object>> getHomo(){
		Solver s = new Solver(this.homToCSP());
		return s.searchAllSolutions(); 
	}
	
	public static void main(String args[]){
        String a1 = "p(x,y);p(y,z);p(x,u);p(z,z);r(x);r(u)";
        String a2 = "p('a','b');p('a','c');p('b','c');p('b','d');p('b','e');p('d','e');p('e','e');r('a');r('b');r('c')";
        Homomorphismes h = new Homomorphismes(a1, a2);
       
        CSP c = h.homToCSP();
        System.out.println(c);
        Solver mySolver = new Solver(c);
        HashMap<String, Object> mySolution = mySolver.searchSolution();
	}
	
		
	
}
