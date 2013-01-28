#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);
	if(bg.loadImage("background.png"))
	{
	
		ofSetWindowShape(bg.getWidth(), bg.getHeight());
	}
	settings.loadFile("settings.xml");
	arrows.assign(NUM_ARROW,Arrow());

	int size=50;
	for(int i = 0 ; i < NUM_ARROW ; i++)
	{
		float x = settings.getValue("POINT:X", i%12*size*1.0f ,i);
		float y = settings.getValue("POINT:Y", i/12*size*1.0f , i);
		ofLogVerbose()<<"x:"<< x <<"\ty:"<< y; 
		arrows[i].setPos(x,y);
		arrows[i].setSize(size,size);
		arrows[i].enableMouseEvents();
	}

	arrowMesh.setMode(OF_PRIMITIVE_TRIANGLES);

	
	arrowMesh.addVertex(ofVec2f(0,0));
	arrowMesh.addVertex(ofVec2f(-1,1));
	arrowMesh.addVertex(ofVec2f(0,1));
	
	
	arrowMesh.addVertex(ofVec2f(0,0));
	arrowMesh.addVertex(ofVec2f(0,1));
	arrowMesh.addVertex(ofVec2f(1,0));
	
	
	arrowMesh.addVertex(ofVec2f(0,0));
	arrowMesh.addVertex(ofVec2f(1,0));
	arrowMesh.addVertex(ofVec2f(0,-1));
	
	
	
	arrowMesh.addVertex(ofVec2f(0,-1));
	arrowMesh.addVertex(ofVec2f(-1,-1));
	arrowMesh.addVertex(ofVec2f(0,0));
	
}

//--------------------------------------------------------------
void testApp::update(){
	for(it = arrows.begin() ; it!=arrows.end() ; it++)
	{
		(*it).update();
//		if(ofGetFrameNum()%100==0)
		{
//			(*it).alpha = 255;
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	bg.draw(0, 0);
	for(it = arrows.begin() ; it!=arrows.end() ; it++)
	{
		Arrow p = (*it);
		if(bDebug)p.draw();
		ofPushMatrix();
		ofPushStyle();
		ofEnableAlphaBlending();
		ofSetColor(255, p.alpha);
		ofTranslate(p.x+p.width*0.5,p.y+p.height*0.5);
		ofScale(10, 10);
		arrowMesh.drawFaces();
		ofPopMatrix();
		ofPopStyle();
//		(*it).draw();
	}
//	ofPushMatrix();
//	ofTranslate(200, 200);
//	ofScale(100, 100);
//	arrowMesh.drawFaces();
//	ofPopMatrix();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='d')
	{
		bDebug = !bDebug;
	}
	if(key=='S')
	{
		
		for(int i = 0 ; i < NUM_ARROW ; i++)
		{
			float x = arrows[i].x;
			float y = arrows[i].y;
			settings.setValue("POINT:X",x,i);
			settings.setValue("POINT:Y",y,i);

		}
		
		
		settings.saveFile("settings.xml");
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}