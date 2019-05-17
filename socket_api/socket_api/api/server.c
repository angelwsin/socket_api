//
//  server.c
//  socket_api
//
//  Created by mac on 17/05/2019.
//  Copyright © 2019 mac. All rights reserved.
//

#include "server.h"


#include<sys/socket.h>
#include<netinet/in.h>
#include <string.h>

/**
 每个协议族族中都定义了自己的套接字地址结构
 套接字地址结构：sockaddr_开头，每个协议族唯一后缀结尾
 
       通用的地址结构为了函数可以接受任何不同的地址   sockaddr 调用bind等需要强转
       导致的原因是c规范当时还没有void * 
 ipv4  的地址结构  sockaddr_in  网际套接字地址结构
 ipv6  的地址结构  sockaddr_in6
 
 */


int sockettest(){
    /*
     三个参数对应不同含义：
     1）地址族  决定了socket的地址类型 ipv4  ipv6
     2）指定socket类型   SOCK_STREAM是基于TCP的，数据传输比较有保障。SOCK_DGRAM是基于UDP的
     3）指定协议  IPPROTO_TCP IPPROTO_UDP 等
     */
    
    int sockfd ;
    //当我们调用socket创建一个socket时，返回的socket描述字它存在于协议族（address family，AF_XXX）空间中，但没有一个具体的地址。如果想要给它赋值一个地址，就必须调用bind()函数
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in my_addr;/*本方地址信息结构体，下面有具体的属性赋值*/
    
    my_addr.sin_family = AF_INET;/*该属性表示接收本机或其他机器传输*/
    my_addr.sin_port = 2992;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);/*IP，括号内容表示本机IP*/
    //将指针变量 s 所指向的前 n 字节的内存单元用一个“整数” c 替换
    memset(&(my_addr.sin_zero),0,8);/*将其他属性置0*/
    int socket_addr_len = sizeof(struct sockaddr);
    bind(sockfd, (struct sockaddr*)&my_addr,socket_addr_len);
    //第二个参数 socket可以排队的最大连接个数
    listen(sockfd, 10);
    while(1){
        int acc =  accept(sockfd, (struct sockaddr*)&my_addr,(socklen_t *)&socket_addr_len);
        struct msghdr msg ;
        recvmsg(acc, &msg, 0);
    }
    return 0;
}
