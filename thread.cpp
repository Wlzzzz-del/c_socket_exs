// 编译命令
// g++ thread.cpp -o thread -std=c++11 -pthread

// 使用多线程与互斥锁实现创建多个socket
#include <cstdio>
#include <cstring>
#include <thread>
#include <iostream>
#include <mutex>
#include "socket.cpp"
using namespace std;

char buf[1024];
char port[3];
int nums=10;
int clients = 0;
std::mutex m;

void prt(){
				int fd = new_socket(buf, port);
				lock_guard<mutex> lock_guard(m);
				if(fd!=-1)++clients;
}
int main(){
				thread* t;
				memset(buf, 0, 1024);
				memset(port, 0, 3);
				sprintf(buf,"www.baidu.com");
				sprintf(port, "80");

				// 多线程
				thread th1(prt);
				thread th2(prt);
				thread th3(prt);

				// 主线程阻塞等待子线程返回
				th1.join();
				th2.join();
				th3.join();
				// 主线程必须等待子线程完成后返回
				for(int i=0; i<nums; ++i){
								t = new thread(prt);
								t->join();
				}
				cout<<"here is main"<<endl;
				cout<<"clients:"<<clients<<endl;

				return 0;
}
