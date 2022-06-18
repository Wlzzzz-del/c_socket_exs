#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
using namespace std;

int main(){
				// create socket
				int fd = socket(AF_INET, SOCK_STREAM, 0);
				if(fd==-1){
				cout<<"failed to create socket.";
				return -1;
				}
				// 获取百度的域名
				char domain[1024] = "www.github.com";
				hostent* ip = gethostbyname(domain);
				char** ptr = ip->h_addr_list;
				char str[1024];

				printf("getting ip address...\n");
				printf("domain:%s\n",ip->h_name);
				for(;*ptr!=NULL;++ptr){
				printf("ipv4 address:%s\n",inet_ntop(ip->h_addrtype,*ptr,str,sizeof(str)));
				}
				// 域名转字节序
				//inet_pton(AF_INET, ip->h_addr_list[0], &addrt.sin_addr.s_addr);

				// specify ip and port
				struct sockaddr_in addrt;
				addrt.sin_port = htons(80);
				addrt.sin_family = AF_INET;
				// 这句好像错了，是需要转NBO
				addrt.sin_addr.s_addr=inet_addr(str);
				

				int ret = connect(fd,(struct sockaddr*)&addrt,sizeof(addrt));
				if(ret == -1){
				cout<<"failed to connect."<<endl;
				return -1;
				}
				cout<<"connect successfully."<<endl;

				// send data
				char buffer[1024];
				// 报文出错
				sprintf(buffer, "GET http://www.github.com HTTP/1.0\r\nUser-Agent: WebBench 1.0\r\nHost: www.github.com\r\nPragma: no-cache\r\nConnection: close\r\n\r\n");
				send(fd, buffer, strlen(buffer)+1,0);

				// recv data
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
				}

				close(fd);
				return 0;
}
