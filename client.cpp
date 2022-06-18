#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
using namespace std;

/*
 *  客户端程序
 * */
int main(){

				// 1. 创建用于通信的socket
				int fd = socket(AF_INET, SOCK_STREAM, 0);
				if(fd==-1){
								cout<<"failed to create socket."<<endl;
								return -1;
				}

				// 2. 指定ip和端口
				struct sockaddr_in addrt;
				addrt.sin_addr.s_addr = INADDR_ANY;
				addrt.sin_port = htons(5004);
				addrt.sin_family = AF_INET;
				int ret = connect(fd,(struct sockaddr*)&addrt, sizeof(addrt));
				if(ret==-1){
				cout<<"failed to connect."<<endl;
				}

				int number =1;
				while (1) {

				// 3.发送数据
				char buffer[1024];
				sprintf(buffer,"hello world,%d", number ++);
				send(fd, buffer, strlen(buffer)+1,0);

				// 4.接收数据
				memset(buffer, 0, sizeof(buffer));
				int len = recv(fd, buffer, sizeof(buffer), 0);
				if(len>0){
								cout<<"server say:"<<buffer<<endl;
				}
				else if(len==0){
								cout<<"server seems cut off the link..."<<endl;
				}
				else if(len<0){
								cout<<"failed to recv."<<endl;
								break;
				}

				sleep(1);// 防止客户端数据发送过快
				}

				// 5. 关闭socket
				close(fd);
}
