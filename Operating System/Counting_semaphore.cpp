#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class CountingSemaphore {
private:
    int count;
    std::mutex mtx;
    std::condition_variable cv;

public:
    CountingSemaphore(int initial_count) : count(initial_count) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return count > 0; });
        count--;
    }

    void release() {
        std::lock_guard<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

void process(CountingSemaphore& semaphore, int process_id) {
    semaphore.acquire();
    std::cout << "Process " << process_id << " has acquired the semaphore" << std::endl;
    // Simulate work
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Process " << process_id << " is releasing the semaphore" << std::endl;
    semaphore.release();
}

int main() {
    CountingSemaphore semaphore(2); // Initial count set to 2

    std::thread p0(process, std::ref(semaphore), 0);
    std::thread p1(process, std::ref(semaphore), 1);
    std::thread p2(process, std::ref(semaphore), 2);
    std::thread p3(process, std::ref(semaphore), 3);
    std::thread p4(process, std::ref(semaphore), 4);
    std::thread p5(process, std::ref(semaphore), 5);

    p0.join();
    p1.join();
    p2.join();
    p3.join();
    p4.join();
    p5.join();

    return 0;
}
