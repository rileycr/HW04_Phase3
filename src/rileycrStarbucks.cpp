#include "rileycrStarbucks.h"

rileycrStarbucks::rileycrStarbucks(){
}

void rileycrStarbucks::build(Entry* c, int n){
	unsortedArrayData_ = new Entry[n];
	for(int i = 0; i < n; i++){
		unsortedArrayData_[i] = c[i];
	}
	size = n;
}

Entry* rileycrStarbucks::getNearest(double x, double y){
	Entry* nearest = new Entry();
	Entry temp = unsortedArrayData_[0];
	for(int i=0; i < size; i++){
		if(sqrt((unsortedArrayData_[i].x-x)*(unsortedArrayData_[i].x-x)+
			(unsortedArrayData_[i].y-y)*(unsortedArrayData_[i].y-y))
			< sqrt((temp.x-x)*(temp.x-x)+(temp.y-y)*(temp.y-y))){
				temp = unsortedArrayData_[i];
		}
	}

	*nearest = temp;
	return nearest;
}