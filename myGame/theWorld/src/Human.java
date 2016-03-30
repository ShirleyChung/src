package com.theworld;

public class Human extends Creature implements Speakable{

	protected Language lang;

	public Human(){
		lang = new Language();
	}

	public String sayHi(){ return "Hi! i am a human"; }

	public String speak(){ 
		return String.format("I stay at (%d,%d)", xPos, yPos);
	}

	public void useLanguage(Language lang){
		this.lang = lang;
	}

}