package java_hex;

import java.util.Scanner;


/**
	penser à close sc en fin d'utilisation
*/
public class Menu {
	private boolean MenuPrincipal;
	Scanner sc = new Scanner(System.in);
	
	/**
	 * 
	 * @param principal: si true, le Menu aura les la sauvegarde, quitter partie inutilisables
	 */
	public Menu (Boolean principal){
		super();
		this.MenuPrincipal = principal;
	}

	/**
	 * @return the permissions
	 */
	public boolean estMenuPrincipal() {
		return this.MenuPrincipal;
	}
	
	
	
	
	
	
	public int new_game(){
		System.out.println("new game");
		return 0;
	}
	
	public int quitterPartie(){
		return 0;
	}
	
	public int sauvegarder(){
		System.out.println("save");
		return 0;
	}
	
	public int charger(){
		System.out.println("charger");
		return 0;
	}
	
	public int help(){
		System.out.println("help");
		return 0;
	}
	
	public int regles(){
		System.out.println("Présentation du jeu de Hex\n");
		System.out.println("	Le jeu de Hex est un jeu de société combinatoire abstrait pour deux joueurs.\n"+
				" Il se joue sur un tablier en forme de losange dont les cases sont hexagonales.\n"+
				" Toutes les dimensions du côté du losange sont possibles, la plus traditionnelle est celle composée par 11 hexagones,\n"+
				" mais on trouve aussi les valeurs 13 ou 19. L’un des inventeurs du jeu, John Nash, préconise un tablier de taille 14 × 14.");
		
		System.out.println("\n\nBut du jeu\n");
		System.out.println("Le but du jeu est, pour chaque joueur, de relier les deux bords opposés du plateau de jeu (noir: B ou blanc: W)\n"+
		" avec un chemin continu de pions.");
		
		System.out.println("\n\nLes coups\n");
		System.out.println("Chaque joueur joue à tour de rôle en posant un pion sur une case libre\n"+
		" n’importe où sur le plateau de jeu. Le premier qui crée un chemin contigu de pions gagne la partie.\n");

		System.out.println("Appuyez sur Entrée pour revenir au menu précédent");
		
		sc.nextLine();
		return 0;
	}
	
	public void commandes(){
		System.out.println("commandes");
	}
	
	private void printMenuPartie(){
		System.out.println("Entrez un des caractères suivants:");
		
		System.out.println("	n: commencer une nouvelle partie");
		if (this.estMenuPrincipal){
			System.out.println("	s: sauvegarder la partie en cours");
			System.out.println("	q: quitter la partie");
		}
		System.out.println("	l: (load) charger une partie");
		System.out.println("	h: (help) afficher l'aide");
		System.out.println("	r: afficher les règles du jeu de Hex");
		System.out.println("	c: afficher les commandes utilisables lors d'une partie");
	}
	
	public void affichage(){
		String str;
		printMenuParti();
		str = sc.nextLine();
		while (!(str.equals("n") || str.equals("s") || str.equals("l") || str.equals("h") || str.equals("r") || str.equals("c"))){
				System.out.print("saisie incorrecte. ");
				printMenuParti();
				str = sc.nextLine();
		}
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
	



public static void main(String[] args) {
		Boolean estMenuPrincipal = true;
		Menu menu = new Menu(estMenuPrincipal);
		menu.affichage();
		menu.sc.close();
	}





}