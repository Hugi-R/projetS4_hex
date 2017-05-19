package java_hex;

import java.util.Scanner;
import java.io.*;
import java.lang.*;

/**
	penser à close sc en fin d'utilisation
*/
public class Menu {
	private boolean estMenuSecondaire;
	Scanner sc = new Scanner(System.in);
	
	/**
	 * 
	 * @param secondaire: si false, le Menu aura les methodes sauvegarder et quitter inutilisables
	 */
	public Menu (Boolean secondaire){
		super();
		this.estMenuSecondaire = secondaire;
	}

	/**
	 * @return estMenuSecondaire
	 */
	public boolean estMenuSecondaire() {
		return this.estMenuSecondaire;
	}
	
	/**
	 *  affiche l'aide de jeu
	 */
	private void help(){
		System.out.println("HELP:\n\ncommandes en jeu:\n"+
		"	- {jouer, poser, pion, p} coordonnée1 coordonnée2	=> poser un pion aux coordonnées {c1, c2}\n"+
		"ex. p 5 12 					=> placer un pion ligne 5, colonne 12\n"+
		"	- {menu, m}						=> ouvre le menu\n"+
		"	- {historique, h}					=> affiche l'historique complet de la partie\n"+
		"	- {undo, u} nombre					=> défait les \"nombre\" derniers coups joués\n"+
		"ex. u 2						=> revient de 2 coups en arrière\n"+
		"   - qs => (quick save) sauvegarde rapide, utilise le nom de la partie pour sauvegarder\n");

		System.out.println("Appuyez sur Entrée pour revenir au menu précédent");
		sc.nextLine();
	}
	
	/**
	 *  test si la saisie est au bon format
	 * @return true si la saisie respecte le format imposé
	 */
	private boolean testNom(String saisie){
		int size = saisie.length();
		char c;
		int val;
		for (int i=0; i<size; i++){
			c = saisie.charAt(i);
			val = (int)c;
			if ((val<(int)'a' || val>(int)'z') && (val<(int)'A' || val>(int)'Z') && (val<(int)'0' || val>(int)'9') && val != (int)'_')
				return false;
		}
		return true;
	}
	
	/**
	 * permet de sauvegarder une partie sous le nom saisi
	 * @return String formaté: "s NomSave". NomSave est uniquement composé de lettres (min ou MAJ), de chiffres et de soulignés "_".
	 */
	private String save(){
		String saisie;
		boolean ok = false;
		do {
			System.out.println("Veillez entrer le nom que portera cette sauvegarde. Le nom ne doit contenir que des lettres, des chiffres et des souslignés \"_\"");
			saisie = sc.nextLine();
			ok = testNom(saisie);
			if (!ok)
				System.out.print("saisie incorrecte. ");
		} while (!ok);
		
		return "s " + saisie;
	}
	
	/**
	 *  affiche les règles du jeu de Hex
	 */
	private void regles(){
		System.out.println("REGLES:\n");
		System.out.println("Présentation du jeu de Hex:\n");
		System.out.println("	Le jeu de Hex est un jeu de société combinatoire abstrait pour deux joueurs.\n"+
				"Il se joue sur un tablier en forme de losange dont les cases sont hexagonales.\n"+
				"Toutes les dimensions du côté du losange sont possibles, la plus traditionnelle est celle composée par 11 hexagones,\n"+
				"mais on trouve aussi les valeurs 13 ou 19. L’un des inventeurs du jeu, John Nash, préconise un tablier de taille 14 × 14.");
		
		System.out.println("\n\nBut du jeu:\n");
		System.out.println("	Le but du jeu est, pour chaque joueur, de relier les deux bords opposés du plateau de jeu (noir: B ou blanc: W)\n"+
		"avec un chemin continu de pions.");
		
		System.out.println("\n\nLes coups:\n");
		System.out.println("	Chaque joueur joue à tour de rôle en posant un pion sur une case libre\n"+
		"n’importe où sur le plateau de jeu. Le premier qui crée un chemin contigu de pions gagne la partie.\n");

		System.out.println("Appuyez sur Entrée pour revenir au menu précédent");
		sc.nextLine();
	}

	
	/**
	 *  affiche le logo du jeu de Hex
	 */
	private void printLogo(){
			System.out.println("\n\n"+
"	    / \\ / \\ \n"+
"	   |   |   | \n"+
"	  / \\ / \\ / \\ \n"+
"	 | H | E | X | \n"+
"	  \\ / \\ / \\ / \n"+
"	   |   |   | \n"+
"	    \\ / \\ / \n\n");
		
	}
	
	/**
	 *  affiche le menu
	 */
	private void printMenu(){
		System.out.println("Entrez un des caractères suivants:");

		System.out.println("	n: commencer une nouvelle partie");
		if (this.estMenuSecondaire){
			System.out.println("	s: sauvegarder la partie en cours");
			System.out.println("	q: quitter la partie");
		}
		System.out.println("	l: (load) charger une partie");
		System.out.println("	h: (help) afficher l'aide de jeu");
		System.out.println("	r: afficher les règles du jeu de Hex");
		if (this.estMenuSecondaire)
			System.out.println("	f: fermer ce menu");
		else
			System.out.println("	q: fermer le programme");
	}
	
	/**
	 *  affiche le nom des sauvegardes existantes
	 * @return false si aucune sauvegarde trouvée, true sinon
	 */
	private static boolean printFnames(String sDir){
		File folder = new File(sDir);
		File[] listOfFiles = folder.listFiles();
		if (listOfFiles == null){
			System.out.println("	Il n'y a aucune sauvegarde\n");
			return false;
		}
		int len = listOfFiles.length;
		for (int i = 0; i < len; i++) {
			System.out.println("	" + listOfFiles[i].getName());
		}
		return true;
	}
	
	/**
	 *  détermine si la saisie correspond à un nom de sauvegarde existante
	 * @return false si saisie ne correspond a aucun nom de sauvegarde trouvée, true sinon
	 */
	private boolean nomExiste(String saisie){
		File folder = new File("./save");
		File[] listOfFiles = folder.listFiles();
		int len = listOfFiles.length;
		for (int i = 0; i < len; i++) {
			if (saisie.equals(listOfFiles[i].getName()))
				return true;
		}
		return false;
	}
	
	/**
	 * @return "" si load annulé ou "l NomPartie" sinon
	 */
	private String load(){
		String str;
		do {
			System.out.println("Entrez le nom d'une partie sauvegardée ou Entrée pour annuler:");
			if (!printFnames("./save")){
				System.out.println("Impossible de charger une partie");
			  return "";
			}
			str = sc.nextLine();
			if (str.equals("\n"))
				return "";
		} while (!nomExiste(str));
		return "l " + str;
	}
	
	/**
	 *  détermine si la saisie correspond à un nombre entre 2 et 35
	 * @return false si saisie ne correspond pas a un nombre entre 2 et 35, true sinon
	 */
	private boolean estIntFormater(String str){
		if (!str.matches("^\\d+$"))
			return false;
		int val = Integer.parseInt(str);
		if (val<2 || val>35)
			return false;
		return true;
	}
	
	/**
	 *  permet de créer une nouvelle partie avec un nom et une taille saisie
	 * @return un String de format: "n " + NomDeLaPartie + tailleGrille 
	 *  		avec NomDeLaPartie ne contennt que des lettre, chiffres et underscores
	 *		et tailleGrille un int entre 2 et 35
	 *       ou "" si action annulé
	 */
	private String nouvellePartie(){
		String str;
		boolean ok;
		do {
			System.out.println("Veuillez nommer votre nouvelle partie. Le nom ne doit contenir que des lettres, des chiffres et des souslignés \"_\""+
			"\nSaisissez uniquement Entrée pour annuler la création d'une nouvelle partie");
			str = sc.nextLine();
			if (str.equals(""))
				return "";
			ok = testNom(str);
			if (!ok)
				System.out.print("Saisie incorrecte. ");
		} while (!ok);
		String nom = str;
		do {
			System.out.println("Saisissez une taille de grille. Un nombre entre 2 et 35. La taille recommandée est 14"+
			"\nSaisissez uniquement Entrée pour annuler la création");
			str = sc.nextLine();
			if (str.equals(""))
				return "";
			ok = estIntFormater(str);
			if (!ok)
				System.out.print("Saisie incorrecte. ");
		} while (!ok);
		return "n " + nom + " " + str;
	}

	public String menu(){
		if (!this.estMenuSecondaire)
			printLogo();
		String str;
		while(true){
			printMenu();
			str = sc.nextLine();
			switch (str){
				case "n":
					if(!estMenuSecondaire){
						str = this.nouvellePartie();
						if( !str.equals("") ) return str;
					} else {
						System.out.println("Invalide en partie, veuillez quitter la partie en cours.");
					}
					break;
				case "l":
					if(!estMenuSecondaire){
						str = this.load();
						if( !str.equals("") ) return str;
					} else {
						System.out.println("Invalide en partie, veuillez quitter la partie en cours.");
					}
					break;
				case "q":
					return str;
				case "f":
					return str;
				case "s":
					if(estMenuSecondaire){
						str = this.save();
						if( !str.equals("") ) return str;
					} else {
						System.out.println("Impossible de sauvegarder si aucune partie est lancée.");
					}
					break;
				case "h": 
					this.help();
					break;
				case "r": 
					this.regles();
					break;
				default	:
					System.out.print("Saisie incorrecte. ");
					break;
			}
		}
	}
}