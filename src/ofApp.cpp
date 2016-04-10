#include "ofApp.h"
#include "hershey/futural.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    sentences.reserve(38);
    sentences.push_back("DYNAMOGRAMA");
    sentences.push_back("ECHANTILLONER");
    sentences.push_back("BOUTON SAMBA PROBABLEMENT");
    sentences.push_back("SPIDERMAN");
    sentences.push_back("NANANI NANA");
    sentences.push_back("CYNIQUE");
    sentences.push_back("TRAUMA ORDINAIRE");
    sentences.push_back("EFFACER L'HISTORIQUE");
    sentences.push_back("TEMPS HISTORIQUE");
    sentences.push_back("SIGNAL");
    sentences.push_back("MONDE SANS NOUS");
    sentences.push_back("NOUS SANS MONDE");
    sentences.push_back("4.5 MILLIARDS D'ANNEES");
    sentences.push_back("10 MILLIARDS D'ANNEES");
    sentences.push_back("PROBLEME DE L'ANCESTRALITE");
    sentences.push_back("TEMPS GEOLOGIQUES");
    sentences.push_back("PERSONNE DANS L'OEIL DU CYCLONE");
    sentences.push_back("LES DIEUX");
    sentences.push_back("LES LIEUX");
    sentences.push_back("LES FOSSILES");
    sentences.push_back("FUSION");
    sentences.push_back("AMIBES");
    sentences.push_back("BACTERIES");
    sentences.push_back("SIGNE");
    sentences.push_back("DRONE");
    sentences.push_back("ECHELLE MOLECULAIRE");
    sentences.push_back("RELATION MEDIATIQUE");
    sentences.push_back("MEDIAS DU MONDE");
    sentences.push_back("SELFIE");
    sentences.push_back("CONNEXION");
    sentences.push_back("MIROIR");
    sentences.push_back("OBJET");
    sentences.push_back("SUJET");
    sentences.push_back("IMAGE");
    sentences.push_back("METAXU");
    sentences.push_back("NOS ANCETRES LES COMETES");
    sentences.push_back("----------");
    sentences.push_back("DYNAMOGRAMA");
    
    currentSentence = -1;
    currentWord = 0;
    
    gui.setup("Dynamograma");
    
    gui.add(fullScreenButton.setup("fullscreen"));
    
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
    lineParams.add(pointCount.set("adjust point count",50,10,800));
    gui.add(lineParams);
    
    textParams.setName("TEXT PARAMETERS");
    textParams.add(fontSize.set("font size", 0.5, 0, 1));
    textParams.add(kerning.set("kerning", 0.1, 0, 0.2));
    gui.add(textParams);
    
    inputParams.setName("INPUT");
    gui.add(inputParams);
    gui.add(clearFrameButton.setup("clear frame"));
    gui.add(textField.setup("TEXT", " "));
    
    clearFrameButton.addListener(this,&ofApp::clearIldaFrame);
    fullScreenButton.addListener(this,&ofApp::toggleFullScreen);
    
    gui.loadFromFile("settings.xml");
    
    textField.getParameter().fromString("");
    
    currentText = textField.getParameter().toString();
    currentCenter = center.get();
    currentFontSize = fontSize.get();
    currentKerning = kerning.get();
    currentColor = color.get();
    
    //etherdream.setup();
    //etherdream.setPPS(30000);
    
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
    textField.getParameter().fromString("");
    //gui.add(textField.setup("TEXT", " "));
    ildaFrame.clear();
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

void ofApp::switchText(int sentenceIndex, int wordIndex) {
    string v = sentences.at(sentenceIndex);
    istringstream iss(v);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
    textField.getParameter().fromString(tokens.at(wordIndex));
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
    
    if (center.get().x != currentCenter.x || center.get().y != currentCenter.y ||
        fontSize.get() != currentFontSize || kerning.get() != currentKerning ||
        color.get().r != currentColor.r || color.get().g != currentColor.g || color.get().b != currentColor.b) {
        currentCenter = center.get();
        currentFontSize = fontSize.get();
        currentKerning = kerning.get();
        currentColor = color.get();
        drawIldaText();
    }
    
    if (textField.getParameter().toString().compare(currentText) != 0) {
        // String changed
        currentText = textField.getParameter().toString();
        drawIldaText();
    }
    
    ildaFrame.update();
    ildaFrame.draw(ofGetWidth()/2-ofGetHeight()*frameScale/2, ofGetHeight()/2-ofGetHeight()*frameScale/2, ofGetHeight()*frameScale, ofGetHeight()*frameScale);
    
    //etherdream.setPoints(ildaFrame);
    
    gui.draw();
}

void ofApp::drawIldaText() {
    string v = currentText;
    ildaFrame.clear();
    float fontScale =currentFontSize/100;
    
    //calculate total width of string
    float totalWidth = 0;
    for (int i = 0;i<v.size();i++) {
        totalWidth += futural_realwidth[v.at(i)-32];
    }
    totalWidth = totalWidth*fontScale+currentKerning*(v.size()-1);
    
    // start letter routine;
    float letterOffset = currentCenter.x-totalWidth/2;
    for (int i = 0;i<v.size();i++) {
        int letter_index = v.at(i)-32;
        
        int letter_size = futural_size[letter_index];
        int letter_width = futural_width[letter_index];
        int letter_realwidth = futural_realwidth[letter_index];
        int letter_height = futural_height;
        const int *letter_points = futural[letter_index];
        
        for (int i = 0;i<letter_size;i+=4) {
            ildaFrame.addPoly();
            ildaFrame.getLastPoly().lineTo(float(letter_points[i])*fontScale+letterOffset,float(letter_points[i+1])*fontScale+currentCenter.y);
            ildaFrame.getLastPoly().lineTo(float(letter_points[i+2])*fontScale+letterOffset,float(letter_points[i+3])*fontScale+currentCenter.y);
        }
        letterOffset += letter_realwidth*fontScale+currentKerning;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'C': ildaFrame.drawCalibration(); break;
        case 'a' :
            if (currentSentence+1 < sentences.size()) {
                currentSentence++;
            } else {
                currentSentence = 0;
            }
            currentWord = 0;
            switchText(currentSentence,currentWord);
            break;
        case 'q' :
            if (currentSentence > 0) {
                currentSentence--;
            } else {
                currentSentence = sentences.size()-1;
            }
            currentWord = 0;
            switchText(currentSentence,currentWord);
            break;
        case 'z':
            string v = sentences.at(currentSentence);
            istringstream iss(v);
            vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
            if (currentWord+1 < tokens.size()) {
                currentWord++;
            } else {
                currentWord = 0;
            }
            switchText(currentSentence,currentWord);
            break;
        //case 'b': switchText(currentSentence,currentWord); break;
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}
