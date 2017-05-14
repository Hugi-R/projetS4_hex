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
		
		for(ListIterator<String> it = historique.listIterator(historique.size()); it.hasPrevious() && n>0; n--){
			ret += it.previous() + '\n';
		}
		
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
}
