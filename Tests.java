public class Tests{
	static public void main(String[] args){
		Grille g = new Grille();
		g.create(5);
		System.out.println( g.toString() );
		
	}
	
	private boolean test_creation_grille(){
		Grille g = new Grille();
		int[] tabGrille = {0,0,1,0,2,0,1,0,2,0,1,2,1,0,0,0,2,0,2,2,2,0,1,0,2};
		g.createFromTab(tabGrille);
		int[] retTab = g.toTab();
		return true;
	}
}