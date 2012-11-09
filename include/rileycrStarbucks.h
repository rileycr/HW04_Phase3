#include "Starbucks.h"
#include "Node.h"

class rileycrStarbucks : public Starbucks {
public:
	rileycrStarbucks();
	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);
	Entry getMedianX(Entry* c);

	void printInOrder(Node* r);

	Entry sortByX(Entry* c, int start, int end);

	Entry* kdTreeRootEntry_;
	Entry medianX_;
	Node* rootNode_;
	int size;
};