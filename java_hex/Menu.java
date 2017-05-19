package java_hex;

import java.util.Scanner;

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
	
	private void help(){
		System.out.println("HELP:\n\ncommandes en jeu:\n"+
		"	- {jouer, poser, pion, p} coordonnée1 coordonnée2	=> poser un pion aux coordonnées {c1, c2}\n"+
		"ex. p 5 12 					=> placer un pion ligne 5, colonne 12\n"+
		"	- {menu, m}						=> ouvre le menu\n"+
		"	- {historique, h}					=> affiche l'historique complet de la partie\n"+
		"	- {undo, u} nombre					=> défait les \"nombre\" derniers coups joués\n"+
		"ex. u 2						=> revient de 2 coups en arrière\n");

		System.out.println("Appuyez sur Entrée pour revenir au menu précédent");
		sc.nextLine();
	}
	/*
	private static printFnames(String sDir){
		File[] faFiles = new File(sDir).listFiles();
		for(File file: faFiles)
			System.out.println(file.getAbsolutePath());
		if(file.isDirectory())
			printFnames(file.getAbsolutePath());
	}
	
	private String load(){
		String ret = "l ";
		System.out.println("Entrez le nom d'une partie sauvegardée:");
		printFnames("./save");
		return ret;
	}
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
	
	private void printMenu(){
		if (!this.estMenuSecondaire)
			printLogo();
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
	
	/* retourne "" si l'utilisateur annule */
	private String load(){
		//TODO
		return "";
	}
	
	/* retourne "" si l'utilisateur annule */
	private String nouvellePartie(){
		return "";
	}

	public String menu(){
		String str;
		while(true){
			printMenu();
			str = sc.nextLine();
			/*while (!(str.equals("n") ||
			(this.estMenuSecondaire && (str.equals("f") ||
							str.equals("s") || 
							str.equals("q"))) ||
			str.equals("l") ||
			str.equals("h") ||
			str.equals("r"))){
				System.out.print("saisie incorrecte. ");
				printMenu();
				str = sc.nextLine();
			}*/
			switch (str){
				case "n":
					if(!estMenuSecondaire){
						str = this.nouvellePartie();
						if( !str.equals("") ) return str;
					} else {
						System.out.println("Invalide en partie, veuillez quitter en la partie cour.");
					}
					break;
				case "l":
					if(!estMenuSecondaire){
						str = this.load();
						if( !str.equals("") ) return str;
					} else {
						System.out.println("Invalide en partie, veuillez quitter en la partie cour.");
					}
					break;
				case "q":
					return str;
				case "f":
					return str;
				case "s":
					return str;
				case "h": 
					this.help();
					break;
				case "r": 
					this.regles();
					break;
				default	: break;
			}
		}
	}
}