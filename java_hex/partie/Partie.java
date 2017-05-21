package java_hex.partie;
import java_hex.Convention;
import java_hex.Menu;

public class Partie{
	private Grille g;
	private String nom;
	private Historique h;
	private IJoueurs j1, j2;
	private Menu menuPartie;
	
	//workaround for java limitation
	public int errCode;
	
	static {
		System.loadLibrary("hex_jni");
	}
	
	public Partie(String nom){
		g = new Grille();
		this.nom = nom;
		h = new Historique();
		j1 = new Joueur(1, "W (o)");
		j2 = new Joueur(2, "B (*)");
		menuPartie = new Menu(true);
	}
	
	public Partie(String nom, IJoueurs j1, IJoueurs j2){
		g = new Grille();
		this.nom = nom;
		h = new Historique();
		this.j1 = j1;
		this.j2 = j2;
		menuPartie = new Menu(true);
	}
	
	public int openMenu(){
		String str = menuPartie.menu();
		String[] ss = str.split(" ",2);
		switch (ss[0]){
			case "n": return 1;
			case "q": return 1;
			case "l": return 1;
			case "s":
				int e = sauvegarder(ss[1]);
				if( e == 0 )
					System.out.println("Sauvegarde réussie.");
				else
					System.out.println("Une erreur (code "+ e +") s'est produite durant la sauvegarde, vérifiez les permissions.");
				return 0;
			case "c":
				changer(ss[1]);
				return 2;
			default	: return 0;
		}
	}
	
	private void changer(String s){
		String[] com = s.split(" ",2);
		switch(com[0]){
			case "h":
				j1 = new Joueur(1, "W (o)");
				break;
			case "o":
				j1 = new Ordinateur(1, "IA W (o)");
				break;
			default :
				System.out.println("ERREUR : quelque chose c'est mal passé pour changer les joueurs.");
				System.exit(1);
				break;
		}
		switch(com[1]){
			case "h":
				j2 = new Joueur(2, "B (*)");
				break;
			case "o":
				j2 = new Ordinateur(2, "IA B (*)");
				break;
			default :
				System.out.println("ERREUR : quelque chose c'est mal passé pour changer les joueurs.");
				System.exit(1);
				break;
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
	private native String chargerPartie(String nomPartie);
	
	/**
	 * Sauvegarde la partie, si aucun nom est fourni ( "" ), utilise le nom de partie.
	 */
	public int sauvegarder(String nomSave){
		if( nomSave.equals("") )
			return sauvegarderPartie( g.getPointer(), nom, h.toString() );
		else
			return sauvegarderPartie( g.getPointer(), nomSave, h.toString() );
	}
	
	public int charger(){
		String s = chargerPartie(nom);
		String[] rep = s.split("_", 2);
		long ptr = Long.parseLong(rep[0]);
		if(ptr != 0){
			g = new Grille(ptr);
			h = new Historique(rep[1]);
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
		IJoueurs j;
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
			if(a == 1) return 0;
		}while( g.vainqueur() == 0);
		System.out.println(g.toString());
		System.out.println("FELICITATIONS !!\nLe vainqueur est joueur " + j.getNom() + " !\n");
		return 0;
	}
}
