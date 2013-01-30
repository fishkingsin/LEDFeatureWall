//
//  debugDrawer.h
//  LEDFeatureWall
//
//  Created by james KONG on 29/1/13.
//
//
#pragma once
#include "guiCustomImpl.h"
#include "guiBaseObject.h" //theo added for isInsideRect()

class debugDrawer : public guiCustomImpl {
	
private:
	
		
public:
	bool mouseIsRelative;
	//ofRectangle boundingRect; //theo changed
	
	debugDrawer(){
		
	}
	
	// -------------------------------------
	void saveSettings(string filename){
	}
	
	void reloadSettings(){
		
	}
	
	void saveSettings(){
		
	}
	
	void loadSettings(string filename) {
		
	}
	
	// -------------------------------------
	float getWidth() {
		return boundingRect.width;
	}
	float getHeight() {
		return boundingRect.height;
	}
	
	// -------------------------------------
	void clearPoints() {
		
	}
	
	// -------------------------------------
	void addPoint(float x, float y) {
		
	}
	
	void draw(float x, float y, float w, float h) {
		
		
	}
	
	// -------------------------------------
	void mousePressed(float x, float y) {
		
	}
	
	//these values come in with 0,0 being the top left of your bounding rect
	// -------------------------------------
	void mouseDragged(float x, float y){
		
		//theo changed
		
		if( isInsideRect(x, y, ofRectangle(0, 0, boundingRect.width, boundingRect.height) ) ){
		}
	}
	
	void mouseReleased(){
		
	}
};
