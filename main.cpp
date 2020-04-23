#include <iostream>
#include <thread>
#include <mutex>
#include <cstring>
#include <cmath>
#include <condition_variable>

#define NUMBER_OF_WRITERS 2
#define NUMBER_OF_READERS 2

using namespace std;

int total_threads = 0;
mutex m;
class reader {
    string name, *data;

    void read() {
        lock_guard<mutex> l(m);
        printf("Reader %s reads data: %s\n", name.c_str(), data->c_str());
        total_threads++;

    }

public:
    reader(const std::string &name, string *data) {
        this->name = name;
        this->data = data;
        thread readThread(&reader::read, this);
        readThread.detach();
    }
};

class writer {
    string name;
    string *data;

    void write() {
        lock_guard<mutex> l(m);
        *data = "writer " + name;
        printf("Writer %s changed string with data: %s\n", name.c_str(), data->c_str());
        total_threads++;
    }

public:
    writer(const string &name, string *data) {
        this->name = name;
        this->data = data;
        thread writeThread(&writer::write, this);
        writeThread.detach();
    }
};

int main() {

    string data = "data";

    for (int j = 0; j < (int) fmax(NUMBER_OF_WRITERS, NUMBER_OF_READERS); ++j) {
        if (j < NUMBER_OF_WRITERS) {
            char *writeName = new char[100];
            sprintf(writeName, "n %d", j);
            writer write(writeName, &data);
        }
        if (j < NUMBER_OF_READERS) {
            char *readName = new char[100];
            sprintf(readName, "n %d", j);
            reader read(readName, &data);
        }
    }

    while (total_threads != NUMBER_OF_READERS + NUMBER_OF_WRITERS) {
        //do nothing
    }
    return 0;
}
