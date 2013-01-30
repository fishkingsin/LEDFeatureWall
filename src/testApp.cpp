#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);
	if(bg.loadImage("background.png"))
	{
		
		ofSetWindowShape(bg.getWidth(), bg.getHeight()*2);
	}
	settings.loadFile("settings.xml");
	
	
	arrowMesh.setMode(OF_PRIMITIVE_TRIANGLES);
	
	arrowMesh.addVertex(ofVec2f(0,0));
	arrowMesh.addVertex(ofVec2f(-1,-1));
	arrowMesh.addVertex(ofVec2f(1,0));
	
	
	arrowMesh.addVertex(ofVec2f(0,0));
	arrowMesh.addVertex(ofVec2f(-1,1));
	arrowMesh.addVertex(ofVec2f(1,0));
	
	
	//	arrowMesh.addVertex(ofVec2f(0,0));
	//	arrowMesh.addVertex(ofVec2f(-1,1));
	//	arrowMesh.addVertex(ofVec2f(1,0));
	
	//	arrowMesh.addVertex(ofVec2f(0,0));
	//	arrowMesh.addVertex(ofVec2f(-1,1));
	//	arrowMesh.addVertex(ofVec2f(0,1));
	//
	//
	//	arrowMesh.addVertex(ofVec2f(0,0));
	//	arrowMesh.addVertex(ofVec2f(0,1));
	//	arrowMesh.addVertex(ofVec2f(1,0));
	//
	//
	//	arrowMesh.addVertex(ofVec2f(0,0));
	//	arrowMesh.addVertex(ofVec2f(1,0));
	//	arrowMesh.addVertex(ofVec2f(0,-1));
	//
	//
	//
	//	arrowMesh.addVertex(ofVec2f(0,-1));
	//	arrowMesh.addVertex(ofVec2f(-1,-1));
	//	arrowMesh.addVertex(ofVec2f(0,0));
	int port = 12000;
	for(int i = 0 ; i< NUM_TSPS ; i++)
	{
		tspsReceiver[i].connect(port+i);
	}
    
    // this will add listeners to your app; this is optional!
    // you will need to add all three of these functions to do this:
    // void onPersonEntered( ofxTSPS::EventArgs & tspsEvent );
    // void onPersonUpdated( ofxTSPS::EventArgs & tspsEvent );
    // void onPersonWillLeave( ofxTSPS::EventArgs & tspsEvent );
    
    ofxAddTSPSListeners(this);
	
	gui.ofxControlPanel::setup("Control Panel", 0, 0, settings.getValue("GUI_WIDTH",bg.getWidth()),settings.getValue("GUI_HEIGHT",bg.getHeight()*2));
	//gui.setup(settings.getValue("GUI_WIDTH",ofGetWidth()),settings.getValue("GUI_HEIGHT",ofGetHeight()*0.5));
	gui.loadFont(settings.getValue("GUI_FONT","MONACO.TTF"),settings.getValue("GUI_FONT_SIZE",8));
	gui.ofxControlPanel::addPanel("General", 4);
	gui.addToggle("Debug", "DEBUG", false);
	gui.ofxControlPanel::addPanel("TrackingInput", 4);
	gui.setWhichPanel("TrackingInput");
	for(int i =0 ; i < NUM_TSPS ; i++)
	{
		gui.setWhichColumn(i);
		gui.addSlider2D("inputPosition", "INPUT_POSITION_"+ofToString(i), input[i].x, input[i].y,0,bg.getWidth() ,0,bg.getHeight(),true);
		gui.addSlider2D("inputSize", "INPUT_SIZE_"+ofToString(i), input[i].width, input[i].height,0,bg.getWidth(),0,bg.getHeight(),true);
	}
	
	gui.ofxControlPanel::addPanel("TrackingOutput", 2);
	gui.setWhichPanel("TrackingOutput");
	gui.setWhichColumn(0);
	gui.addSlider2D("outputPosition", "OUTPUT_POSITION",output.x,output.y,0,bg.getWidth(),0,bg.getHeight(),true);
	gui.addSlider2D("outputSize", "OUTPUT_SIZE", output.width,output.height,0,bg.getWidth(),0,bg.getHeight(),true);
	
	gui.ofxControlPanel::addPanel("DebugDraw", 1);
	gui.setWhichPanel("DebugDraw");
	gui.setWhichPanel("DebugDraw");
	gui.setWhichColumn(0);
	gui.addCustomRect("Debug Drawer", &drawer, gui.getWidth()*0.8, gui.getHeight()*0.8);
	
	//  -- this gives you back an ofEvent for all events in this control panel object
	ofAddListener(gui.guiEvent, this, &testApp::eventsIn);
	gui.setupEvents();
	gui.enableEvents();
	gui.loadSettings(settings.getValue("GUI_SETTING_PATH","./settings/control_settings.xml"));
	oldOutput = output;
	arrows.assign(NUM_ARROW,Arrow());
	
	arrowSize=settings.getValue("SIZE",30);
	for(int i = 0 ; i < NUM_ARROW ; i++)
	{
		float x = settings.getValue("POINT:X", (i%12*arrowSize)/(50.0*NUM_ARROW) ,i);
		float y = settings.getValue("POINT:Y", (i/12*arrowSize)/(50.0*NUM_ARROW), i);
		ofLogVerbose()<<"x:"<< x <<"\ty:"<< y;
		//		arrows[i].setPos(x*output.width,y*output.height);
		arrows[i].setPos(x*output.width+output.x,y*output.height+output.y);
		arrows[i].setSize(arrowSize*2,arrowSize*2);
		arrows[i].enableMouseEvents();
		arrows[i].index = i;
	}
}
//--------------------------------------------------------------
void testApp::onPersonEntered( ofxTSPS::EventArgs & tspsEvent ){
    ofLog(OF_LOG_NOTICE, "New person!");
    // you can access the person like this:
    // tspsEvent.person
}

//--------------------------------------------------------------
void testApp::onPersonUpdated( ofxTSPS::EventArgs & tspsEvent ){
    ofLog(OF_LOG_NOTICE, "Person updated!");
	
	//	ofRectangle rect = tspsEvent.person->boundingRect;
	//	rect.x=input.x+(rect.x*input.width);
	//	rect.width*=input.width;
	//	rect.y=input.y+(rect.y*input.height);
	//	rect.height*=input.height;
	//	ofLogVerbose("onPersonUpdated")<<rect.x<<endl
	//	<<rect.y<<endl
	//	<<rect.width<<endl
	//	<<rect.height<<endl;
	//	for(it = arrows.begin() ; it!=arrows.end() ; it++)
	//	{
	//		Arrow *p = &(*it);
	//
	//		if (rect.inside(p->x+p->width*0.5,p->y+p->height*0.5)) {
	//			p->alpha = 255;
	//		}
	//	}
}

//--------------------------------------------------------------
void testApp::onPersonWillLeave( ofxTSPS::EventArgs & tspsEvent ){
    ofLog(OF_LOG_NOTICE, "Person left!");
    // you can access the person like this:
    // tspsEvent.person
    
}
void testApp::eventsIn(guiCallbackData & data)
{
	if( data.isElement( "DEBUG" ) ){
		bDebug = data.getInt(0);
		toggleDebug();
	}
	for(int i = 0 ; i < NUM_TSPS ;i++)
	{
		if(data.isElement( "INPUT_POSITION_"+ofToString(i) ))
		{
			input[i].x = data.getInt(0);
			input[i].y = data.getInt(1);
		}
		if(data.isElement( "INPUT_SIZE_"+ofToString(i) ))
		{
			input[i].width = data.getInt(0);
			input[i].height = data.getInt(1);
		}
	}
	if(data.isElement( "OUTPUT_POSITION" ))
	{
		
		output.x = data.getInt(0);
		output.y = data.getInt(1);
		
	}
	if(data.isElement( "OUTPUT_SIZE" ))
	{
		
		output.width = data.getInt(0);
		output.height = data.getInt(1);
	}
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
	for(int i = 0; i < NUM_TSPS ; i++)
	{
		vector<ofxTSPS::Person*> people = tspsReceiver[i].getPeople();
		for ( int j=0; j<people.size(); j++){
			
			ofRectangle rect = people[j]->boundingRect;
			rect.x		=	input[i].x+(rect.x*input[i].width);
			rect.width	*=	input[i].width;
			rect.y		=	input[i].y+(rect.y*input[i].height);
			rect.height	*=	input[i].height;
//			ofLogVerbose("onPersonUpdated")<<rect.x<<endl
//			<<rect.y<<endl
//			<<rect.width<<endl
//			<<rect.height<<endl;
			for(it = arrows.begin() ; it!=arrows.end() ; it++)
			{
				Arrow *p = &(*it);

				if (rect.inside(p->x+p->width*0.5,p->y+p->height*0.5)) {
					p->alpha = 255;
				}
			}

		}
	}
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
	bg.draw(0, 0);
	ofPushMatrix();
	for(it = arrows.begin() ; it!=arrows.end() ; it++)
	{
		Arrow p = (*it);
		if(bDebug)p.draw();
		ofPushMatrix();
		ofPushStyle();
		ofEnableAlphaBlending();
		
		
		ofTranslate(p.x+p.width*0.5,p.y+p.height*0.5);
		{
			ofPushMatrix();
			ofTranslate(-1.5, 0);
			ofScale(arrowSize+3, arrowSize+3	);
			ofPushStyle();
			ofNoFill();
			ofSetColor(255, p.alpha);
			arrowMesh.drawFaces();
			ofPopStyle();
			ofPopMatrix();
		}
		
		ofScale(arrowSize, arrowSize);
		ofPushStyle();
		ofFill();
		ofSetColor(ofColor::black);
		arrowMesh.drawFaces();
		ofPopStyle();
		
		
		ofPopStyle();
		ofPopMatrix();
		
	}
	ofPopMatrix();
	if(bDebug)
	{
		
		ofPushStyle();
		ofSetColor(ofColor::green);
		ofNoFill();
		ofRect(output);
		ofPopStyle();
		
		for(int i = 0 ; i< NUM_TSPS ; i++)
		{
			ofPushStyle();
			ofNoFill();
			ofSetColor(ofColor::red);
			ofRect(input[i]);
			ofPopStyle();
			ofPushMatrix();
			ofTranslate(input[i].x, input[i].y);
			
			tspsReceiver[i].draw(input[i].width,input[i].height);
			
			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='d')
	{
		bDebug = !bDebug;
		gui.setValueB("DEBUG", bDebug);
		toggleDebug();
	}
	if(key=='S')
	{
		
		for(int i = 0 ; i < NUM_ARROW ; i++)
		{
			float x = arrows[i].x;
			float y = arrows[i].y;
			settings.setValue("POINT:X",(x-output.x)/output.width,i);
			settings.setValue("POINT:Y",(y-output.y)/output.height,i);
			
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
	if(!gui.hidden)
	{
		ofPoint diff = ofPoint(output.x-oldOutput.x,output.y-oldOutput.y);
		for(it = arrows.begin() ; it!=arrows.end() ; it++)
		{
			Arrow *p = &(*it);
			p->x+=diff.x;
			p->y+=diff.y;
		}
		oldOutput = output;
	}
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
void testApp::toggleDebug()
{
	
	
	if(bDebug)
	{
		
		ofSetLogLevel(OF_LOG_VERBOSE);
	}
	else
	{
		ofSetLogLevel(OF_LOG_SILENT);
	}
	
}