public class Convention{
	public static final int VID = 0;
	public static final int RED = 1;
	public static final int BLU = 2;
	
	public static final char VID_C = '.';
	public static final char RED_C = '*';
	public static final char BLU_C = 'o';
	
	/** Donne le caractere correspondant a une couleur representee par son entier.
	 * @return le caractere de la couleur. E si couleur inconnue.
	 */
	public static char convertToChar(int x){
		switch(x){
			case VID : return VID_C;
			case RED : return RED_C;
			case BLU : return BLU_C;
			default  : return 'E';
		}
	}
	
	/** Donne l'entier correspondant a une couleur representee par son caractere.
	 * @return l'entier de la couleur. -1 si couleur inconnue.
	 */
	public static int convertToInt(char x){
		switch(x){
			case VID_C : return VID;
			case RED_C : return RED;
			case BLU_C : return BLU;
			default : return -1;
		}
	}
}
