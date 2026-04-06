#include "ip_router.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

bool ip_string_to_uint32(const char* ip_str, uint32_t* ip_int)
{
    struct in_addr addr;
    if(inet_pton(AF_INET, ip_str, &addr) != 1)
    {
        return false;
    }

    *ip_int = addr.s_addr;
    return true;
}

void ip_uint32_to_string(uint32_t ip_int, char* buffer)
{
    struct in_addr addr;
    addr.s_addr = ip_int;
    strcpy(buffer,inet_ntoa(addr));
}

uint32_t generate_random_ip(void)
{
    uint8_t bytes[4];
    for(int i = 0; i < 4; i++)
    {
        bytes[i] = rand() % 256;
    }

    uint32_t ip_host = (bytes[0] << 24 ) | 
    bytes[1] << 16 |
    (bytes[2] << 8) | 
    bytes[3];

    return htonl(ip_host);
}

bool is_ip_subnet(uint32_t ip, uint32_t network, uint32_t mask)
{
    return (ip & mask) == (network & mask);
}

bool parse_subnet_mask(const char* mask_str, uint32_t* mask)
{
    if(mask_str[0] == '/')
    {
        int prefix_len = atoi(mask_str + 1);

        if(prefix_len < 0 || prefix_len > 32)
        {
            fprintf(stderr, "Ошибка: префикс от 0 до 32\n");
            return false;
        }

        if(prefix_len == 0)
        {
            *mask = 0;
        }else{
            uint32_t host_mask = 0xFFFFFFFF << (32 - prefix_len);
            *mask = htonl(host_mask);
        }
        return true;
    }
    struct in_addr addr;
    if(inet_pton(AF_INET, mask_str, &addr) == 1)
    {
        *mask = addr.s_addr;
        return true;
    }
    fprintf(stderr, "Ошибка: неверный формат маски '%s'\n", mask_str);
    fprintf(stderr, "Поддерживаемые форматы: 255.255.255.0или /24 \n");
    return false;
}