#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <functional>
#include <future>
#include <chrono>

using namespace std;

struct task
{
    string status;
    function<void()> func;
    task(string status, function<void()> func)
    {
        this->status = status;
        this->func = func;
    }
};

class threadpool
{
public:
    threadpool()
    {
        flag = true;
        thcount = 0;
    }
    ~threadpool()
    {
       for (int i = 0; i < threads.size(); i++)
       {
          threads[i].join();
       }
    }
    void addTask(function<void()> func)
    {
        lock_guard<mutex> mtx(blocker);
        queue.push_back(task(statuses[0], func));
    }
    void run(int threadnum = thread::hardware_concurrency() - 1)
    {
        thcount += threadnum;
        if (thcount > thread::hardware_concurrency() - 1)
        {
            cout << "Error:: maximum number of threads reached" << endl;
            return;
        }
        else if (threadnum < 1)
        {
            cout << "Error:: the number of threads cannot be negative" << endl;
            return;
        }
        for (int i = 0; i < threadnum; i++)
        {
            threads.push_back(thread([this]()
                {
                    while (flag)
                    {
                        for (int i = 0; i < queue.size(); i++)
                        {

                            if (queue[i].status == statuses[0])
                            {
                                queue[i].status = statuses[1];
                                queue[i].func();
                                queue[i].status = statuses[2];
                                break;
                            }
                        }
                    }
            }));
        }
    }
    void end()
    {
        flag = false;
    }
    string getStatus(int index)
    {
        if (index <= 0)
        {
            return "Error:: 404";
        }
        else if (index > queue.size())
        {
            return "Error:: 404";
        }
        else
        {
            return queue[index - 1].status;
        }
    }

private:
    vector<task> queue;
    const vector<string> statuses = {"Waiting","In process","Complete"};
    mutex blocker;
    vector<thread> threads;
    bool flag;
    int thcount;
};






void test(int x)
{
    this_thread::sleep_for(chrono::milliseconds(8000));
    cout << "This is cool tekst: " << x << endl;
}

void test1(int x, int y)
{
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Hello world: " << x + y << endl;
}

string test2()
{
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "8=D\n";
    return "8=D\n";
}

int main()
{
    threadpool tp;
    tp.addTask([&]() {test2(); });
    tp.addTask([&]() {test2(); });
    tp.addTask([&]() {test2(); });
    tp.addTask([&]() {test2(); });
    tp.addTask([&]() {test2(); });
    tp.addTask([&]() {test2(); });
    tp.addTask([&]() {test2(); });
    tp.addTask([&]() {tp.end(); });
    cout << tp.getStatus(4);
    tp.run(5);


}