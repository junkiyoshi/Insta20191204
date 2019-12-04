#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face_list.clear();
	this->frame_list.clear();

	for (int radius = 50; radius < 350; radius += 30) {

		ofMesh face, frame;
		frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

		for (int deg = 0; deg <= 360; deg += 1) {

			int index = face.getNumVertices() - 2;

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			int z = ofMap(ofNoise(glm::vec3(location * 0.005, ofGetFrameNum() * 0.005)), 0, 1, 0, radius);

			face.addVertex(glm::vec3(location, 0));
			face.addVertex(glm::vec3(location, z));

			frame.addVertex(glm::vec3(location, 0));
			frame.addVertex(glm::vec3(location, z));

			if (index > -1) {

				face.addIndex(index); face.addIndex(index + 1); face.addIndex(index + 3);
				face.addIndex(index); face.addIndex(index + 2); face.addIndex(index + 3);

				frame.addIndex(index); frame.addIndex(index + 2);
				frame.addIndex(index + 1); frame.addIndex(index + 3);
			}
		}

		this->face_list.push_back(face);
		this->frame_list.push_back(frame);
	}	
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < this->face_list.size(); i++) {

		ofSetColor(39);
		this->face_list[i].drawFaces();

		ofSetColor(239);
		this->frame_list[i].drawWireframe();		
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}