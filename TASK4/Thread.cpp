#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

struct SensorPacket {
    uint64_t id;
    chrono::steady_clock::time_point send_time;
    vector<int> values;
};

queue<SensorPacket> q;   // 队列，放入数据，先进先出
mutex mtx;           // 互斥锁
bool finished = false;   // 采集是否结束
int total = 0;// 一共要有20
condition_variable cv;   // 条件变量,有效避免一直重复循环          
//线程一，产生数据
void producer() {
    for (int i = 0; i < 20; i++) {
        this_thread::sleep_for(chrono::milliseconds(100));  // 每 100ms 一组

        SensorPacket p;
        p.id = i;
        for (int j = 0; j < 5; j++) {
            p.values.push_back(rand() % 101);
        }
        p.send_time = chrono::steady_clock::now();          // 发送时刻

        mtx.lock();                 // 上锁
        q.push(p);               // 放数据
        mtx.unlock();               // 解锁
        cv.notify_one();             // 条件变量通知

    }

    mtx.lock();
    finished = true;                // 采集结束
    mtx.unlock();
    cv.notify_all();                // 这个必须得有，没有就坏了
}
//第二个线程
void consumer() {
    while (1) {
        unique_lock<mutex> lk(mtx);              // 上锁
        while (q.empty() && !finished) {
            cv.wait(lk);                         // 等着
        }
        if (q.empty()) {
            break;                               // 退出
        }
        SensorPacket p = q.front();              // 取一个包
        q.pop();
        lk.unlock();                       

        int mn = 101, mx = -1, sum = 0;
        for (int j = 0; j < (int)p.values.size(); j++) {
            int v = p.values[j];
            if (v < mn) mn = v;
            if (v > mx) mx = v;
            sum = sum + v;
        }
        double avg = sum / 5.0;

        double ms = chrono::duration<double, milli>(
                        chrono::steady_clock::now() - p.send_time).count();

        // 输出
        printf("[结果] id=%llu, 数据=[", (unsigned long long)p.id);
        for (int j = 0; j < (int)p.values.size(); j++) {
            if (j != 0) printf(", ");
            printf("%d", p.values[j]);
        }
        printf("], 最小值=%d, 最大值=%d, 平均值=%.2f, 耗时=%.2f ms\n",
               mn, mx, avg, ms);

        total = total + 1;
    }
}

int main() {
    srand(time(NULL));//如果没有这，随机生成会得到一样的数据，有必要引入<ctime>
    cout << "监测程序已启动" << endl;
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();

    cout << "采集与处理完成，共处理 " << total << " 组数据，程序退出" << endl;
    return 0;
}