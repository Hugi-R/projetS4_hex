public class Grille{
	private long grille;
	
	static {
		System.loadLibrary("grille_jni");
	}
	
	public Grille(){
		grille = 0;
	}
	
	/**
	 * @brief construction d'une grille de taille t 
	 */
	private native long grilleCreation( int t );
	
	/**
	 * @brief detruit la grille et libère la mémoire
	 */
	private native void grilleDestruction( long g);
	
	/**
	 * @brief ajoute un pion a une case
	 * 	@param g la grille pour accéder 
	 *	@param l la ligne de la case a modifier
	 *	@param c la colonne de la case a modifier
	 *	@param pion la valeur du pion ( RED ou BLU )
	 */
	private native void grilleAjouterPion( long g ,int l , int c , int pion );
	
	/**
	 * @brief verifie la validiter du coup 
	 * 	@param g la grille pour accéder 
	 *	@param l la ligne du coup a verifier
	 *	@param c la colonne du coup a verifier
	 * @return true si le coup est jouable 
	 */
	private native boolean grilleCoupValide ( long g , int l , int c );
	
	/**
	 * @brief verifie si un joueur a gagner
	 * 	@param g la grille pour accéder 
	 * @return 0 si aucun gagnant sinon retourne la valeur du gagnant : RED 1, BLU 2
	 */
	private native int grilleVainqueur ( long g);

	/**
	 * @param g la grille pour accéder 
	 * @return la grille sous forme d'un tableau, NULL s'il y a eu un problème
	 */
	private native int[] grilleToTab( long g );
	
	/**
	 * @param g la grille pour accéder 
	 * @return la grille sous forme d'un string
	 */
	private native String grilleToString (long g );
	
	/**
	 * @brief construit une grille depuis un tableau de valeur 
	 * @param g la grille pour accéder 
	 * @param t la taille de la grille
	 */
	private native long grilleFromTab ( int[] tab );
	
	/**
	 * @brief return les numeros des différents voisin
	 * @param g la grille pour accéder
	 * @param node le numero de la node à analyser
	 * @return un tableau contenant les 6 entiers correspondant aux voisins. NULL s'il y a eu une erreur.
	 */
	private native int[] grilleVoisinsNode ( long g, int node);
	
	/**
	 * @return la taille de la grille
	 */
	private native int grilleGetSize(long g);
	
	private boolean errorNotExist(){
		//TODO gestion des erreurs
		System.out.println("ERREUR : action sur une grille qui n'existe pas !");
		return grille == 0;
	}
	
	public void create( int t ){
		grille = grilleCreation(t);
	}
	
	public void destroy(){
		if(grille != 0)
			grilleDestruction(grille);
	}
	
	public boolean exist(){
		return grille != 0;
	}
	
	/** @return true si le pion est placé, false si impossible de placer le pion.
	 */
	public boolean ajouterPion(int l, int c, int pion){
		if(errorNotExist()){
			return false;
		}
		
		if( grilleCoupValide(grille, l, c) ){
			grilleAjouterPion(grille, l, c, pion);
			return true;
		} else {
			return false;
		}
	}
	
	public boolean coupValide(int l, int c){
		if(errorNotExist()){
			return false;
		}
		return grilleCoupValide(grille, l, c);
	}
	/** Donne la couleur du vainqueur : 0 personne, 1 RED, 2 BLU.
	 *  @return la couleur du vainqueur. -1 si la grille n'existe pas.
	 */
	public int vainqueur(){
		if(errorNotExist()){
			return -1;
		}
		return grilleVainqueur(grille);
	}
	
	/** @return la grille sous forme d'un tableau d'entier correspondant aux couleurs. null si la grille n'existe pas.
	 */
	public int[] toTab(){
		if(errorNotExist()){
			return null;
		}
		return grilleToTab(grille);
	}
	
	public String toString(){
		if(errorNotExist()){
			return null;
		}
		return grilleToString(grille);
	}
	
	/** Créer une grille à partir d'un tableau d'entier représantant les pions.
	 */
	public void createFromTab(int[] tab){
		grille = grilleFromTab(tab);
	}
	
	/** @return les numeros des cases voisine d'une case. null si la grille n'existe pas.
	 */
	public int[] voisinsNode(int node){
		if(errorNotExist()){
			return null;
		}
		return grilleVoisinsNode(grille, node);
	}
	
	/** @return la hauteur (taille) de la grille. -1 si la grille n'existe pas.
	 */
	public int getSize(){
		if(errorNotExist()){
			return -1;
		}
		return grilleGetSize(grille);
	}
	
}
