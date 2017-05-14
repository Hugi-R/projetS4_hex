package java_hex.partie;

public class Partie{
	private Grille g;
	private String nom;
	private Historique h;
	
	static {
		System.loadLibrary("hex_jni");
	}
	
	public Partie(String nom){
		g = new Grille();
		this.nom = nom;
		h = new Historique();
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
	private native long chargerPartie(String nomPartie, int numeroSauvegarde, String historique);
	
	public int sauvegarder(){
		return sauvegarderPartie(g.getPointer(), nom, h.toString());
	}
	
	public int charger(int numeroSauvegarde){
		String historique = new String();
		long ptr = chargerPartie(nom, numeroSauvegarde, historique);
		if(ptr != 0){
			g = new Grille(ptr);
			h = new Historique(historique);
			return 0;
		} else {
			//erreurs
			return 1;
		}
	}
	
	public Grille getGrille(){
		return g;
	}
}
