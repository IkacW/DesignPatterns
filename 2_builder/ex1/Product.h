#ifndef __PRODUCT_H
#define __PRODUCT_H

#include <iostream>

using namespace std;

/* concrete product */
class Product {
private:
    int part;
public:
    void setPart(int part) { this->part = part; }
    void use() { cout << "Using product which has part #" << part << endl ; }
};
#endif // __PRODUCT_H
