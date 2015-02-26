import java.util.ArrayList;


public class Rule {
	
	private ArrayList<Atome> hypothese;
	private Atome conclusion;
	
	public ArrayList<Atome> getHypothese() {
		return hypothese;
	}

	public void setHypothese(ArrayList<Atome> hypothese) {
		this.hypothese = hypothese;
	}

	public Atome getConclusion() {
		return conclusion;
	}

	public void setConclusion(Atome conclusion) {
		this.conclusion = conclusion;
	}
	
	public Rule(String S){
		//S de la forme "atome1;atome2;...atomek"
		String[] tabAtomes = S.split(";");
		hypothese = new ArrayList<Atome>();
		for (int i = 0; i<tabAtomes.length-1; i++){
			Atome newAtome = new Atome(tabAtomes[i]);
			hypothese.add(newAtome);
		}
		conclusion = new Atome(tabAtomes[tabAtomes.length-1]);
	}
	
	public boolean contenir (Atome A){
		boolean retour = false;
		for(Atome Atom : hypothese){
			if(Atom.equals(A)){
				retour = true;
			}
		}
		return retour;
	}
	
	public int getNbHyp(){
		int nb = 0;
		for(Atome Atom : hypothese){
			nb = nb+1;
		}
		return nb;
	}
	
	public String toString(){
		String aff = "";
		for(Atome Atom : hypothese){
			aff = aff + hypothese.toString() + "  @  ";
		}
		aff = aff + conclusion.toString();
		return aff;
	}
	
}
