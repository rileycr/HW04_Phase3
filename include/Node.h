#include "Starbucks.h"
class Node {
public:
	Node(Entry e);
	Node(Entry e, bool xLevel);
	Node* insert(Entry e, Node* r);
	Node* search(Entry* e, Node* r, bool xLevel);
	double distance(Entry entry1, Entry entry2);

	Entry entry_;
	int index;
	Node* leftChild_;
	Node* rightChild_;
	bool isXLevel_;
};