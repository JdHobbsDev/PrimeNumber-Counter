// Prime number counting using threads
// Doing this in C++, Python, C# and Java.. Maybe
// hopefulyl this doesn't go to shit.

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>


// Main function to check if the number is a prime number
// bool to make it easier
bool isPrime(int num) {
    if (num < 2) return false; // 0 & 1 are not prime numbers, so adding this check.
    for (int i = 2; i * i <= num; ++i) { // checks up to the square root of number
        if (num % i == 0) return false; // if it divides evenly, it's not prime
    }
    return true; // if no divisors found, it shows true meaninfg its prime.
}

// Counts prime numbers in the range given and stores the result.
void countPrimes(int start, int end, int &count) {
    count = 0; // starts counting from 0
    for (int i = start; i <= end; ++i) {
        if (isPrime(i)) count++; // if the number is prime, it increases the count.
    }
}

int main() {
    int N; // the number we count the primes up to.
    std::cout << "Enter a Number: ";
    std::cin >> N; // Get's the users input and stores as the N variable

    auto start_time = std::chrono::high_resolution_clock::now(); // Starts timing how long it takes the threads to count.

    int numThreads = 4; // Uses 4 threads (Basically Workers trying to find the prime numbers.)
    std::vector<std::thread> threads(numThreads); // List that stores the threads
    std::vector<int> results(numThreads); // List that stores the results from each thread / worker

    int chunkSize = N / numThreads; // Decides how much each worker does.

    // Starts the threads
    for (int i = 0; i < numThreads; i++) {
        int start = i * chunkSize + 1; // Start of range
        int end = (i == numThreads - 1) ? N : (i + 1) * chunkSize; // End of range
        threads[i] = std::thread(countPrimes, start, end, std::ref(results[i]));
    }

    // Waits for all workers to finish before displaying a result.
    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }

    // Adds up all the threads results
    int totalPrimes = 0;
    for (int count : results) {
        totalPrimes += count;
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // Stops the timing (Mostly using timing if its like a massive number)
    std::chrono::duration<double> elapsed_time = end_time - start_time; // Calculates elapsed time

    // simple iostream console result
    // TODO:
    // Eventually I want to make a GUI that displays it.
    std::cout << "Total prime numbers up to " << N << ": " << totalPrimes << "\n";
    std::cout << "Time Taken: " << elapsed_time.count() << "seconds\n";
    return 0;
}
