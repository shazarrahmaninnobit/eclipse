#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>
using namespace std;
mutex m1;
condition_variable cv;
bool flag=false;
void produce(){
	unique_lock<mutex>lock(m1);
	cout<<"Produced"<<endl;;
	flag=true;
	cv.notify_all();
}
void consume(){
	unique_lock<mutex>lock(m1);
	cv.wait(lock,[]{return flag;});
	cout<<"Consumed"<<endl;
}
int main(){
	thread consumer(consume);
	thread producer(produce);
	consumer.join();
	producer.join();
	return 0;
}

