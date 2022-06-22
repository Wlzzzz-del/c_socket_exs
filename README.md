# C-Socket编程的一些实例小程序
+ service.cpp 实现了基于tcp的服务端
+ client.cpp 基于tcp实现了一个客户端能够和service.cpp的服务端进行交互
+ link.cpp 尝试与百度建立tcp连接，并且组装和发送http请求报文
+ socket.cpp 封装了一个socket函数，传入两个参数主机号与端口后返回创建并连接至服务端的socket标识符.准备用于实现webbench.
+ htons_example.cpp 主要对主机字节序与网络字节序之间的转换做了实验
+ thread.cpp 使用多线程与互斥锁实现了创建与管理多个socket进行网络测压
