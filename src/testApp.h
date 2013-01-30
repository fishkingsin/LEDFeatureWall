#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxDraggable.h"
#include "ofxTSPSReceiver.h"
#include "ofxAutoControlPanel.h"
#include "debugDrawer.h"
#define NUM_ARROW 72
#define NUM_TSPS 4
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
		else
		{
			ofNoFill();
			ofSetHexColor(0xAAAAAA);
			ofRect(x, y, width, height);
		}
		ofPopStyle();
		ofDrawBitmapString(ofToString(index), x+8,y+8);
	}
	void begin()
	{
		
	}
	void end()
	{
		
	}
	void update()
	{
		if(alpha >0)alpha-=5;
	}
	void onRollOver(int x, int y)
	{
		alpha=255;
	}
	float alpha;
	ofPoint normPt;
	int index;
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
	int arrowSize;
	ofxXmlSettings settings;
	bool bDebug;
	
	ofxTSPS::Receiver tspsReceiver[NUM_TSPS];
    
	// event listeners
	void onPersonEntered( ofxTSPS::EventArgs & tspsEvent );
	void onPersonUpdated( ofxTSPS::EventArgs & tspsEvent );
	void onPersonWillLeave( ofxTSPS::EventArgs & tspsEvent );
	
	
	ofxAutoControlPanel gui;
		void eventsIn(guiCallbackData & data);
	ofRectangle input[NUM_TSPS];
	ofRectangle output,oldOutput;
	debugDrawer drawer;
	void toggleDebug();
	
	
};
