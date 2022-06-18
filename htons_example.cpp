#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <bits/stdint-uintn.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(){
int port = 90;
// host to net short
// 主机字节序转网络字节序（短整形）
uint16_t temp = htons((uint16_t)port);
std::cout<<"host to net:"<<temp<<std::endl;
// net to host short
// 网络字节序转主机字节序(长整形)

temp = ntohs(temp);
std::cout<<"net to host:"<<temp<<std::endl;

/****IP地址的转换****/
// 需要用宏定义指定数组长度，才能够正确转换
char ip[INET6_ADDRSTRLEN]={'1','9','2','.','1','6','8','.','1','.','1'};
unsigned char dst[sizeof(struct in6_addr)];
std::cout<<inet_pton(AF_INET,ip,dst)<<std::endl;
printf("%s\n",ip);
return 0;
}
