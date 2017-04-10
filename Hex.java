public class Hex{
	public static native void helloWorld();
	
	static {
		System.loadLibrary("hex");
	}
	
	static public void main(String[] args){
		helloWorld();
	}
}
