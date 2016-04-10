#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxIldaFrame.h"
#include "ofxEtherdream.h"
#include "ofxInputField.h"

class ofApp : public ofBaseApp {

	public:
    
        vector<string> sentences;
    
		void setup();
		void update();
		void draw();
        void exit();
        
		void keyPressed(int key);
		void windowResized(int w, int h);
		void toggleFullScreen();
        void clearIldaFrame();
        void updateIldaParameters();
        void drawIldaText();
        void switchText(int sentenceIndex, int wordIndex);
    
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
        ofColor currentColor;
        int currentSentence;
        int currentWord;
};
