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
			String[] com = command.split(" ",2);
			switch (com[0]) {
			case "poser" :
			case "pion":
			case "p" :
				if (com.length == 1){
				choixTrouve = saisirCase(p," ");
				}else{
				choixTrouve = saisirCase(p,com[1]);
				}
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
	
	public Boolean saisirCase (Partie p, String s){
		      String[] para = s.split(" ");
		      int l,c;
		      try {
			    l = Integer.parseInt(para[0]);
			} catch (NumberFormatException e) {
			    return false ;
			}
			try {
			    c = Integer.parseInt(para[1]);
			} catch (NumberFormatException e) {
			    return false;
			}
		      if ( p.getGrille().ajouterPion(l-1,c-1,couleur)){
			    return true;
		      }else{
			    System.out.println("saisie invalide ");
			    return false;
		      }
		
		}/*
		int colonne ;
		int ligne ; 
		System.out.println("veuillez saisir une ligne ");
		ligne = input.nextInt();
		System.out.println("veuillez saisir une colonne");
		colonne = input.nextInt() ;
		input.nextLine(); // vide le buffer
		return p.getGrille().ajouterPion(ligne-1, colonne-1, couleur);*/
	
	
}
