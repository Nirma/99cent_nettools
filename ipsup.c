//
//  ipsup.c
//  ipsup
//
//  Created by Nicholas Maccharoli on 11/27/15.
//  Copyright © 2015 Nicholas Maccharoli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, const char * argv[]) {
  
    int status;
    struct addrinfo hints, *servinfo, *p;
    char ipster[INET6_ADDRSTRLEN];
    const char *port = argc >= 3 ? argv[2] : "80";
    const char *address = argv[1];
    
    if (argc < 2) {
        fprintf(stderr, "Usage: ipsub [IP or Domain] (Optional: Port)\n");
        exit(EXIT_FAILURE);
    }
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    if ((status = getaddrinfo(address, port, &hints, &servinfo)) != 0){
        printf("IP Lookup error: %s", gai_strerror(status));
    }
    
    for (p = servinfo; p != NULL; p = p->ai_next) {
        
        char *ipVersion = NULL;
        void *addr = NULL;
        
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipVersion = "IP V4";
        }
        
        if (p->ai_family == AF_INET6) {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipVersion = "IP V6";
        }
        
        inet_ntop(p->ai_family, addr, ipster, sizeof ipster);
        
        printf("%s: %s\n", ipVersion, ipster);
    }
    
    freeaddrinfo(servinfo);
    return 0;
}

