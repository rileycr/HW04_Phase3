#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"
#include "Starbucks.h"
#include "rileycrStarbucks.h"
#include "locationMarker.h"

#include <stdlib.h>
#include <stdio.h>
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
	ColorA nearestColor(int x, int y);

private:
	rileycrStarbucks* dataTree_;
	Entry* dataFile_;
	Entry* nearest_;
	uint8_t* dataArray_;
	Color8u locationColor;
	int windowWidth;
	int windowHeight;
	gl::Texture usMap_;
//	Surface* mySurface_;
//	uint8_t* nearestTint_;
	locationMarker* markerArray_;
};

void HW04_Phase3App::setup(){
	usMap_ = gl::Texture(loadImage( "usMap.png"));
	dataFile_ = new Entry[8000];
	markerArray_ = new locationMarker[7655];
//	mySurface_ = new Surface(getWindowWidth()*1.065, getWindowHeight()*.96, true);
	gl::enableAlphaBlending(true);
//	nearestTint_ = (*mySurface_).getData();
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

	for(int i = 0; i < 7655; i++){
		markerArray_[i] = locationMarker(dataFile_[i], getWindowWidth(), getWindowHeight());
	}
}

void HW04_Phase3App::mouseDown( MouseEvent event ){
	if(event.isLeft()){
		Vec2i mouse_location = event.getPos();
		double scaledXValue = mouse_location.x/(getWindowWidth()*1.065);
		double scaledYValue = (windowHeight - mouse_location.y)/(getWindowHeight()*.96);

		//Code for searching the data as an array rather than a tree to check accuracy with the
		//visual feedback.
		/*	Entry temp = dataFile_[0];
		for(int i=0; i < 7655; i++){
		if(sqrt((dataFile_[i].x-scaledXValue)*(dataFile_[i].x-scaledXValue)+
		(dataFile_[i].y-scaledYValue)*(dataFile_[i].y-scaledYValue))
		< sqrt((temp.x-scaledXValue)*(temp.x-scaledXValue)+
		(temp.y-scaledYValue)*(temp.y-scaledYValue))){
		temp = dataFile_[i];
		}
		}
		*nearest_ = temp;
		*/

		nearest_ = dataTree_ -> getNearest(scaledXValue, scaledYValue);
	} else if(event.isRight()){
		Vec2i zoom_location = event.getPos();

	}
}

void HW04_Phase3App::update(){

}

void HW04_Phase3App::draw(){
	//Draws the map
	gl::color( Color(255,255,255));
	gl::draw( usMap_, getWindowBounds() );

	//Draws the markers of the locations
	for(int i = 0; i < 7655; i++){
		markerArray_[i].draw();
	}

/*	for(int x = 0; x < getWindowWidth()*1.065; x++){
		for(int y = 0; y < getWindowHeight()*.96; y++){
			nearestTint_[3*(x + (int)(y*getWindowWidth()*getWindowHeight()*1.065))] = nearestColor(x,y).r;
			nearestTint_[3*(x + (int)(y*getWindowWidth()*getWindowHeight()*1.065))+1] = nearestColor(x,y).g;
			nearestTint_[3*(x + (int)(y*getWindowWidth()*getWindowHeight()*1.065))+2] = nearestColor(x,y).b;
			nearestTint_[3*(x + (int)(y*getWindowWidth()*getWindowHeight()*1.065))+3] = nearestColor(x,y).a;
		}
	}
*/

	//Draws the highlighted marker that is nearest to the mouse click
	if(nearest_ -> x >= 0){
		gl::color(Color8u(255,255,255));
		gl::drawSolidCircle(Vec2f(nearest_ -> x*(getWindowWidth()*1.065), 
			windowHeight - nearest_ -> y*(getWindowHeight()*.96)), 6);

		gl::color(Color8u(0,0,0));
		gl::drawSolidCircle(Vec2f(nearest_ -> x*(getWindowWidth()*1.065), 
			windowHeight - nearest_ -> y*(getWindowHeight()*.96)), 5);
	}
}

//This code was used when trying to shade the map with the color of the nearest starbucks
//it is not used now because I could not get the it to work in the draw() method
ColorA HW04_Phase3App::nearestColor(int x, int y){
	Entry* nearest = dataTree_ -> getNearest(x,y);
	for(int i = 0; i < 7655; i++){
		if(markerArray_[i].entry_ -> x == x && markerArray_[i].entry_ -> y == y)
			return ColorA(markerArray_[i].color_.r, markerArray_[i].color_.b, markerArray_[i].color_.g, .5);
	}
}

void HW04_Phase3App::prepareSettings(Settings *settings){
	windowWidth = 1300;
	windowHeight = 750;
	settings -> setWindowPos(7,29);
	settings -> setWindowSize(windowWidth, windowHeight);

}

CINDER_APP_BASIC( HW04_Phase3App, RendererGl )