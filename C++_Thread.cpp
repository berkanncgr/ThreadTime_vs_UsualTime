#include <iostream>
#include <thread>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <chrono>
#include <ctime>
#include <mutex>

// Comment down and run the program. If you get 4996 Error, uncomment and run.
#pragma warning(disable : 4996) 

//double AccountBalance = 100;
//std::mutex AccountLock, Lock;
//int GetRandom(int max)
//{
//    srand(time(NULL));
//    return rand() % max;
//}

//void ExecuteThread(int id)
//{
//    auto nowTime = std::chrono::system_clock::now();
//    std::time_t SleepTime = std::chrono::system_clock::to_time_t(nowTime);
//    tm myLocalTime = *localtime(&SleepTime);
//    std::cout << "Thread " << id << " Sleep Time" << SleepTime << std::ctime(&SleepTime)<<"\n";
//
//    std::this_thread::sleep_for(std::chrono::seconds(GetRandom(3)));
//
//    nowTime = std::chrono::system_clock::now();
//    SleepTime = std::chrono::system_clock::to_time_t(nowTime);
//    std::cout << "Thread " << id << " Awake Time" << SleepTime << std::ctime(&SleepTime)<<"\n";
//}

//std::string GetTime()
//{
//    auto nowTime = std::chrono::system_clock::now();
//    std::time_t SleepTime = std::chrono::system_clock::to_time_t(nowTime);
//    return std::ctime(&SleepTime);
//}

//void GetMoney(int id, double withdrawal)
//{
//    std::lock_guard<std::mutex> lock(AccountLock);
//    std::this_thread::sleep_for(std::chrono::seconds(3));
//    std::cout << id << " tries to withdrawal $ " << withdrawal << " on "<<GetTime();
//    if (AccountBalance >= withdrawal)
//    {
//        AccountBalance -= withdrawal;
//        std::cout << "New Balance is $ " << AccountBalance << "\n"; 
//    }
//    else std::cout << "Not enough money. Current Balance: "<<AccountBalance<<"\n";
//}

//void AccountThread()
//{
//    std::thread threads[10];
//    for (int i = 0; i < 10; i++)
//        threads[i] = std::thread(GetMoney, i, 15);
//    }
//    for (int j = 0; j < 10; j++)
//        threads[j].join();
//}

std::vector<unsigned int> PrimeVector;

// Just Call the FindPrimesWithThreadTime() of down three.
void FindPrimesUsingThread(unsigned int start, unsigned int end)
{
    for (unsigned int x = start; x <= end; x += 2)
    {
        for (unsigned int y = 2; y <= x; y++)
        {
            if (x % y == 0) break;
            else if (y + 1 == x)
            {
                Lock.lock();
                PrimeVector.push_back(x);
                Lock.unlock();
            }
        }
    }
}

void FindPrimesWithThread(unsigned int start, unsigned int end,unsigned int numThreds)
{
    std::vector<std::thread> ThreadVector;
    unsigned int ThreadSpread = end / numThreds,  newEnd = start + ThreadSpread - 1;
    
    for (unsigned int x = 0; x < numThreds; x++)
    {
        ThreadVector.emplace_back(FindPrimesUsingThread, start, newEnd);
        start += ThreadSpread;
        newEnd += ThreadSpread;
    }
    for (auto& t: ThreadVector)
    {
        t.join();
    }
}

void FindPrimesWithThreadTime()
{
    int StartTime = clock();
    FindPrimesWithThread(1, 10000, 3);
    int EndTime = clock();

    for (auto i : PrimeVector)
        std::cout << i << std::endl;

    std::cout << "Thread End Time: " << (EndTime - StartTime) / double(CLOCKS_PER_SEC) << std::endl;
}



// Just call the FindPrimesWithoutThreadTime() of down two.

void FindPrimesNotUsingThread(unsigned int start, unsigned int end)
{
    for (unsigned int x = start; x <= end; x+=2)
    {
        for (unsigned int y = 2; y < x; y++)
        {
            if (x % y == 0) break;
            else if (y + 1 == x)PrimeVector.push_back(x);
        }   
    }

}

void FindPrimesWithoutThreadTime()
{
    int StartTime = clock();
    FindPrimesNotUsingThread(1, 100000);
    int EndTime = clock();
    for (auto i : PrimeVector)
        std::cout << i << "\n";
    std::cout << "Exec time: " << (EndTime - StartTime) / double(CLOCKS_PER_SEC) << std::endl;
}


int main()
{    
    // Comment one of them and run the code, after then do the opposite.

    FindPrimesWithThreadTime(); 
    FindPrimesWithoutThreadTime();

    return 0;
}
