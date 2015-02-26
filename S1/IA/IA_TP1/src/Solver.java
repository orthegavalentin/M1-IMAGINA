
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;


public class Solver {

		public CSP problem; // l'instance de CSP                 
		private HashMap<String,Object> assignation; // codage d'une solution partielle ou totale
		private HashSet<HashMap<String,Object>> solutions;
		
		public Solver(CSP p) {
			problem = p;
			assignation = new HashMap<String,Object>();   
			setSolutions(new HashSet<HashMap<String,Object>>());
		}
		        
		public HashMap<String,Object> searchSolution() { 
			searchAllSolutions();
			return backtrack();
		}
		
		private boolean isConstraintValid(Constraint c, HashMap<String,Object> a) {
			ArrayList<String> vars = new ArrayList<String>();
			for (String var : a.keySet()) {
				if(c.getVariables().contains(var)){
					vars.add(var);
				}
			}
			boolean ok = true;
			for(ArrayList<Object> tuple : c.getContraintes()) {
				ok = true;
				while(ok){
					for (String string : vars) {
						if(!tuple.get(c.getVariables().indexOf(string)).toString().equals(a.get(string).toString())){
							ok = false;
							break;
						}
					}
					if(ok)
						return ok;
				}
			}

			return ok;
		}
		
		private boolean areAllConstraintsValid(HashMap<String,Object> a) {
			for (Constraint c : problem.getConstraints()) {
				if(!isConstraintValid(c, a)) {
					return false;
				}
			}
			return true;
		}
		
		// l'algo recursif
		private HashMap<String,Object> backtrack() {
			if (this.assignation.size() == problem.getVarNumber()){
				return assignation;
			}
			String s = this.chooseVar(problem.getVar(), assignation.keySet());
			for (Object val : tri(problem.getDom(s))) {
				assignation.put(s, val);
				if(areAllConstraintsValid(assignation)){
					HashMap<String,Object> temp = backtrack();
					if(temp != null && temp.size() == problem.getVarNumber()){
						return temp;
					}
				}
				else{
					assignation.remove(s);
				}
			}
			return null;
		}
		
		// choix d'une variable
		private String chooseVar(Set<String> allVar, Set<String> assignedVar) {
			for (String string : allVar) {
				if(!assignedVar.contains(string)) {
					return string;
				}
			}
			return null;
		}
		
		
		private TreeSet<Object> tri(TreeSet<Object> values) {
			return values;
		}
		
		
		// retourne l'ensemble des solutions
		@SuppressWarnings("unchecked")
		public HashSet<HashMap<String,Object>> searchAllSolutions() {
			if (this.assignation.size() == this.problem.getVarNumber()) {
				this.getSolutions().add((HashMap<String, Object>) this.assignation.clone());
				return this.getSolutions();
			}
			
			String s = this.chooseVar(this.problem.getVar(), this.assignation.keySet());
			
			for (Object val : tri(problem.getDom(s))) {
				this.assignation.put(s, val);
				if(areAllConstraintsValid(assignation)) {
					this.searchAllSolutions();
				}
				this.assignation.remove(s);
			}
			
			return this.getSolutions();
		}

		public HashSet<HashMap<String,Object>> getSolutions() {
			return solutions;
		}

		public void setSolutions(HashSet<HashMap<String,Object>> solutions) {
			this.solutions = solutions;
		}
}
