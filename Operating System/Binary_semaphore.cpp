#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

// Binary semaphore implementation
class BinarySemaphore {
private:
    bool signal; // Binary flag (true or false)
    mutex mtx;
    condition_variable cv;

public:
    BinarySemaphore() : signal(false) {}

    void wait(const string &processName) {
        unique_lock<mutex> lock(mtx);
        cout << processName << " is waiting (in block state)..." << endl;
        cv.wait(lock, [this]() { return signal; }); // Wait until signal is true
        signal = false; // Reset signal
        cout << processName << " entered the critical section." << endl;
    }

    void signalSemaphore(const string &processName) {
        unique_lock<mutex> lock(mtx);
        signal = true; // Set signal
        cout << processName << " exited the critical section and signaled the semaphore." << endl;
        cv.notify_one(); // Notify one waiting thread
    }
};

// Shared resource
int shared_data = 0;
BinarySemaphore semaphore;

// Producer function
void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        this_thread::sleep_for(chrono::seconds(1)); // Simulate work outside critical section
        semaphore.wait("Producer " + to_string(id)); // Producer enters critical section

        shared_data += 10; // Produce data
        cout << "Producer " << id << ": Produced data = " << shared_data << endl;

        semaphore.signalSemaphore("Producer " + to_string(id)); // Signal the consumer
    }
}

// Consumer function
void consumer(int id) {
    for (int i = 0; i < 5; ++i) {
        semaphore.wait("Consumer " + to_string(id)); // Consumer enters critical section

        cout << "Consumer " << id << ": Consumed data = " << shared_data << endl;

        semaphore.signalSemaphore("Consumer " + to_string(id)); // Exit critical section and signal
    }
}

int main() {
    const int num_producers = 4; // Number of producers
    const int num_consumers = 4; // Number of consumers

    vector<thread> producers;
    vector<thread> consumers;

    // Create producer threads
    for (int i = 1; i <= num_producers; ++i) {
        producers.emplace_back(producer, i);
    }

    // Create consumer threads
    for (int i = 1; i <= num_consumers; ++i) {
        consumers.emplace_back(consumer, i);
    }

    // Join all producer threads
    for (auto &t : producers) {
        t.join();
    }

    // Join all consumer threads
    for (auto &t : consumers) {
        t.join();
    }

    return 0;
}
