package java_hex;
import java_hex.partie.*;

public class Main{
	public static void main(String[] args){
		int a = 1;
		int tailleGrille = 2;
		String nomPartie = "partie_test";
		Partie p = new Partie(nomPartie);
		do{
			switch(a){
				case 0 :
					//TODO appel menu principal
				case 1 : 
					p.getGrille().destroy();
					p = new Partie(nomPartie);
					p.getGrille().create(tailleGrille);
					break;
				case 2 :
					p.getGrille().destroy();
					p = new Partie(nomPartie);
					p.charger();
					break;
				default : 
					a = 3;
					break;
			}
			a = p.jouer();
		}while(a != 3);

	}
}

