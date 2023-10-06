#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	for (int x = 120; x < ofGetWindowWidth(); x += 240) {

		for (int y = 120; y < ofGetWindowHeight(); y += 240) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

			for (float radius = 10; radius < 100; radius += 5) {

				ofMesh face, line;
				line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

				int start_deg = ofMap(ofNoise(noise_seed.x, radius * 0.01 + ofGetFrameNum() * 0.01), 0, 1, -360, 360);
				int deg_len = 60;

				color.setHsb(ofRandom(255), 255, 255);

				face.addVertex(glm::vec3());
				face.addColor(ofColor(255, 32));
				for (int deg = start_deg; deg < start_deg + deg_len; deg += 2) {

					face.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
					face.addColor(ofColor(color, 64));

					line.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
					line.addColor(color);

					if (deg != start_deg) {

						face.addIndex(0);
						face.addIndex(face.getNumVertices() - 1);
						face.addIndex(face.getNumVertices() - 2);

						line.addIndex(line.getNumVertices() - 1);
						line.addIndex(line.getNumVertices() - 2);
					}
				}

				face.draw();
				line.draw();
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}