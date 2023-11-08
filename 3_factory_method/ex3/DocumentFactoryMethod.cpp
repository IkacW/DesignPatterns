#include <iostream>
#include <vector>

using namespace std;

/* Abstract product  */
class Document {
private:
    string m_name;
public:
    Document(string name) {
        m_name = name;
    }
    virtual void open() = 0;
    virtual void close() = 0;
    string getName() {
        return m_name;
    }
};

/* concrete product */
class MyDocument: public Document {
public:
    MyDocument(string name): Document(name) {}
    void open() {
        cout << "\tMyDocument.open()" << endl;
    }
    void close() {
        cout << "\tMyDocument.close()" << endl;
    }
};

/* Abstract Client which has fabric method makeDocument */
class Client {
  public:
    Client() {
        cout << "Client.constructor()" << endl;
    }
    ~Client() {
        cout << "Client.destructor()" << endl;
        for (int i = 0; i < m_documents.size(); i ++) {
            m_documents[i]->close();
        }
    }
    void newDocument(string ime) {
        cout << "Client.newDocument()" << endl;
        m_documents.push_back(makeDocument(ime));
        m_documents.back()->open();
    }
    void documentReports();
    /* factory method */
    virtual Document *makeDocument(string ime) = 0;
  private:
    vector<Document*> m_documents;
};

void Client::documentReports() {
  cout << "Client.documentReports()" << endl;
  for (int i = 0; i < m_documents.size(); i ++) {
    cout << "name document #" << i << ": " << m_documents[i]->getName() << endl;
  }
}

/* concrete client, implements concrete factory method for concrete product */
class MyClient: public Client {
  public:
    MyClient() {
        cout << "MyClient.constructor()" << endl;
    }
    ~MyClient() {
        cout << "MyClient.destructor()" << endl;
    }
    /* concrete factory method for making concrete procudt MyDocument */
    Document *makeDocument(string name) {
        cout << "   MyClient.makeDocument()" << endl;
        return new MyDocument(name);
    }
};
/* primer koriscenja */
int main() {
  Client *myClient = new MyClient();
  myClient->newDocument("List");
  myClient->newDocument("Contract");
  myClient->newDocument("Invoice");
  myClient->documentReports();
  delete myClient;
}
