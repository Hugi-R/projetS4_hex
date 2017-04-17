public class Hex{
	
	static {
		System.loadLibrary("hex");
	}
	
	public static native void helloWorld();
	
	/**
	 * @brief construction d'une grille de taille t 
	 */
	public native long grilleCreation( int t );
	
	/**
	 * @brief detruit la grille et libère la mémoire
	 */
	public native void grilleDestruction( long g);
	
	/**
	 * @brief ajoute un pion a une case
	 * 	@param g la grille pour accéder 
	 *	@param l la ligne de la case a modifier
	 *	@param c la colonne de la case a modifier
	 *	@param pion la valeur du pion ( RED ou BLU )
	 */
	public native void grilleAjouterPion( long g ,int l , int c , int pion );
	
	/**
	 * @brief verifie la validiter du coup 
	 * 	@param g la grille pour accéder 
	 *	@param l la ligne du coup a verifier
	 *	@param c la colonne du coup a verifier
	 * @return true si le coup est jouable 
	 */
	public native boolean grilleCoupValide ( long g , int l , int c );
	
	/**
	 * @brief verifie si un joueur a gagner
	 * 	@param g la grille pour accéder 
	 * @return 0 si aucun gagnant sinon retourne la valeur du gagnant : RED 1, BLU 2
	 */
	public native int grilleVainqueur ( long g);

	/**
	 * @param g la grille pour accéder 
	 * @return la grille sous forme d'un tableau, NULL s'il y a eu un problème
	 */
	public native int[] grilleToTab( long g );
	
	/**
	 * @param g la grille pour accéder 
	 * @return la grille sous forme d'un string
	 */
	public native String grilleToString (long g );
	
	/**
	 * @brief construit une grille depuis un tableau de valeur 
	 * @param g la grille pour accéder 
	 * @param t la taille de la grille
	 */
	public native long grilleFromTab ( int[] tab );
	
	/**
	 * @brief return les numeros des différents voisin
	 * @param g la grille pour accéder
	 * @param node le numero de la node à analyser
	 * @param un tableau de 6 entiers correspondant aux voisins
	 *
	 SERA AJOUTER PLUS TARD SI NECESSAIRE
	public native void grilleVoisin ( long g, int node, int[] tab );
	*/
	static public void main(String[] args){
		helloWorld();
		Hex h = new Hex();
		long grille = h.grilleCreation(5);
		System.out.println( h.grilleToString(grille) );
		
	}
}
