package java_hex;
import java_hex.partie.*;

public class Tests{
	
	static public void main(String[] args){
		/*Tests t = new Tests();
		t.test_grille_tab();
		//t.test_sauvegarde();
		t.test_historique();*/
		Partie p = new Partie("partie_test");
		p.nouvelleGrille(2);
		p.jouer();
		
	}
	
	private boolean test_grille_tab(){
		Grille g = new Grille();
		int[] tabGrille = {0,0,1,0,2,0,1,0,2,0,1,2,1,0,0,0,2,0,2,2,2,0,1,0,2};
		g.createFromTab(tabGrille);
		System.out.println(g.getPointer());
		int[] retTab = g.toTab();
		boolean ok = true;
		for(int i = 0; i<25 && ok; i++){
			ok = ok && retTab[i] == tabGrille[i];
		}
		System.out.println( g.toString() );
		if(!ok){
			System.out.println("ECHEC test creation/lecture grille tab.");
		} else {
			System.out.println("SUCCES test creation/lecture grille tab.");
		}
		return ok;
	}
	
	private boolean test_sauvegarde(){
		Partie p = new Partie("partie_test");
		int[] tabGrille = {0,0,1,0,2,0,1,0,2,0,1,2,1,0,0,0,2,0,2,2,2,0,1,0,2};
		p.getGrille().createFromTab(tabGrille);
		System.out.println( p.sauvegarder() );	
		return true;
	}
	
	private void test_historique(){
		Historique h = new Historique("* 1 1o 2 3* 1 4o 2 4");
		System.out.println( h.printLast(h.size()) );
		System.out.println( h.toString() );
	}
}