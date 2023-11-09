#include<iostream>
#include<unordered_set>
#include<unordered_map>

/*
In this case, we will see the situation where the order of handlers plays a big role in the time
efficiency of completing tasks. The request is not telling us if some specified handler could handle 
the request. Every handler, through hes logic, will decide if he can handle the request or to pass the 
request to another handler.
*/

class WebPage {
public:
	std::string url;
	WebPage(const std::string& url): url(url) {}
};

class InternetServiceHandler {
protected:
	InternetServiceHandler* next;
public:
	virtual WebPage* getPage(const std::string& url, const std::string& ip) {
		// It's not rare for base class handler not to have the abstract method that handles the request, 
		// because it has the simple solution, just to pass it to another handler. Now the purpose of derived 
		// classes is to handle the request if that is possible (if they can do it), otherwise, they should 
		// pass the request to the next hadler, if there is one.
		if (next) { return next->getPage(url, ip); }
		return nullptr;
	}
	void setNext(InternetServiceHandler* handler) { this->next = handler; }
	virtual ~InternetServiceHandler() { delete next; }
};

class DownloadPageInternetServiceHandler : public InternetServiceHandler {
public:
	WebPage* getPage(const std::string& url, const std::string& ip) { 
		return new WebPage(url); 
	}
};

class RestrictedAccessInternetServiceHandler : public InternetServiceHandler {
protected:
	std::unordered_set<std::string> ips;
public:
	RestrictedAccessInternetServiceHandler(std::unordered_set<std::string>& ips): ips(ips) {}
	WebPage* getPage(const std::string& url, const std::string& ip) {
		if (ips.find(ip) == ips.end()) { 
			return InternetServiceHandler::getPage(url, ip);
		}
		else {
			return nullptr;
		}
	}
};

class CacheInternetServiceHandler : public InternetServiceHandler {
protected:
	std::unordered_map<std::string, WebPage*> cache;
public:
	WebPage* getPage(const std::string& url, const std::string& ip) {
		if (cache.find(url) == cache.end()) {
			WebPage* page = InternetServiceHandler::getPage(url, ip);
			if (page != NULL)
				cache[url] = page;
			return page;
		} else {
			std::cout << "Vracam kesiran content sa adrese " << url << std::endl;
			return cache[url];
		}
	}
};

int main() {
	std::unordered_set<std::string>ips;
	ips.insert("12.32.43.54");
	ips.insert("12.32.43.154");

	InternetServiceHandler* handler1 = new RestrictedAccessInternetServiceHandler(ips);
	InternetServiceHandler* handler2 = new CacheInternetServiceHandler();
	InternetServiceHandler* handler3 = new DownloadPageInternetServiceHandler();
	handler2->setNext(handler3);
	handler1->setNext(handler2);

	WebPage* p1 = handler1->getPage("www.nesto.com", "12.32.43.154");
	if (p1) {
		std::cout << "Successfully downloaded contet from adress: " << p1->url << std::endl;
	}
	else {
		std::cout << "Failed to download content from adress www.nesto.com and from ip adress 12.32.43.154" << std::endl;
	}

	WebPage* p2 = handler1->getPage("www.nesto.com", "12.32.43.1");
	if (p2) {
		std::cout << "Successfully downloaded contet from adress " << p2->url << std::endl;
	}
	else {
		std::cout << "Failed to download content from adress www.nesto.com and from ip adress 12.32.43.1" << std::endl;
	}

	WebPage* p3 = handler1->getPage("www.nesto.com", "12.32.43.1");
	if (p3) {
		std::cout << "Successfully downloaded contet from adress " << p3->url << std::endl;
	}
	else {
		std::cout << "Failed to download content from adress www.nesto.com and from ip adress 12.32.43.1" << std::endl;
	}
	return 0;
}