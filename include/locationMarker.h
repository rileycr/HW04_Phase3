#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Starbucks.h"

using namespace ci;

class locationMarker {
public:
	locationMarker(Entry e, int windowWidth, int windowHeight);
	locationMarker();
	void draw();
	Entry* entry_;
	ColorA color_;
private:
	Vec2f center_;
	int radius_;
};