#include <iostream>
#include <time.h>
#include <math.h>
#include <thread>
using namespace std;

unsigned long long aPub , bPub;
long g, p, a, b;
int flag = 0;

unsigned long long int power(long k, long n) {
	long long m = 9223372036800;
	if (n == 1) {
		return k;
	}
	else return((long long int )pow(k, n) % m);
}

int alice() {
	unsigned long long key;
	aPub = power(g, a)%p;
	//aPub = aPub % p;
	//cout << aPub << " ";
	flag = 1;
	//this_thread::sleep_for(1000ms);
	while (1) {
		if (flag == 2) {
			key = power(bPub, a)%p;
			cout << "Alice's key:" << key << endl;
			break;
		}
	}
	return 0;
}

int bob() {
	bPub= power(g, b) %p;
	//bPub = bPub % p;
	unsigned long long key;
	//cout << " " << bPub << " ";
	while (1) {
		if (flag == 1){
			key = power(aPub, b)%p;
			cout << "Bob's key:" << key << endl;
			flag = 2;
			break;
		}
	}
	return 0;
}




int main(){
	srand((unsigned)time(NULL));
	g = rand()%5+2;
	p = rand()%100+9;
	a = rand()%5+2;
	b = rand()%5+2;
	//cout << a << " " << b << " " << g << " " << p << endl;
	thread f(alice);
	thread s(bob);

	f.join();
	s.join();
	return 0;
}