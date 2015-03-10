package main;
import javax.swing.JFrame;
import affichage.Vue;

public class Main {
	
	public static void main(String s[]) {
		int w = 612, h= 792;
		JFrame frame = new JFrame("Intersection de segments");
		Vue v = new Vue(10,w,h);
		v.init(20);
		frame.add(v);
		frame.pack();
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
