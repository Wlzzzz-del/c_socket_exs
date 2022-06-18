#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
using namespace std;

/*
 *   服务器端服务程序
 * */
int main(){

				// 1. 创建监听的socket
				int fd = socket(AF_INET, SOCK_STREAM, 0);
				if(fd==-1)
				{
								cout<<"failed to create socket."<<endl;
								return -1;
				}
				cout<<"succfully create socket.";

				// 2.绑定本地IP port
				struct sockaddr_in addr;
				addr.sin_family = AF_INET;
				addr.sin_port = htons(5004);
				addr.sin_addr.s_addr = INADDR_ANY;

				int ret = bind(fd,(struct sockaddr*)&addr,sizeof(struct sockaddr));
				if(ret == -1){
								cout<<"failed to bind."<<endl;
								return -1;
				}
				cout<<"succfully bind port."<<endl;

				// 3. 设置监听
				// 第二个参数已经完成连接但正在等待应用程序接收的
				// socket 队列长度
				ret = listen(fd, 128);
				if(ret == -1){
								cout<<"failed to listen"<<endl;
								return -1;
				}
				// 4. 等待客户端连接
				struct sockaddr_in caddr;
				socklen_t size = sizeof(caddr);
				// accept 返回一个用于通信的文件描述符
				int cfd = accept(fd, (struct sockaddr*)&caddr,&size);
				if(fd==-1){
								cout<<"failed to accept"<<endl;
								return -1;
				}

				// 5. 连接建立成功
				// 打印端口和ip
				cout<<"client's port: "<<ntohs(caddr.sin_port);
				char ip[INET_ADDRSTRLEN];// INET地址长度宏定义
				cout<<inet_ntop(AF_INET,&caddr.sin_addr.s_addr,ip,sizeof(ip));

				while(1){
								char buffer[1024];
								int len = recv(cfd, buffer,sizeof(buffer), 0);
								if(len>0){
												cout<<"client say:"<<buffer<<endl;
												send(cfd, buffer, len, 0);
								}
								else if(len==0){
												cout<<"client have cut off."<<endl;
												break;
								}
								else{
												cout<<"recv"<<endl;
												break;
								}
				}
				// 关闭描述符
				close(cfd);
				close(fd);

				return 0;
}
