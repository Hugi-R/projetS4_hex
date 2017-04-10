public class Test{
	public static native void helloWorld();
	
	static {
		System.loadLibrary("libHex");
	}
	
	static public void main(String[] args){
		helloWorld();
	}
}
