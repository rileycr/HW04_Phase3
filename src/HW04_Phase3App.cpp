#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "C:\Users\Cooper\Documents\CSE 274\HW04-rileycr-2\HW04-rileycr-2\rileycrStarbucks.h"
#include "Resources.h"

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

	dataTree_ = new rileycrStarbucks();
}

void HW04_Phase3App::mouseDown( MouseEvent event ){

}

void HW04_Phase3App::update(){

}

void HW04_Phase3App::draw(){

	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( HW04_Phase3App, RendererGl )