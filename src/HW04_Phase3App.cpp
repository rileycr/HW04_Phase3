#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"
#include "Starbucks.h"
#include "rileycrStarbucks.h"
#include <iostream>
#include <fstream>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_Phase3App : public AppBasic {
public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings *settings);

private:
	rileycrStarbucks* dataTree_;
	Entry* dataFile_;
	uint8_t* dataArray_;
	Color8u locationColor;
	int windowWidth;
	int windowHeight;
};

void HW04_Phase3App::setup(){

	dataFile_ = new Entry[8000];
	ifstream in("Starbucks_2006.csv");

	for(int i = 0; i < 7655; i++){
		getline(in, dataFile_[i].identifier, ',');

		console() << dataFile_[i].identifier;

		in >> dataFile_[i].x;
		in.get();

		in >> dataFile_[i].y;
		in.get();
	}
	dataTree_ = new rileycrStarbucks();
	dataTree_ -> build(dataFile_, 7655);
}

void HW04_Phase3App::mouseDown( MouseEvent event ){

}

void HW04_Phase3App::update(){

}

void HW04_Phase3App::draw(){
	gl::clear( Color(255,255,255) );
	gl::color(Color8u(0,0,0));
	for(int i = 0; i < 7655; i++){
		gl::drawSolidCircle(Vec2f(dataFile_[i].x*windowWidth, windowHeight - dataFile_[i].y*windowHeight), 4);
	}
}

void HW04_Phase3App::prepareSettings(Settings *settings){
	windowWidth = 1300;
	windowHeight = 750;
	settings -> setWindowPos(7,29);
	settings -> setWindowSize(windowWidth, windowHeight);
	
}

CINDER_APP_BASIC( HW04_Phase3App, RendererGl )