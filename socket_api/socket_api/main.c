//
//  main.c
//  socket_api
//
//  Created by mac on 17/05/2019.
//  Copyright © 2019 mac. All rights reserved.
//

#include <stdio.h>


struct  xxx {
    int  age;
    char* name;
} st;


void v(struct  xxx* x){
    printf("%ld\n",sizeof(x));
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    v(&st);
    return 0;
}



