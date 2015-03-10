package affichage;


import java.awt.Color;
import java.awt.Graphics2D;

class Segment {
	PointVisible gauche;
	PointVisible droit;
	Color lineColor;

	//Precondition: f.x < t.x par convention et pour les besoins de l'algorithme de balayage gauche droite
	Segment(PointVisible f, PointVisible t) {
		gauche = f;
		droit = t;
		lineColor =  Couleur.nw;
		gauche.segment = this;
		droit.segment = this;
	}
	
	public boolean gauche(Segment s1){
		return (this.gauche.x < s1.gauche.x);
	}
	
	public boolean intersect(Segment s){
		boolean bool = false;
		Segment AC = new Segment(this.gauche, s.gauche);
		Segment AD = new Segment(this.gauche, s.droit);
		Segment CA = new Segment(s.gauche, this.gauche);
		Segment CB = new Segment(s.gauche, this.droit);
		if(!((det(this, AC) * det(this, AD)) > 0)){
			if(det(s, CA) * det(s, CB) < 0){
				bool = true;
			}
		}
		System.out.println(bool);
		//on regarde si p1 et p2 sont du meme coté de s1
		//det(AB,AC)*det(AB,AD) > 0 //meme coté donc FALSE... sinon
		//____________________< 0 -> det(CD,CA)*det(CD,CB) < 0 // -> intersection
		return bool;
	}
	
	public double det(Segment s0, Segment s1){
		return (s0.droit.x - s0.gauche.x) * (s1.droit.y - s1.gauche.y) - (s1.droit.x - s1.gauche.x) * (s0.droit.y - s0.gauche.y);
	}

	public void dessine(Graphics2D g) {
		g.setColor(lineColor);
		g.drawLine((int) gauche.x , (int) gauche.y , (int) droit.x, (int) droit.y);
	}
}
