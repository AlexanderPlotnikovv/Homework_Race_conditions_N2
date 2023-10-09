#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mx;

void funchelp(int progress, int num)
{
	mx.lock();
	std::cout << "\033[" << num+1 << ';' << 0 << "H" << num << "\t" << std::this_thread::get_id() << "\t";
	for (int i = 0; i < progress; ++i)
	{
		std::cout << '=';
	}
	if (progress != 24)
	{
		std::cout << "\r";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	mx.unlock();
}

void func(int num)
{
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < 25; ++i)
	{
		funchelp(i,num);
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	mx.lock();
	std::cout << "\t" << elapsed_seconds.count();
	std::cout << std::endl;
	mx.unlock();
}

int main()
{
	std::vector<std::thread> threads(4);
	std::cout << "Number" << "\t" << "ID" << "\t" << "Progress Bar" << "\t" << "\t" << "\t" << "Time" << std::endl;
	for (int i = 0; i < 4; ++i)
	{
		threads[i] = std::thread(func, i+1);
		//std::cout << std::endl;
	}
	for (auto& t : threads)
	{
		t.join();
	}
	return 0;
}