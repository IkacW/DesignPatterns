#include<iostream>

class Image {
protected:
	std::string path;
	int width; 
	int height;

public:
	Image() = default;
	Image(std::string path, int width, int height):
		path(path), width(width), height(height) {
		std::cout << "Creating image " << width << "x" << height << " from " << path << std::endl;
	}

	virtual int getWidth() { return width; }
	virtual int getHeight() { return height; }
	virtual void displayImage() {
		std::cout << "displaying image from " << path << std::endl; 
	}
};

class ImageProxy : public Image {
private:
	Image* img = nullptr;
	// The idea is to create picture only when needed. As a derived class of Image,
	// our proxy already has atribudes for this image, and with his creation we are creating
	// the image object also, but idea is that in real use, our picture would be the a matrix
	// or some 3D tensor of pixels which would be available to us only after reading from file, which
	// is expensive operation.
	// Only when needed, image is going to be created. Which is stored as a pointer to an image.
	// To be able to crete an image, we must store some paramaters that are needed for image creation.
	
	// We could store it in the following way:
	// std::string imgPath; // na vežbama smo koristili ova tri atributa
	// int imgWidth;
	// int imgHeight;
	// But there is no need for it, because we already have (as an derived class from image), all  needed 
	// atributes.

	void createImage() {
		if (img) return;
		//img = new Image(imgPath, imgWidth, imgHeight);
		img = new Image(path, width, height);
	}
public:
	ImageProxy(std::string path, int width, int height)
		// : imgPath(path), imgWidth(width), imgHeight(height) {}
	{
		this->path = path;
		this->width = width;
		this->height = height;
		// We are not calling the constructor Image(path, width, height), because it is expensive operation
		// in a real life situation, and we won't call it until it's really necessary.
	}

	int getWidth() override {
		createImage();
		return img->getWidth();
	}
	int getHeight() override {
		createImage();
		return img->getHeight();
	}

	void displayImage() {
		createImage();
		img->displayImage();
	}

	~ImageProxy() { delete img; }
};


int main() {
	Image* im = new ImageProxy("bla bla.png", 100, 200);
	Image* im2 = new ImageProxy("bla.png", 10, 20);
	Image* im3 = new ImageProxy("bla3.png", 140, 240);
	im->displayImage(); // images im2 and im3 won't be created.
	return 0;
}