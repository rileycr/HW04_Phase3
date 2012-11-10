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
	Entry* nearest_;
	uint8_t* dataArray_;
	Color8u locationColor;
	int windowWidth;
	int windowHeight;
	gl::Texture usMap_;
};

void HW04_Phase3App::setup(){
	usMap_ = gl::Texture(loadImage( "usMap.png"));
	dataFile_ = new Entry[8000];
	ifstream in("Starbucks_2006.csv");
	nearest_ = new Entry();

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
	Vec2i mouse_location = event.getPos();
	double scaledXValue = mouse_location.x/(getWindowWidth()*1.065);
	double scaledYValue = mouse_location.y/(getWindowHeight()*.96);

	//Entry temp = dataFile_[0];
	//for(int i=0; i < 7655; i++){
	//	if(sqrt((dataFile_[i].x-scaledXValue)*(dataFile_[i].x-scaledXValue)+
	//		(dataFile_[i].y-scaledYValue)*(dataFile_[i].y-scaledYValue))
	//		< sqrt((temp.x-scaledXValue)*(temp.x-scaledXValue)+
	//		(temp.y-scaledYValue)*(temp.y-scaledYValue))){
	//			temp = dataFile_[i];
	//	}
	//}
	//*nearest_ = temp;

	nearest_ = dataTree_ -> getNearest(scaledXValue, scaledYValue);
	console() << nearest_ ->x << endl;
}

void HW04_Phase3App::update(){

}

void HW04_Phase3App::draw(){
	gl::color( Color(255,255,255));
	gl::draw( usMap_, getWindowBounds() );

	//gl::color(Color8u(255,255,255));

	if(nearest_ -> x >= 0){
		gl::drawSolidCircle(Vec2f(nearest_ -> x*getWindowWidth()*1.065, nearest_ -> y*getWindowHeight()*.96), 3);
	}
	gl::color(Color8u(0,0,0));
	for(int i = 0; i < 7655; i++){
		gl::drawSolidCircle(Vec2f(dataFile_[i].x*(getWindowWidth()*1.065),
			windowHeight - dataFile_[i].y*(getWindowHeight()*.96)), 1);
	}
}

void HW04_Phase3App::prepareSettings(Settings *settings){
	windowWidth = 1300;
	windowHeight = 750;
	settings -> setWindowPos(7,29);
	settings -> setWindowSize(windowWidth, windowHeight);

}

CINDER_APP_BASIC( HW04_Phase3App, RendererGl )