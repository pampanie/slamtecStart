#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
//	cam.setup(640,480);
//	// imitate() will set up previous and diff
//	// so they have the same size and type as cam
//	imitate(previous, cam);
//	imitate(diff, cam);
	
	lastScanImg.allocate(1280, 960,OF_IMAGE_COLOR);
	curScanImg.allocate(1280, 960,OF_IMAGE_COLOR);
	diff.allocate(1280, 960,OF_IMAGE_COLOR);
//
	tmpFbo.allocate(1280, 960);
	
	
	
	ofBackground(0, 0, 0);
	auto sensor_list = ofxRPlidar::getDeviceList();
//	for(auto &sensor_info : sensor_list) {
//		auto sensor = make_shared<ofxRPlidar>();
//		if(sensor->connect(sensor_info.getDevicePath())) {
//			sensor->start();
//			sensors_.push_back(sensor);
//		}
//	}

	lidar = make_shared<ofxRPlidar>();
	lidar->connect(sensor_list[0].getDevicePath());
	lidar->start();
	gui.setup("settings");
	gui.add(scanRadius.set("scan radius",1,1,100));
	gui.add(diffMeanThreshold.set("diff mean threshold",0.05,0.05,1));

}

//--------------------------------------------------------------
void ofApp::update(){
//	cam.update();
//	if(cam.isFrameNew()) {
//		// take the absolute difference of prev and cam and save it inside diff
//		absdiff(cam, previous, diff);
//
//
//		diff.update();
//
//
//		// like ofSetPixels, but more concise and cross-toolkit
//		copy(cam, previous);
//
//		// mean() returns a Scalar. it's a cv:: function so we have to pass a Mat
//		diffMean = mean(toCv(diff));
//
//		// you can only do math between Scalars,
//		// but it's easy to make a Scalar from an int (shown here)
//		diffMean *= Scalar(50);
//	}
	
	auto data = lidar->scan();
//	tmpFbo.clear();
//	tmpPixels.clear();
//	curScanPixels.clear();
//	lastScanPixels.clear();
	
	tmpFbo.begin();
	ofClear(0,0);
	ofSetColor(255,0,0);

	for(auto &d : data) {
		if(d.quality > 0) {

			ofVec2f pos = ofVec2f(d.distance / scanRadius.get(), 0).getRotated(d.angle);
			ofDrawCircle(pos, 5);
		}
	}
	tmpFbo.end();
	tmpFbo.draw(0,0);
	tmpFbo.readToPixels(tmpPixels);

//	copy(curScanPixels,lastScanPixels);

	copy(curScanImg,lastScanImg);

	curScanImg.setFromPixels(tmpPixels);
//	curScanImg.setFromPixels(tmpPixels, 1280, 960, OF_IMAGE_COLOR);
	absdiff(curScanImg, lastScanImg, diff);
	diffMean = mean(toCv(diff));

	diff.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
//	ofSetColor(255);
//	cam.draw(0, 0);
//	diff.draw(640, 0);
//
//	// use the [] operator to get elements from a Scalar
//	float diffRed = diffMean[0];
//	float diffGreen = diffMean[1];
//	float diffBlue = diffMean[2];
//
//	ofSetColor(255, 0, 0);
//	ofDrawRectangle(0, 0, diffRed, 10);
//	ofSetColor(0, 255, 0);
//	ofDrawRectangle(0, 15, diffGreen, 10);
//	ofSetColor(0, 0, 255);
//	ofDrawRectangle(0, 30, diffBlue, 10);
//

	
//	auto data = lidar->scan();
//	ofPushMatrix();
//	ofTranslate(ofVec2f(ofGetWidth(), ofGetHeight())/2.f);
//	for(auto &d : data) {
//		if(d.quality > 0) {
//
//			ofVec2f pos = ofVec2f(d.distance / scanRadius.get(), 0).getRotated(d.angle);
//			ofDrawCircle(pos, 5);
//		}
//	}
//	ofPopMatrix();
////
	
//	cout << diffMean[0] << endl;
	if (diffMean[0] > diffMeanThreshold.get()) {
		ofPushMatrix();
		ofTranslate(ofVec2f(ofGetWidth(), ofGetHeight())/2.f);
		diff.draw(0,0);
		ofPopMatrix();
	}


//	curScanImg.draw(0, 0);
//	tmpFbo.draw(0,0);

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
	for(auto &s : sensors_) {
		s->stop();
		s->disconnect();
	}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
