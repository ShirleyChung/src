import com.theworld.*;

class testMyWorld{
	public static void main(String args[]){
		World w = new World();		
		Thread t = new Thread(w, "world");
		t.start();
		try{
			int c=100;
			while(c-->0){
				Thread.sleep(500);
			}
		}catch(InterruptedException e){
			System.out.println(e.toString());
		}

		System.out.println(w.getClass().getName());		
	}
}