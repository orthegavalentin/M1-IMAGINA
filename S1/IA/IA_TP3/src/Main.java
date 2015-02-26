
public class Main {
	
	public static void main(String args[]) {
		KnowledgeBase test = new KnowledgeBase("fromageDechevre.txt");
		System.out.println(test.toString());
		test.saturation();
		System.out.println("----saturation done ----");
		System.out.println(test.toString());
		
	}
}
