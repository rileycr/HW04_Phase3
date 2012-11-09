#include "Starbucks.h"


class rileycrStarbucks : public Starbucks {
public:
	rileycrStarbucks();
	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);
	Entry* unsortedArrayData_;
private:
	int size;
};