#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

// Binary Semaphore implementation
class BinarySemaphore {
private:
    bool signal; // Binary flag (true or false)
    mutex mtx;
    condition_variable cv;

public:
    BinarySemaphore() : signal(false) {}

    void wait(const string &processName) {
        unique_lock<mutex> lock(mtx);
        cout << processName << " is blocked, waiting for signal..." << endl;
        cv.wait(lock, [this]() { return signal; }); // Wait until signal is true
        signal = false; // Reset signal to false after receiving it
        cout << processName << " is in critical section." << endl;
    }

    void signalSemaphore(const string &processName) {
        unique_lock<mutex> lock(mtx);
        signal = true; // Set signal to true, allowing a waiting process to proceed
        cout << processName << " has exited critical section and signaled the semaphore." << endl;
        cv.notify_one(); // Notify one waiting thread
    }
};

// Shared resource
int shared_data = 0;
BinarySemaphore semaphore;  // Semaphore object

// Producer function
void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        this_thread::sleep_for(chrono::seconds(1)); // Simulate work before entering critical section
        semaphore.wait("Producer " + to_string(id)); // Producer waits for semaphore to enter critical section

        shared_data += 10; // Produce data
        cout << "Producer " << id << ": Produced data = " << shared_data << endl;

        semaphore.signalSemaphore("Producer " + to_string(id)); // Signal consumer
    }
}

// Consumer function
void consumer(int id) {
    for (int i = 0; i < 5; ++i) {
        semaphore.wait("Consumer " + to_string(id)); // Consumer waits for semaphore to enter critical section

        cout << "Consumer " << id << ": Consumed data = " << shared_data << endl;

        semaphore.signalSemaphore("Consumer " + to_string(id)); // Signal producer
    }
}

int main() {
    const int num_producers = 2; // Number of producer threads
    const int num_consumers = 2; // Number of consumer threads

    thread producers[num_producers]; // Producer threads
    thread consumers[num_consumers]; // Consumer threads

    // Create producer threads
    for (int i = 0; i < num_producers; ++i) {
        producers[i] = thread(producer, i + 1);
    }

    // Create consumer threads
    for (int i = 0; i < num_consumers; ++i) {
        consumers[i] = thread(consumer, i + 1);
    }

    // Join all producer threads
    for (int i = 0; i < num_producers; ++i) {
        producers[i].join();
    }

    // Join all consumer threads
    for (int i = 0; i < num_consumers; ++i) {
        consumers[i].join();
    }

    return 0;
}
