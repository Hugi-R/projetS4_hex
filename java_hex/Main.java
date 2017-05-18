package java_hex;
import java_hex.partie.*;

public class Main{
	private static int tailleGrille;
	private static String nomPartie;
	
	public static void main(String[] args){
		int a = 0;
		tailleGrille = 2;
		nomPartie = "partie_test";
		Partie p = new Partie(nomPartie);
		do{
			switch(a){
				case 0 :
					a = menuPrincipal();
					break;
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
			if( a == 1 || a == 2 )
				a = p.jouer();
		}while(a != 3);

	}
	
	private static int menuPrincipal(){
		Menu m = new Menu(false);
		String rep = m.menu();
		String[] commande = rep.split(" ", 2);
		switch(commande[0]){
			case("n") : 
				String[] com = commande[1].split(" ");
				nomPartie = com[0];
				tailleGrille = Integer.parseInt(com[1]);
				return 1;
			case("l") : 
				nomPartie = commande[1];
				return 2;
			case("q") : return 3;
			default : return 0;
		}
	}
	
	
}

