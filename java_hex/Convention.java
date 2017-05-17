package java_hex;

public class Convention{
	public static final int VID = 0;
	public static final int WHI = 1;
	public static final int BLA = 2;
	
	public static final char VID_C = '.';
	public static final char BLA_C = '*';
	public static final char WHI_C = 'o';
	
	/** Donne le caractere correspondant a une couleur representee par son entier.
	 * @return le caractere de la couleur. E si couleur inconnue.
	 */
	public static char convertToChar(int x){
		switch(x){
			case VID : return VID_C;
			case BLA : return BLA_C;
			case WHI : return WHI_C;
			default  : return 'E';
		}
	}
	
	/** Donne l'entier correspondant a une couleur representee par son caractere.
	 * @return l'entier de la couleur. -1 si couleur inconnue.
	 */
	public static int convertToInt(char x){
		switch(x){
			case VID_C : return VID;
			case BLA_C : return BLA;
			case WHI_C : return WHI;
			default : return -1;
		}
	}
}
