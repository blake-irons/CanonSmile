#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(920 * 2, 768);

	auto devices = ofxCanon::listDevices();

	for (auto device : devices) {
		device->open();
		this->device = device;
		this->keyPressed(' '); //take photo
		this->device->setLiveViewEnabled(true, false);
		break;
	}

	//New
	//--------------------------------
	camWidth = 640;
	camHeight = 480;
	findHue = 0;
	findSat = 0;

	vidGrabber.setDeviceID(0);
	vidGrabber.initGrabber(camWidth, camHeight);

	finder.setup("haarcascade_smile.xml");

}

//--------------------------------------------------------------
void ofApp::update(){
	if (device) {
		device->update();

		//update live view
		{
			ofPixels liveViewPixels;
			if (this->device->getLiveView(liveViewPixels)) {
				this->previewLiveView.loadData(liveViewPixels);
				this->isLivePixelsNew = true;

				//img.setFromPixels(liveViewPixels, ofGetWidth()/2, ofGetHeight()/2, OF_IMAGE_COLOR);

				//contours.findContours(img, 1000, (ofGetHeight()*ofGetWidth()) / 3, 3, false);

				finder.findHaarObjects(liveViewPixels);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	auto rect = ofGetCurrentViewport();
	rect.width /= 2.0f;

	if (this->previewPhoto.isAllocated()) {
		this->previewPhoto.draw(rect);
		finder.draw(0, 0);
		//img.draw();
	}

	rect.x += rect.width;

	if (this->previewLiveView.isAllocated()) {
		
		this->previewLiveView.draw(rect);
		this->finder.draw(0, 0);
	}

	/*
	if(this->device) {
		stringstream status;

		{
			status << "[I]SO : \t\t" << device->getISO() << endl;
			status << "[A]perture : \t\t" << device->getAperture() << endl;
			status << "[S]hutter Speed : \t" << device->getShutterSpeed() << endl;
			status << "0 = automatic" << endl;
			status << endl;
		}

	}*/

	//.bind()


	//ofSetColor(ofColor::white);
	//ofFill();
	
	//hsb.draw(0, camHeight, 320, 240);
	//hue.draw(camWidth, 0, 320, 240);
	
	

	finder.draw(0, 0);

	contours.draw(0, 0);
	for (int i = 0; i < contours.nBlobs; i++) {
		cout << "blob " << i << ":" << contours.blobs[i].centroid << endl;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
		this->device.reset();
		this->setup();
	}

	if (!this->device) {
		return;
	}

	switch (key) {
	case ' ':
	{
		ofPixels pixels;
		if (this->device->takePhoto(pixels)) {
			this->previewPhoto.loadData(pixels);
		}
		break;
	}

	case 'i':
	case 'I':
	{
		auto result = ofSystemTextBoxDialog("Set ISO");
		if (!result.empty()) {
			auto ISO = ofToInt(result);
			device->setISO(ISO);
		}
		break;
	}
	case 'a':
	case 'A':
	{
		auto result = ofSystemTextBoxDialog("Set Aperture");
		if (!result.empty()) {
			auto aperture = ofToFloat(result);
			device->setAperture(aperture);
		}
		break;
	}
	case 's':
	case 'S':
	{
		auto result = ofSystemTextBoxDialog("Set Shutter Speed");
		if (!result.empty()) {
			auto shutterSpeed = ofToFloat(result);
			device->setShutterSpeed(shutterSpeed);
		}
		break;

	}
	default:
		break;
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
