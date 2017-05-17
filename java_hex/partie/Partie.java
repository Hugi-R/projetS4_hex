package java_hex.partie;
import java_hex.Convention;
import java_hex.Menu;

public class Partie{
	private Grille g;
	private String nom;
	private Historique h;
	private Joueur j1, j2;
	private Menu menuPartie;
	
	static {
		System.loadLibrary("hex_jni");
	}
	
	public Partie(String nom){
		g = new Grille();
		this.nom = nom;
		h = new Historique();
		j1 = new Joueur(1, "W (o)");
		j2 = new Joueur(2, "B (*)");
		menuPartie = new Menu(false);
	}
	
	public int openMenu(){
		String str = menuPartie.menu();
		switch (str){
			case "n": return 1;
			case "q": return 3;
			case "l": return 2;
			default	: return 0;
		}
	}
	
	public Historique getHistorique(){
		return h;
	}
	
	/**
	 * Annule les n dernières actions
	 */
	public void undo(int n){
		int t = g.getSize();
		h.supprDerniers(n);
		g.destroy();
		g = h.grilleFromHistorique(t);
	}
	
	/**
	 * Place un pion et met à jour l'historique
	 */
	protected boolean coup(int l, int c, int couleur){
		if(g.ajouterPion(l,c,couleur)){
			h.add(Convention.convertToChar(couleur), l, c);
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 * @brief sauvegarde la partie
	 * @param [input] g pointeur vers la grille
	 * @param [input] nomPartie est le dossier ou se trouvent les sauvegardes de la partie
	 * @param [input] historique String contenant l'historique deja formate
	 * @return retourne le numero de sauvegarde, ou un code erreur (-x)
	 * 	code d'erreur:	-1: historique incoherent avec la grille 
	 * 			-2: erreur lors de l'ouverture de repertoire nomPartie
	 * 			-3: erreur lors de l'ouverture du fichier de sauvegarde
	 */
	private native int sauvegarderPartie(long g, String nomPartie, String historique);
		
	/**
	 * @brief cree une grille selon la sauvegarde indiquee
	 * @param [input] nomPartie est le dossier ou se trouvent les sauvegardes de la partie
	 * @param [input] numeroSauvegarde 
	 * @param [output] historique le String contenant l'historique
	 * @return le pointer vers la grille initilise si tout c'est bien passe, 0 sinon
	 */
	private native long chargerPartie(String nomPartie, String historique);
	
	public int sauvegarder(){
		return sauvegarderPartie(g.getPointer(), nom, h.toString());
	}
	
	public int charger(){
		String historique = new String();
		long ptr = chargerPartie(nom, historique);
		if(ptr != 0){
			g = new Grille(ptr);
			h = new Historique(historique);
			return 0;
		} else {
			//erreurs
			return 1;
		}
	}
	
	public void nouvelleGrille(int t){
		g.create(t);
	}
	
	public Grille getGrille(){
		return g;
	}
	
	public int jouer(){
		Joueur j;
		int a; //action du joueur
		do{
			if(h.dernierJoueur() == 1){
				j = j2;
			} else {
				j = j1;
			}
			System.out.println(g.toString());
			System.out.println("Joueur " + j.getNom() + " c'est à vous !");
			a = j.action(this);
			if(a != 0) return a;
		}while( g.vainqueur() == 0);
		System.out.println(g.toString());
		System.out.println("Le vainqueur est joueur " + j.getNom() + " !");
		return 0;
	}
}
