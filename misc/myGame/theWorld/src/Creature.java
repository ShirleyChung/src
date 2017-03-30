package com.theworld;

import java.util.*;

enum Direction{
	UP,DOWN,LEFT,RIGHT
}

public class Creature extends Thread{
	
	public class Life{
	
		private Double lifeTime;

		public Life(){
			lifeTime = new Double(100.0);
		}
		
		public void timePass(){
			lifeTime += 0.01;
		}
	

		public void setLifeTime(Double lt){ lifeTime = lt; }
		public Double getLifeTime(){ return lifeTime; }
	}
	
	private static Random ran = new Random();

	protected Life life;
	protected int xPos, yPos;

	public Creature(){
		life = new Life();
		xPos = ran.nextInt(97);
		yPos = ran.nextInt(97);
		this.start();
	}
	
	public void move(Direction dir){
		switch(dir)
		{
			case UP: yPos--;break;
			case DOWN: yPos++;break;
			case LEFT: xPos--;break;
			case RIGHT: yPos++;break;			
		}
	}
	
	public void run(){
		while(true){
			life.timePass();
			try{
				Thread.sleep(1000);
			}catch(InterruptedException e){}
		}
	}
	
	public Creature gen(){
		return new Creature();
	}
}