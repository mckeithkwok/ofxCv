#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
	finder.setup("haarcascade_frontalface_alt2.xml");
	finder.setPreset(ObjectFinder::Fast);
	cam.initGrabber(640, 480);
	sunglasses.loadImage("sunglasses.png");
	ofEnableAlphaBlending();
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		finder.update(cam);
	}
}

void testApp::draw() {
	cam.draw(0, 0);
	
	for(int i = 0; i < finder.size(); i++) {
		ofRectangle object = finder.getObject(i);
		sunglasses.setAnchorPercent(.5, .5);
		float scaleAmount = .85 * object.width / sunglasses.getWidth();
		ofPushMatrix();
		ofTranslate(object.x + object.width / 2., object.y + object.height * .42);
		ofScale(scaleAmount, scaleAmount);
		sunglasses.draw(0, 0);
		ofPopMatrix();
	}
}
