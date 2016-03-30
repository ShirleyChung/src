package com.theworld;

import java.lang.*;
import java.io.*;
import java.util.*;

public class World implements Runnable{

	public Map<String, Creature> creatures;

	public class Time{
		private Integer tick = new Integer(0);
		public Time(){
		}

		public Integer getTime(){ return tick;}
		public void setTime(Integer t){ tick = t;}
		public void timePass(){ tick++; }

		public void load(){
			try{
				try{
					File file = new File("time");
					if (file.exists()){
						tick = Integer.parseInt((new BufferedReader(new FileReader(file))).readLine());
					}
				}catch(FileNotFoundException e){
					tick = 0;
				}
			}catch(IOException e){
				System.out.println(e.toString());
			}
		}
		public void save(){
			try{
				(new BufferedWriter(new FileWriter(new File("file")))).write(tick.toString());
			}catch(IOException e){
				System.out.println(e.toString());
			}
		}

		public String toString(){
			return String.format("%d Year, %d.%d, %d:%d:%d", tick/31536000, (tick%31536000)/2592000 + 1, (tick%2592000)/86400 + 1, (tick%86400)/3600, (tick%3600)/60, tick%60);
		}
	}

	public Time time = new Time();

	public World(){
		time.load();
		creatures = new HashMap<String, Creature>();
	}

	public void Close(){
		time.save();
	}

	public void run(){
		Integer i = 0;
		Human newOne = new Human();
		creatures.put( (i++).toString(), newOne);
		while(true){
			time.timePass();
			System.out.println(newOne.speak());
			System.out.println(time.toString());
			try{
				Thread.sleep(1000);
			}catch(InterruptedException e){}
		}
	}
	
}