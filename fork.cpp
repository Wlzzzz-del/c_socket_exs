#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
				int frk=0;
				cout<<"progress begin..."<<endl;
				int clients = 2;

				for(int i=0;i<clients;++i){
				int pid = frk = fork();
				if(frk==0){
				cout<<"this is child"<<pid<<endl;
				}
				else {
				cout<<"this is parent"<<pid<<endl;
				}
				}
				return 0;
}
