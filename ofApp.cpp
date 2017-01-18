/************************************************************
************************************************************/
#include "ofApp.h"


/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _soundStream_DeviceId)
: soundStream_DeviceId(_soundStream_DeviceId)
, b_ThreadFuncFrom_AudioIn(false)
{
}

/******************************
******************************/
ofApp::~ofApp()
{
}

/******************************
******************************/
void ofApp::exit()
{
	/********************
	********************/
	try{
		/********************
		********************/
		if(MyThread.isThreadRunning()){
			MyThread.waitForThread(true); // means call stopThread() inside the function, then wait for thread to Stop.
		}
		
	}catch(...){
		printf("Thread exiting Error\n");
	}
	
	/********************
	********************/
	printf("Good bye\n");
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("theread");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnableSmoothing();
	
	/********************
	********************/
	soundStream.listDevices();
	if(soundStream_DeviceId == -1){
		printf("*.exe AudioInput\n");
		std::exit(1);
	}
	soundStream.setDeviceID(soundStream_DeviceId);
	soundStream.setup(this, 0, 1, AUDIO_SAMPLERATE, AUDIO_BUF_SIZE, AUDIO_BUFFERS);
	
	/********************
	********************/
	MyThread.startThread(true, false); 	// blocking, non verbose
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	printf("%d\n", key - '0');
	
	switch(key){
		case '0':
			b_ThreadFuncFrom_AudioIn = true;
			break;
			
		case '1':
			MyThread.lock();
			MyThread.func_1();
			MyThread.unlock();
			break;
			
		case '2':
			break;
			
		case '3':
			break;
			
		case '4':
			break;
			
		case '5':
			break;
	}
}

/******************************
******************************/
void ofApp::audioIn(float *input, int bufferSize, int nChannels)
{
	if(b_ThreadFuncFrom_AudioIn){
		b_ThreadFuncFrom_AudioIn = false;
		printf("b_ThreadFuncFrom_AudioIn\n");
		
		MyThread.lock();
		MyThread.func_0();
		MyThread.unlock();
		
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
