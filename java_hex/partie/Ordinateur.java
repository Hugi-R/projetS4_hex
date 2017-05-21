package java_hex.partie;

public class Ordinateur implements IJoueurs {
	private int couleur;
	private String nom;
	
	private class Coord{
		int ligne;
		int colonne;
	}
	
	public Ordinateur( int couleur, String nom ) {
		this.couleur = couleur ;
		this.nom = nom;
	}
	
	public String getNom(){
		return nom;
	}
	
	private native int minimax ( long g , int couleur );
	
	private Coord convert(int numCase, int tailleGrille){
		Coord coord = new Coord();
		int cas = numCase ;
		coord.ligne =0;
		coord.colonne = 0 ;
		while ( cas >= tailleGrille ){
			coord.ligne += 1;
			cas -= tailleGrille;
		}
		coord.colonne = cas ;
		return coord;
	}
	
	public int action (Partie p){
		Coord coord = convert( minimax( p.getGrille().getPointer(), couleur ), p.getGrille().getSize() );
		System.out.println(nom + " joue en " + (coord.ligne+1) + " " + (coord.colonne+1));
		if( !p.coup(coord.ligne, coord.colonne, couleur) ){
			System.out.println(" Hu ho ! Quelque chose s'est mal passe, merci de contacter les developpeurs et de leurs dire \"minimax a sorti un coup invalide\".");
		}
		return 0;
	}
}

