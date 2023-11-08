#ifndef __CONCRETE_BUILDER_H
#define __CONCRETE_BUILDER_H

/*  concrete builder, has an ability to generate product part by part */
class ConcreteBuilder: public Builder {
private:
    Product *product;
public:
    ConcreteBuilder() {
        product = new Product();
    }
    void buildPart() {
        product->setPart(5);
    }
    Product *getProduct() {
        return product;
    }
};
#endif // __CONCRETE_BUILDER_H

