#ifndef __DIRECTOR_H
#define __DIRECTOR_H

#include "Builder.h"
#include "Product.h"

/* director which is using builders to generate product part by part */
class Director {
private:
    Builder *builder;
public:
    Director(Builder *builder) {
        this->builder = builder;
    }
    Product* construct() {
        builder->buildPart();
        return builder->getProduct();
    }
};

#endif // __DIRECTOR_H
