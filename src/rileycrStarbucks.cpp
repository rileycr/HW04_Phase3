#include "rileycrStarbucks.h"
#include <iostream>
#include <fstream>

rileycrStarbucks::rileycrStarbucks(){
}

/*
I have a method to get the entry with the median x-value but have it commented
out because it sorts the whole array in terms of the x-value  I decided I should
pick the middle (unsorted) entry so that when I build the rest of the tree from the array
it is not all sorted by x-value.
*/
void rileycrStarbucks::build(Entry* c, int n){
	size = n;
	kdTreeRootEntry_ = new Entry(); 
	*kdTreeRootEntry_ = c[n/2];
	rootNode_ = new Node(*kdTreeRootEntry_, true);

	for(int i = 0; i< n; i++){
		rootNode_ -> insert(c[i], rootNode_);
	}
}

/*
This method was used to check that all the entries were all
added to the tree correctly
*/
void rileycrStarbucks::printInOrder(Node* r){
	if(r==NULL)
		return;
	printInOrder(r->leftChild_);
	cout << r -> entry_.identifier << endl;
	printInOrder(r->rightChild_);
}


Entry* rileycrStarbucks::getNearest(double x, double y){

	Entry* temp = new Entry();
	temp -> x = x;
	temp -> y = y;
	*temp = rootNode_ -> search(temp, rootNode_, true) -> entry_;

	return temp;
}


Entry rileycrStarbucks::getMedianX(Entry* c){
	Entry* temp = c;
	medianX_ = sortByX(temp, 0, size);
	return medianX_;
}

Entry rileycrStarbucks::sortByX(Entry* c, int start, int end){

	Entry temp;
	int i = start;
	int j = end;
	int pivotIndex = (start+end)/2;
	Entry pivot = c[pivotIndex];

	while(i <= j) {
		while(c[i].x < pivot.x)
			i++;
		while(c[j].x > pivot.x)
			j--;
		if(i <= j){
			temp = c[i];
			c[i] = c[j];
			c[j] = temp;
			i++;
			j--;
		}
	}

	if(start < j)
		sortByX(c, start, j);
	if(i < end)
		sortByX(c, i, end);

	return c[size/2];
}