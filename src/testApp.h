#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxDraggable.h"
#define NUM_ARROW 48
class Arrow : public ofxDraggable
{
public:
	Arrow()
	{
		alpha=255;
	}
	void draw()
	{
		ofPushStyle();
		if(isMouseDown()) {
			ofNoFill();
			ofSetHexColor(0xFF0000);
			ofRect(x, y, width, height);
		} else if(isMouseOver()){
			ofNoFill();
			ofSetHexColor(0x00FF00);
			ofRect(x, y, width, height);
		}
	ofPopStyle();
	}
	void begin()
	{
		
	}
	void end()
	{
		
	}
	void update()
	{
		if(alpha >0)alpha-=2;
	}
void onRollOver(int x, int y)
{
	alpha=255;
}
	float alpha;
	
	
};
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	vector<Arrow> arrows;
	vector<Arrow>::iterator it;
	ofImage bg;
	ofMesh arrowMesh;
	ofxXmlSettings settings;
	bool bDebug;
};
