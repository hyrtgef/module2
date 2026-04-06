#include "ip_router.h"
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        printf("Примеры:\n");
        printf("%s 192.168.1.1 255.255.255.0 100\n", argv[0]);
        printf("%s 192.168.1.1 /24 100\n", argv[0]);
        printf("%s 10.0.0.1 255.255.255.255 50 (маска /32)\n", argv[0]);
        printf("%s 10.0.0.1 /32 50 \n", argv[0]);
        printf("%s 192.168.1.1 0.0.0.0 50 (Маска /0)\n", argv[0]);
        printf("%s 192.168.1.1 /0 50 \n", argv[0]);
        return 1;
    }

    char* getaway_str = argv[1];
    char* mask_str = argv[2];
    int N = atoi(argv[3]);

    if( N <= 0)
    {
        fprintf(stderr, "Ошибка: колличество пакетов N должно быть положительным числом\n");
        return 1;
    }

    uint32_t gateway_ip; 
    if(!ip_string_to_uint32(getaway_str, &gateway_ip))
    {
        fprintf(stderr, "Ошибка: неверный формат IP адреса шлюза '%s'\n", getaway_str);
        return 1;
    }

    uint32_t mask;
    if(!parse_subnet_mask(mask_str, &mask))
    {
        return 1;
    }

    uint32_t network_addr = gateway_ip & mask;

    char gateway_display[IP_STR_LEN];
    char mask_display[IP_STR_LEN];
    char network_display[IP_STR_LEN];

    ip_uint32_to_string(gateway_ip, gateway_display);
    ip_uint32_to_string(mask, mask_display);
    ip_uint32_to_string(network_addr, network_display);

    printf("IP адрес шлюза: %s\n", gateway_display);
    printf("Маска подсети: %s\n" , mask_display);
    printf("Адрес сети: %s\n",network_display);
    printf("Колличество пакетов: %d\n", N);

    srand(time(NULL));

    int same_subnet = 0;
    int other_subnet = 0;

    for(int i = 0; i < N ; i++)
    {
        uint32_t dest_ip = generate_random_ip();

        bool in_subnet = is_ip_subnet(dest_ip, network_addr, mask);

        char dest_display[IP_STR_LEN];
        ip_uint32_to_string(dest_ip, dest_display);

        printf("Пакет: %4d: %15s  -> %s\n",
        i + 1,
        dest_display,
        in_subnet ? "Своя подсеть" : "Другая подсеть");
    
        if(in_subnet)
        {
            same_subnet++;
        }
        else{
            other_subnet++;
        }
    }

    printf("Всего обработано сигналов: %d\n", N);
    printf("Пакетов для СВОЕЙ подсети: %4d шт. (%5.lf%%)\n", 
    same_subnet,
    (double)same_subnet / N * 100.0);
    printf("Пакеты для других сетей: %4d шт. (%5.lf%%)\n",
    other_subnet,
    (double)other_subnet / N * 100.0);
    return 0;
}