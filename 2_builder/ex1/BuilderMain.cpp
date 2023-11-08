#include "Director.h"
#include "ConcreteBuilder.h"

/* basically a template, firstly create a concrete builder, then passing it to a director
  with which we generate product */
int main() {
    Builder *builder = new ConcreteBuilder();
    Director *director = new Director(builder);
    Product *product = director->construct();
    product->use();

    delete builder;
    delete director;
    delete product;

    return 0;
}
