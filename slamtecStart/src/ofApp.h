#pragma once

#include "ofMain.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	ofVideoGrabber cam;
	ofPixels previous;
	ofImage diff;
	
	// a scalar is like an ofVec4f but normally used for storing color information
	cv::Scalar diffMean;
	
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
	
};
