#include "ofApp.h"
#include "hershey/futural.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    gui.setup("Dynamograma"); // most of the time you don't need a name but don't forget to call setup
    
    positionParams.setName("POSITION");
    positionParams.add(center.set("center",ofVec2f(0.5,0.5),ofVec2f(0,0),ofVec2f(1,1)));
    positionParams.add(flipX.set("flip X", true));
    positionParams.add(flipY.set("flip Y", true));
    positionParams.add(capX.set("cap X", true));
    positionParams.add(capY.set("cap Y", true));
    gui.add(positionParams);
    
    lineParams.setName("LINE PARAMETERS");
    lineParams.add(color.set("color",ofColor(255,255,255),ofColor(0,0),ofColor(255,255)));
    lineParams.add(drawLines.set("draw lines",true));
    lineParams.add(drawPoints.set("draw points",true));
    lineParams.add(pointCount.set("adjust point count",50,10,200));
    gui.add(lineParams);
    
    inputParams.setName("INPUT");
    gui.add(inputParams);
    gui.add(textField.setup("TEXT", " "));
    gui.add(clearFrameButton.setup("clear frame"));
    
    textParams.setName("TEXT PARAMETERS");
    textParams.add(fontSize.set("font size", 0.5, 0, 1));
    textParams.add(kerning.set("kerning", 0.1, 0, 0.2));
    gui.add(textParams);
    
    gui.add(fullScreenButton.setup("fullscreen"));
    
    clearFrameButton.addListener(this,&ofApp::clearIldaFrame);
    fullScreenButton.addListener(this,&ofApp::toggleFullScreen);
    
    gui.loadFromFile("settings.xml");
    
    currentText = textField.getParameter().toString();
    currentCenter = center.get();
    currentFontSize = fontSize.get();
    currentKerning = kerning.get();
    
    #ifdef DEBUG
    etherdream.setup();
    etherdream.setPPS(30000);
    #endif
    
    updateIldaParameters();
    drawIldaText();
}

//--------------------------------------------------------------
void ofApp::exit(){
    clearFrameButton.removeListener(this,&ofApp::clearIldaFrame);
    fullScreenButton.removeListener(this,&ofApp::toggleFullScreen);
    gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

void ofApp::toggleFullScreen() {
    ofToggleFullscreen();
}

void ofApp::clearIldaFrame() {
    ildaFrame.clear();
}


void ofApp::guiChanged() {
    
}

void ofApp::updateIldaParameters() {
    ildaFrame.params.output.transform.doFlipX = flipX.get();
    ildaFrame.params.output.transform.doFlipY = flipY.get();
    ildaFrame.params.output.doCapX = capX.get();
    ildaFrame.params.output.doCapY = capY.get();
    ildaFrame.params.output.color = color.get();
    ildaFrame.params.draw.lines = drawLines.get();
    ildaFrame.params.draw.points = drawPoints.get();
    ildaFrame.polyProcessor.params.targetPointCount = pointCount.get();
    /*ildaFrame.params.output.transform.offset.y = center.get().
    ildaFrame.params.output.transform.offset.x
     ildaFrame.params.output.transform.scale.y
     ildaFrame.params.output.transform.scale.x*/
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    
    // Draw ILDA frame zone
    ofNoFill();
    ofSetColor(50, 160, 255);
    
    ofDrawRectangle(ofGetWidth()/2-ofGetHeight()*frameScale/2, ofGetHeight()/2-ofGetHeight()*frameScale/2, ofGetHeight()*frameScale, ofGetHeight()*frameScale);
    ofSetLineWidth(0.5);
    ofDrawLine(ofGetWidth()/2, ofGetHeight()/2-ofGetHeight()*frameScale/2, ofGetWidth()/2, ofGetHeight()/2+ofGetHeight()*frameScale/2);
    ofDrawLine(ofGetWidth()/2-ofGetHeight()*frameScale/2, ofGetHeight()/2,ofGetWidth()/2+ofGetHeight()*frameScale/2, ofGetHeight()/2);
    ofSetColor(color);
    ofSetLineWidth(2);
    
#pragma mark ILDA DRAWING

    updateIldaParameters();
    
    // check if parameters changed
    if (textField.getParameter().toString().compare(currentText) != 0) {
        // String changed
        currentText = textField.getParameter().toString();
        drawIldaText();
    }
    
    ildaFrame.update();
    ildaFrame.draw(ofGetWidth()/2-ofGetHeight()*frameScale/2, ofGetHeight()/2-ofGetHeight()*frameScale/2, ofGetHeight()*frameScale, ofGetHeight()*frameScale);
    
    #ifdef DEBUG
    etherdream.setPoints(ildaFrame);
    #endif
    
    gui.draw();
}

void ofApp::drawIldaText() {
    string v = currentText;
    ildaFrame.clear();
    float fontScale =fontSize.get()/100;
    
    //calculate total width of string
    float totalWidth = 0;
    for (int i = 0;i<v.size();i++) {
        totalWidth += futural_realwidth[v.at(i)-32];
    }
    totalWidth = totalWidth*fontScale+kerning.get()*(v.size()-1);
    
    // start letter routine;
    float letterOffset = center.get().x-totalWidth/2;
    for (int i = 0;i<v.size();i++) {
        int letter_index = v.at(i)-32;
        
        int letter_size = futural_size[letter_index];
        int letter_width = futural_width[letter_index];
        int letter_realwidth = futural_realwidth[letter_index];
        int letter_height = futural_height;
        const int *letter_points = futural[letter_index];
        
        for (int i = 0;i<letter_size;i+=4) {
            ildaFrame.addPoly();
            ildaFrame.getLastPoly().lineTo(float(letter_points[i])*fontScale+letterOffset,float(letter_points[i+1])*fontScale+center.get().y);
            ildaFrame.getLastPoly().lineTo(float(letter_points[i+2])*fontScale+letterOffset,float(letter_points[i+3])*fontScale+center.get().y);
        }
        letterOffset += letter_realwidth*fontScale+kerning.get();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        // draw rectangle
        case 'r': {
            ofPolyline p = ofPolyline::fromRectangle(ofRectangle(ofRandomuf()/2, ofRandomuf()/2, ofRandomuf()/2, ofRandomuf()/2));
            ildaFrame.addPoly(p);
        }
            break;
            
        case 'C': ildaFrame.drawCalibration(); break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // draw a line to the mouse cursor (normalized coordinates) in the last poly created
    //ildaFrame.getLastPoly().lineTo(x / (float)ofGetWidth(), y / (float)ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // create a new poly in the ILDA frame
    //ildaFrame.addPoly();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    //screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
