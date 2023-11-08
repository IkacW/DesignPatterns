#include <cstring>
#include <iostream>

using namespace std;

/* concrete product which has mulitple parts (in this case, body, wings) */
class Plane {
private:
    string body;
    string wings;
public:
    Plane() {}
    string getBody() { return body; }
    void setBody(string body) { this->body = body; }
    string getWings() { return wings; }
    void setWings(string wings) { this->wings = wings; }

    void show() {
        cout << "Plane looks like this -> " << endl;
        cout << "Body: " << body << endl;
        cout << "Wings: " << wings << endl;
    }
};

/* abstract builder, it has an ability to set parts when generating product */
class PlaneBuilder {
public:
    virtual void makeBody() = 0;
    virtual void makeWings() = 0;
    virtual Plane* getPlane() = 0;
};

/* concrete builder */
class JetPlaneBuilder : public PlaneBuilder {
private:
    Plane* product;
public:
    JetPlaneBuilder() {
        product = new Plane();
    }
    void makeBody() {
        product->setBody("Metal sassi for JET plane");
    }
    void makeWings() {
        product->setWings("Metal wings for JET plane");
    }
    Plane* getPlane() {
        return product;
    }
};

/* concrete builder */
class PropellerPlaneBuilder : public PlaneBuilder {
private:
    Plane* product;
public:
    PropellerPlaneBuilder() {
        product = new Plane();
    }
    void makeBody() {
        product->setBody("Metal sassi for PROPELLER plane");
    }
    void makeWings() {
        product->setWings("Metal wings for PROPELLER plane");
    }
    Plane* getPlane() {
        return product;
    }
};

/* controller/director which is using builder to create plane and gives back a concrete product */
class Controller {
public:
    Plane* makePlane(PlaneBuilder *m) {
        m->makeBody();
        m->makeWings();
        return m->getPlane();
    }
};

/* we are creating controller and passing him the concrete builder to create finished product */
int main() {
    Controller *d = new Controller();
    cout << "Creating JET Plane" << endl;
    Plane *a = d->makePlane(new JetPlaneBuilder());
    a->show();

    cout << "Creating PROPELLER Plane" << endl;
    Plane *b = d->makePlane(new PropellerPlaneBuilder());
    b->show();

    return 0;
}
