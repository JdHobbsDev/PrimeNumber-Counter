using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;

class PrimeNumbers
{
    //  checks if a number is prime \\ This one is very similar to the C++ one (It's vasically the same thing.)
    static bool IsPrime(int num)
    {
        if (num < 2) return false;
        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Counts prime numbers in the range given and stores the result.
    static int CountPrimes(int start, int end)
    {
        int count = 0;
        for (int i = start; i <= end; i++)
        {
            if (IsPrime(i)) count++;
        }
        return count;
    }

    static void Main()
    {
        Console.Write("Enter a number: ");
        int N = int.Parse(Console.ReadLine()); // Read input from user

        Stopwatch stopwatch = Stopwatch.StartNew(); // Starts the clock
        int numThreads = Environment.ProcessorCount; // Get CPU core count
        int chunkSize = N / numThreads; // Divide work evenly between threads

        List<Task<int>> tasks = new List<Task<int>>();
        for (int i = 0; i < numThreads; i++)
        {
            int start = i * chunkSize + 1;
            int end = (i == numThreads - 1) ? N : (i + 1) * chunkSize;
            tasks.Add(Task.Run(() => CountPrimes(start, end))); // Creates a worker thread
        }

        Task.WaitAll(tasks.ToArray()); // Waits for all workers to finish
        int totalPrimes = tasks.Sum(t => t.Result); // Adds up all results
        stopwatch.Stop(); // Stops the clock.

        Console.WriteLine($"Total prime numbers up to {N}: {totalPrimes}");
        Console.WriteLine($"Time taken: {stopwatch.Elapsed.TotalSeconds:F3} seconds");
    }
}
