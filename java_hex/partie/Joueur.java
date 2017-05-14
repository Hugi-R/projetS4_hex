package java_hex.partie;
import java.util.Scanner;

public class Joueur {
	int couleur ;
	Scanner input = new Scanner(System.in);
	
	public Joueur( int couleur ) {
		this.couleur = couleur ;
	}
	
	public void action (Partie p){
		String command ;
		boolean choixTrouve  = false;
		while (!choixTrouve){
			System.out.println("Que souhaitez-vous faire ?");
			command = input.nextLine();
			switch (command) {
			case "poser" :
			case "pion":
			case "p" :
				saisirCase(p);
				choixTrouve = true;
				break;
			case "menu" : 
			case "m" :
				//openMenu(); // a modifier si changement
				choixTrouve = true ;
				break ;
			default :
				break;
			}
		}
	}
	
	public void saisirCase (Partie p){
		int colonne ;
		int ligne ;
		System.out.println("veuillez saisir une colonne");
		colonne = input.nextInt() ; 
		System.out.println("veuillez saisir une ligne ");
		ligne = input.nextInt();
		p.getGrille().ajouterPion(ligne, colonne, couleur);
	}
	
	
}
