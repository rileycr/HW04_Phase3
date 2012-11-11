#include "locationMarker.h"
locationMarker::locationMarker(Entry e, int windowWidth, int windowHeight){
	center_ = Vec2f(e.x*(windowWidth*1.065), windowHeight - e.y*(windowHeight*.96));
	color_ =  ColorA(rand() / (RAND_MAX-0.0), rand() / (RAND_MAX-0.0), rand() / (RAND_MAX-0.0), .51);
	radius_ = 4;
}

locationMarker::locationMarker(){
	center_ = Vec2f(0,0);
	color_ = Color8u(0,0,0);
	radius_ = 0;
}

void locationMarker::draw(){
	//gl::color(Color8u(255,255,255));
	//gl::drawSolidCircle(center_, radius_+1);
	gl::color(color_);
	gl::drawSolidCircle(center_, radius_);
}