                                                                                                                    

import java.util.HashMap;

// exemple de main pour le test de l'algorithme de backtrack

public class TP {

	public static void main(String args[]) {
		//Lire un CSP depuis un fichier
		String fileName = "contraintesControle.txt";
		CSP myProblem;
		try {    
			System.out.println("Chargement du fichier : "+new java.io.File( "." ).getCanonicalPath()+"/"+fileName);
			myProblem = new CSP(fileName);
		}catch(Exception e) {
	     System.err.println("Erreur lors du chargement du fichier " + fileName);
			System.err.println(e);
			return;
		}
		
		System.out.println("\nRecherche d'une solution au probleme :\n" + myProblem);
		Solver mySolver = new Solver(myProblem);
		HashMap<String,Object> mySolution = mySolver.searchSolution();
		if (mySolution == null) System.out.println("Pas de solution !");
		else System.out.println("\nUne solution est " + mySolution);
		System.out.println("\nIl y a : " +mySolver.getSolutions().size() + " solutions\nqui sont : " + mySolver.getSolutions());
		

//		System.out.println("\nRecherche de solutions au probleme :\n" + myProblem);
//		Solver mySolver = new Solver(myProblem);
//		HashMap<String,Object> mySolutions = mySolver.searchSolution();
//		if (mySolutions == null) System.out.println("Pas de solution !");
//		else System.out.println("Il y a : " +mySolver.getSolutions().size() + " solution\nqui sont : " + mySolver.getSolutions());
	}
}
