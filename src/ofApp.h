#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxIldaFrame.h"
#include "ofxEtherdream.h"
#include "ofxInputField.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
        void updateIldaParameters();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void clearIldaFrame();
        void toggleFullScreen();
        void drawIldaText();
        void guiChanged();
    
        ofParameterGroup positionParams;
        ofParameterGroup lineParams;
        ofParameterGroup textParams;
        ofParameterGroup inputParams;
    
        ofParameter<ofVec2f> center;
        ofParameter<bool> flipX;
        ofParameter<bool> flipY;
        ofParameter<bool> capX;
        ofParameter<bool> capY;
        ofParameter<bool> drawLines;
        ofParameter<bool> drawPoints;
        ofxButton clearFrameButton;
        ofxButton fullScreenButton;
        ofParameter<ofColor> color;
        ofParameter<float> fontSize;
        ofParameter<float> kerning;
        ofParameter<int> pointCount;
        ofxTextField textField;
    
        ofxPanel gui;
    
        ofxIlda::Frame ildaFrame;   // stores and manages ILDA frame drawings
        ofxEtherdream etherdream;   // interface to the etherdream device
    
        float frameScale = 0.9;
        string currentText;
        float currentFontSize;
        float currentKerning;
        ofVec2f currentCenter;

};
