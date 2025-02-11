#include <thread>
#include <ctime>
#include "Threads.h"

std::mutex critacal_se;
std::mutex print_se;

//the function print "I Love Threads"
void I_Love_Threads()
{
	std::cout << "I Love Threads" << std::endl;
}

//the function use thread to print "I Love Threads" by another function
void call_I_Love_Threads()
{
	std::thread t1(I_Love_Threads);

	t1.join();
}

//the function print a list (vector<int> type)
//primes - the vector to get the info from(to print)
void printVector(const std::vector<int> primes)
{
	for (int i = 0;i < primes.size();i++)
	{
		std::cout << primes[i] << ",";
	}
	std::cout << std::endl;
}

//the function get all the primes from the begin to the end and put it in the given vector
//begin - the start of the range to check
//end - the end of the range to check
//primes - the vector to put into the answars
void getPrimes(const int begin, const int end, std::vector<int>& primes)
{
	bool isPrime = true;//asume that the number is prime
	for (int i = begin; i < end;i++)
	{
		isPrime = true;//reset the value of the flag
		for (int j = 2;j < i;j++)
		{
			if (i % j == 0)
			{
				isPrime = false;//fount a divisitor so it not a primt number
				break;
			}
		}
		if (isPrime && i != 1)
		{
			primes.push_back(i);//if it prime add it
		}
	}
}

//the function using thread to get the primes number
//begin - the start of the range to check
//end - the end of the range to check
//the function return the vector of the primes
std::vector<int> callGetPrimes(int begin, int end)
{
	std::vector<int> primes;
	time_t start, ending;
	time(&start);//get the starting time
	std::thread t(getPrimes, begin, end, std::ref(primes));
	t.join();//waiting for the thread to finish
	time(&ending);//get the time he finished working
	print_se.lock();
	std::cout << "time took for one thread: " << difftime(ending, start) << std::endl;
	print_se.unlock();
	return primes;
}

//the function put all the file in range into a file
//begin - the start of the range to check
//end - the end of the range to check
//file - the file to put into the answars
void writePrimesToFile(int begin, int end, std::ofstream& file)
{
	std::vector<int> prime = callGetPrimes(begin, end);
	file << "[ ";
	for (int i = 0;i < prime.size();i++)
	{
		critacal_se.lock();
		file << prime[i];
		if (i != prime.size() - 1)
		{
			file << " , ";
		}
		critacal_se.unlock();
	}
	file << " ]";
}

//the function seperate the work of finding the primes into a cuople of threads
//begin - the start of the range to check
//end - the end of the range to check
//filePath - the path of the file to put into the answars
//N - how much thread to do
void callWritePrimesMultipleThreads(int begin, int end, std::string filePath, int N)
{
	int diff = (end - begin) / N, threadEnd = 0;
	std::vector<std::thread> threads;
	end = end - diff * N;
	std::ofstream file(filePath);
	time_t start, ending;
	time(&start);
	for (int i = 0;i < N;i++)
	{
		threads.push_back(std::thread(writePrimesToFile, begin, threadEnd, std::ref(file)));
		begin += diff;
		threadEnd = (i == N - 1) ? end : begin + diff;
	}
	for (int i = 0;i < N;i++)
	{
		threads[i].join();
	}
	time(&ending);
	std::cout << "time took: " << difftime(ending, start) << std::endl;
}
