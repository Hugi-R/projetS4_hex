package java_hex.partie;
import java.util.*;

public class Historique{
	private List<String> historique;
	
	public Historique(){
		historique = new ArrayList<String>();
	}
	
	public Historique(String hist){
		historique = fromString(hist);
	}
	
	public void add(char j, int l, int c){
		String s = j + " " + l + " " + c;
		historique.add(s);
	}
	
	public int size(){
		return historique.size();
	}
	
	public String toString(){
		String ret = "";
		
		for( String s : historique ){
			ret += s;
		}
		
		return ret;
	}
	
	public String printLast(int n){
		String ret = "";
		int i = 0;
		for(ListIterator<String> it = historique.listIterator(0); it.hasNext() && i<n; i++){
			ret += i + " : " + it.next() + '\n';
		}
		if (ret.equals(""))
			return "historique vide";
		return ret;
	}
	
	private List<String> fromString(String s){
		List<String> l = new ArrayList<String>();
		String[] hist = s.split("(?<=([o*].{4}))");
		for( String item : hist ){
			l.add(item);
		}
		
		return l;
	}
	
	/**
	 * Renvoit le dernier joueur à avoir jouer
	 */
	public int dernierJoueur(){
		if(historique.size() == 0){
			return 1;
		} else {
			String s = historique.get( historique.size()-1 );
			if(s.charAt(0) == '*' )
				return 2;
			else
				return 1;
		}
	}
	
	/**
	 * Supprime les n dernier ajout a l'historique
	 */
	public void supprDerniers(int n){
		if( n>this.size() ) n = this.size();
		for( int i = 0; i<n; i++)
			historique.remove( historique.size()-1 );
	}
	
	/**
	 * Creer une nouvelle grille a partir de l'historique
	 */
	public Grille grilleFromHistorique(int sizeGrille){
		Grille g = new Grille();
		g.create(sizeGrille);
		
		for( String s : historique ){
			String[] ss = s.split(" ");
			if( ss[0].equals("o") ){
				g.ajouterPion( Integer.parseInt(ss[1]), Integer.parseInt(ss[2]), 1 );
			} else {
				g.ajouterPion( Integer.parseInt(ss[1]), Integer.parseInt(ss[2]), 2 );
			}
		}
		
		return g;
	}
}
