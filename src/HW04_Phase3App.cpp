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

private:
	Surface* mySurface_;
	rileycrStarbucks* dataTree_;
	static const int kAppWidth = 800;
	static const int kAppHeight = 600;
	static const int kTextureSize = 1024;
};

void HW04_Phase3App::setup(){
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	uint8_t* dataArray = (*mySurface_).getData();

	Entry* dataFile = new Entry[8000];
	ifstream in("Starbucks_2006.csv");

	for(int i = 0; i < 7655; i++){
		getline(in, dataFile[i].identifier, ',');

		in >> dataFile[i].x;
		in.get();

		in >> dataFile[i].y;
		in.get();

		cout << dataFile[i].identifier << " " << dataFile[i].x << " " << dataFile[i].y << endl;
	}
	dataTree_ = new rileycrStarbucks();
	dataTree_ -> build(dataFile, 7655);
}

void HW04_Phase3App::mouseDown( MouseEvent event ){

}

void HW04_Phase3App::update(){

}

void HW04_Phase3App::draw(){

	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( HW04_Phase3App, RendererGl )