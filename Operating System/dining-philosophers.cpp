#include <iostream>
#include <mutex>
#include <thread>
#include <semaphore.h>

using namespace std;

const int no_of_philosophers = 10;
const int max_philosophers_eating = 3;

struct Chopstics
{
public:
    Chopstics() {}
    std::mutex mu;
};

// Semaphore to control the number of philosophers eating simultaneously
sem_t eatingSemaphore;

auto eat = [](Chopstics &left_chopstics, Chopstics &right_chopstics, int philosopher_number) {

    // Wait until allowed to eat
    sem_wait(&eatingSemaphore);

    // Pick up left chopstick
    std::unique_lock<std::mutex> llock(left_chopstics.mu);

    // Pick up right chopstick
    std::unique_lock<std::mutex> rlock(right_chopstics.mu);

    // Eating
    cout << "Philosopher " << philosopher_number << " is enjoying a meal." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Finished eating
    cout << "Philosopher " << philosopher_number << " has finished the meal." << endl;

    // Release the semaphore to allow another philosopher to eat
    sem_post(&eatingSemaphore);
};

int main()
{
    // Initialize semaphore
    sem_init(&eatingSemaphore, 0, max_philosophers_eating);

    // Create chopsticks
    Chopstics chp[no_of_philosophers];

    // Create philosophers
    std::thread philosopher[no_of_philosophers];

    // Philosophers start contemplating
    for (int i = 0; i < no_of_philosophers; ++i)
    {
        cout << "Philosopher " << (i + 1) << " is thinking..." << endl;

        // Define the left and right chopsticks for each philosopher
        Chopstics &left_chopstick = chp[i];
        Chopstics &right_chopstick = chp[(i + 1) % no_of_philosophers];

        // Start a thread for each philosopher
        philosopher[i] = std::thread(eat, std::ref(left_chopstick), std::ref(right_chopstick), i + 1);
    }

    // Join philosopher threads
    for (auto &ph : philosopher)
    {
        ph.join();
    }

    // Destroy semaphore
    sem_destroy(&eatingSemaphore);

    return 0;
}
