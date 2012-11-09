#include "Node.h"

Node::Node(Entry e, bool xLevel){
	entry_ = e;
	isXLevel_ = xLevel;
	leftChild_ = rightChild_ = NULL;
}

Node::Node(Entry e){
	entry_ = e;
	leftChild_ = rightChild_ = NULL;
}

Node* Node::insert(Entry e, Node* r){
	if(r==NULL)
		return new Node(e, true);
	if(r -> isXLevel_){
		if(e.x == r -> entry_.x)
			return r;
		if(e.x < r -> entry_.x){
			r -> leftChild_ = insert(e, r -> leftChild_);
		} else {
			r -> rightChild_ = insert(e, r -> rightChild_);
		}
	} else {
		if(e.y == r -> entry_.y)
			return r;
		if(e.y < r -> entry_.y){
			r -> leftChild_ = insert(e, r -> leftChild_);
		} else {
			r -> rightChild_ = insert(e, r -> rightChild_);
		}
	}
	return r;
}

Node* Node::search(Entry* e, Node* r, bool xLevel){
	Node* candidate;
	if(r == NULL)
		return NULL;
	if(xLevel){
		if(e -> x == r -> entry_.x){
			return r;
		}
		if(e -> x < r -> entry_.x){
			candidate = search(e, r -> leftChild_, !xLevel); 
		} else {
			candidate = search(e, r -> rightChild_, !xLevel);
		}
	} else {
		if(e -> y == r -> entry_.y){
			return r;
		}
		if(e -> y < r -> entry_.y){
			candidate = search(e, r -> leftChild_, !xLevel); 
		} else {
			candidate = search(e, r -> rightChild_, !xLevel);
		}
	}
	if(candidate == NULL)
		return r;
	else {
		if(distance(*e, candidate->entry_) < distance(*e,r->entry_))
			return candidate;
		else
			return r;
	}
}

double Node::distance(Entry entry1, Entry entry2){
	return ((entry1.x-entry2.x)*(entry1.x-entry2.x))+((entry1.y-entry2.y)*(entry1.y-entry2.y));
}