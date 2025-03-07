#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono> // For sleep_for

using namespace std;

// Global variables
mutex mtx;
condition_variable cv_empty, cv_full;
queue<int> buffer;
const int BUFFER_SIZE = 5; // Maximum buffer size

// Producer function
void producer(int id) {
    for (int i = 0; i < 10; ++i) { // Produce 10 items
        unique_lock<mutex> lock(mtx); // Lock the mutex
        cv_full.wait(lock, [] { return buffer.size() < BUFFER_SIZE; }); // Wait until space is available

        buffer.push(i); // Produce an item
        cout << "Producer " << id << " produced item " << i << endl;

        cv_empty.notify_all(); // Notify consumers
        this_thread::sleep_for(chrono::milliseconds(1000)); // Simulate production delay
    }
}

// Consumer function
void consumer(int id) {
    for (int i = 0; i < 10; ++i) { // Consume 10 items
        unique_lock<mutex> lock(mtx); // Lock the mutex
        cv_empty.wait(lock, [] { return !buffer.empty(); }); // Wait until buffer is not empty

        int item = buffer.front(); // Consume the item
        buffer.pop();
        cout << "Consumer " << id << " consumed item " << item << endl;

        cv_full.notify_all(); // Notify producers
        this_thread::sleep_for(chrono::milliseconds(1500)); // Simulate consumption delay
    }
}

int main() {
    const int num_producers = 2; // Number of producers
    const int num_consumers = 2; // Number of consumers

    thread producers[num_producers]; // Create producer threads
    thread consumers[num_consumers]; // Create consumer threads

    // Start producer threads
    for (int i = 0; i < num_producers; ++i) {
        producers[i] = thread(producer, i + 1);
    }

    // Start consumer threads
    for (int i = 0; i < num_consumers; ++i) {
        consumers[i] = thread(consumer, i + 1);
    }

    // Join all threads
    for (int i = 0; i < num_producers; ++i) {
        producers[i].join();
    }
    for (int i = 0; i < num_consumers; ++i) {
        consumers[i].join();
    }

    return 0;
}
