package interfaceHex;

import java.util.Scanner;

public class Menu {
	private static final int taille = 6;
	private boolean[] permissions;
	
	/**
	 * 
	 * @param permissions: est une combinaisson des charactères suivants
	 * pour attribuer l'autorisation correspondante:
	 * 		n: new game
	 * 		s: sauvegarder
	 * 		l: load (charger)
	 * 		h: help
	 * 		r: règles
	 * 		c: commandes
	 */
	public Menu (String permissions){
		super();
		this.permissions=new boolean[taille];
		for(int i=0; i<taille; i++){
			this.permissions[i] = false;
		}
		String[] perm = permissions.split("(?<=.)");
		int size = perm.length;
		for (int i=0; i<size; i++){
			switch (perm[i]){
				case "n": 	this.permissions[0]=true;
							break;
				case "s": 	this.permissions[1]=true;
							break;
				case "l": 	this.permissions[2]=true;
							break;
				case "h": 	this.permissions[3]=true;
							break;
				case "r": 	this.permissions[4]=true;
							break;
				case "c": 	this.permissions[5]=true;
							break;
				default	:	break;
			}
		}
	}

	/**
	 * @return the permissions
	 */
	public boolean[] getPermissions() {
		return permissions;
	}
	
	
	
	
	
	
	public void new_game(){
		System.out.println("new game");
	}
	
	public void sauvegarder(){
		System.out.println("save");
	}
	
	public void charger(){
		System.out.println("charger");
	}
	
	public void help(){
		System.out.println("help");
	}
	
	public void regles(){
		System.out.println("Présentation du jeu de Hex\n");
		System.out.println("	Le jeu de Hex est un jeu de société combinatoire abstrait pour deux joueurs."+
				" Il se joue sur un tablier en forme de losange dont les cases sont hexagonales."+
				" Toutes les dimensions du côté du losange sont possibles, la plus traditionnelle est celle composée par 11 hexagones,"+
				" mais on trouve aussi les valeurs 13 ou 19. L’un des inventeurs du jeu, John Nash, préconise un tablier de taille 14 × 14."+
				" Ce jeu possède des similarités avec le go. Ce jeu, inventé par des mathématiciens fait uniquement appel à la logique,"+
				" à l’image du go ou des échecs. Son étude est source d’inspiration, non seulement en théorie des jeux,"+
				" mais aussi pour d’autres branches des mathématiques comme la topologie ou la géométrie algébrique."+
				" Si l’on sait qu’il existe une stratégie gagnante pour le premier joueur,"+
				" cette stratégie est inconnue si le tablier n’est pas de petite taille (de côté strictement plus petit que 9)."+
				" La recherche de stratégies efficaces, à défaut d’une stratégie gagnante, est l’objet d’études en intelligence artificielle.");
		
		System.out.println("\n\nBut du jeu\n");
		System.out.println("Le but du jeu est, pour chaque joueur, de relier les deux bords opposés du plateau de jeu (noir: B ou blanc: W)"+
		" avec un chemin continu de pions.");
		
		System.out.println("\n\nLes coups\n");
		System.out.println("Chaque joueur joue à tour de rôle en posant un pion sur une case libre"+
		" n’importe où sur le plateau de jeu. Le premier qui crée un chemin contigu de pions gagne la partie.\n");

		this.affichage();
	}
	
	public void commandes(){
		System.out.println("commandes");
		
	}
	
	private void printMenu(){
		System.out.println("Entrez une des commandes suivantes:");
		for (int i=0; i<taille; i++){
			if (this.permissions[i])
			switch (i){
				case 0: 	System.out.println("	n: commencer une nouvelle partie");
							break;
				case 1: 	System.out.println("	s: sauvegarder la partie en cours");
							break;
				case 2: 	System.out.println("	l: (load) charger une partie");
							break;
				case 3: 	System.out.println("	h: (help) afficher l'aide");
							break;
				case 4: 	System.out.println("	r: afficher les règles du jeu de Hex");
							break;
				case 5: 	System.out.println("	c: afficher les commandes utilisables lors d'une partie");
							break;
				default	:	break;
			}
		}
	}
	
	public void affichage(){
		Scanner sc = new Scanner(System.in);
		String str;
		printMenu();
		str = sc.nextLine();
		while (!(str.equals("n") || str.equals("s") || str.equals("l") || str.equals("h") || str.equals("r") || str.equals("c"))){
				System.out.print("saisie incorrecte. ");
				printMenu();
				str = sc.nextLine();
		}
		sc.close();
		switch (str){
			case "n": this.new_game();
					break;
			case "s": this.sauvegarder();
					break;
			case "l": this.charger();
					break;
			case "h": this.help();
					break;
			case "r": this.regles();
					break;
			case "c": this.commandes();
					break;
			default	:break;
		}
	}
	
}
