## Prime number counting project in 4 different languages. 
## Python time!

import time
import math
import multiprocessing


## main is prime number function, pretty much the same as the other languages
## then basically check if less than 2 and then check if divisible by any number up to the square root of the number

def is_prime(n):
    if n < 2: 
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0: 
            return False
    return True


## Straight forward count prime numbers function, will add to count if prime number is found and continue looping.
def count_primes(start, end): 
    count = 0 
    for num in range(start, end + 1):
        if is_prime(num): 
            count += 1
    return count

def main(): 
    N = int(input("Enter a number: "))
    num_processes = multiprocessing.cpu_count() # Uses all of the CPU Cores Available
    pool = multiprocessing.Pool(processes=num_processes)

    chunk_size = N

    ## This is a lot more complicated then the C++ one
    ## This ranges function basically does this if the number was 10,000 for eg:
    ## ranges = [
    ## (1, 2500),     # First worker (i = 0)
    ## (2501, 5000),  # Second worker (i = 1)
    ## (5001, 7500),  # Third worker (i = 2)
    ## (7501, 10000)  # Fourth worker (i = 3, last one)
    ranges = [(i * chunk_size + 1, (i + 1) * chunk_size if i < num_processes -1 else N) for i in range(num_processes)]

    start_time = time.time()
    results = pool.starmap(count_primes, ranges)
    pool.close()
    pool.join()

    total_primes = sum(results)
    end_time = time.time()

    print(f"Total prime numbers up to {N}: {total_primes}")
    print(f"Time taken: {end_time - start_time} seconds")

if __name__ == "__main__":
    main()