package java_hex.partie;
import java.util.Scanner;

public class Joueur {
	int couleur ;
	String nom;
	Scanner input = new Scanner(System.in);
	
	public Joueur( int couleur, String nom ) {
		this.couleur = couleur ;
		this.nom = nom;
	}
	
	public String getNom(){
		return nom;
	}
	
	public void action (Partie p){
		String command ;
		boolean choixTrouve  = false;
		while (!choixTrouve){
			System.out.println("Que souhaitez-vous faire ? (votre tour se termine après avoir joué ou undo)");
			command = input.nextLine();
			String[] com = command.split(" ",2);
			switch (com[0]) {
				case "jouer" :
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
					p.openMenu();
					break ;
				case "h" :
				case "historique" :
					historique(p, com);
					break;
				case "u" :
				case "undo" :
					choixTrouve = undo(p, com);
					break;
				default :
					break;
			}
		}
	}
	
	/**
	 * Affiche en partie ou totalement l'historique
	 */
	private void historique(Partie p, String[] com){
		String hist;
		if(com.length > 1){
			try {
				int n = Integer.parseInt(com[1]);
				hist = p.getHistorique().printLast( n );
				System.out.println(hist);
				return;
			} catch (NumberFormatException e) {
				hist = p.getHistorique().printLast( p.getHistorique().size() );
				System.out.println(hist);
			}
		} else {
			hist = p.getHistorique().printLast( p.getHistorique().size() );
			System.out.println(hist);
		}
	}
	
	private boolean undo(Partie p, String[] com){
		if(com.length > 1){
			try {
				int n = Integer.parseInt(com[1]);
				p.undo(n);
				return true;
			} catch (NumberFormatException e){
				System.out.println("Saisie incorrecte.");
				return false;
			}
		} else {
			System.out.println("Saisie incorrecte.");
			return false;
		}
	}
	
	private Boolean saisirCase (Partie p, String s){
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
				if ( p.coup(l-1,c-1,couleur) ){
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
