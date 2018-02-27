#include "ofApp.h"
#include "config/Config.h"
#include "interface/TestKinectInterfaceLayout.h"
#include "interface/TestMainUIInterfaceLayout.h"
#include "tracker/KinectTracker.h"
#include "facedetector/faceplusplus/FacePlusPlusDetector.h"

using namespace bbrother;

//--------------------------------------------------------------
void ofApp::setup()
{
	config = ConfigPtr(new Config());
	ofAddListener(config->loadCompleteEvent, this, &ofApp::onConfigLoadComplete);

#ifdef DEBUG_VERSION	
	testKinectInterfaceLayout = TestInterfaceLayoutPtr(new TestKinectInterfaceLayout());
	testKinectInterfaceLayout->setPosition(ofPoint(20, 40));
	testKinectInterfaceLayout->setVisibility(true);
	ofAddListener(testKinectInterfaceLayout->InterfaceEvent, this, &ofApp::onInterfaceEvent);

	testMainUIInterfaceLayout = TestInterfaceLayoutPtr(new TestMainUIInterfaceLayout());
	testMainUIInterfaceLayout->setPosition(ofPoint(400, 40));
	testMainUIInterfaceLayout->setVisibility(true);
	ofAddListener(testMainUIInterfaceLayout->InterfaceEvent, this, &ofApp::onInterfaceEvent);

#endif

	tracker = bbrother::TrackerPtr(new KinectTracker());
	facedetector = bbrother::FaceDetectorPtr(new FacePlusPlusDetector());
	mainUI = bbrother::MainAppUIHolderPtr(new MainAppUIHolder());

	//printerWorker = bbrother::PrinterWorkerPtr(new PrinterWorker());	
	//tcpController = TcpControllerPtr(new TcpController());

	config->load();
}

//--------------------------------------------------------------
void ofApp::onConfigLoadComplete()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Config load complete");

	ofLog(ofLogLevel::OF_LOG_NOTICE, "Start application...");
}

//--------------------------------------------------------------
void ofApp::onInterfaceEvent(bbrother::InterfaceEventType& Event)
{
	switch (Event)
	{
	case InterfaceEventType::TrackingStart:
		ofLog(ofLogLevel::OF_LOG_NOTICE, "Try kinect starts...");
		break;

	case InterfaceEventType::ShowWaitScreen:
		ofLog(ofLogLevel::OF_LOG_NOTICE, "Show Wait Screen...");
		break;
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	tracker->update();
	mainUI->update();

#ifdef DEBUG_VERSION
	testKinectInterfaceLayout->update();
	testMainUIInterfaceLayout->update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
	tracker->draw();
	mainUI->draw();

#ifdef DEBUG_VERSION
	// on top level
	testKinectInterfaceLayout->draw();
	testMainUIInterfaceLayout->draw();
#endif
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
