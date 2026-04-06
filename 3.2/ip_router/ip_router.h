#ifndef IP_ROUTER_H
#define IP_ROUTER_H

#include <stdint.h>
#include <stdbool.h>

#define IP_STR_LEN 16

bool ip_string_to_uint32(const char* ip_str, uint32_t* ip_int);

void ip_uint32_to_string(uint32_t ip_int , char* buffer);

uint32_t generate_random_ip(void);

bool is_ip_subnet(uint32_t ip, uint32_t network, uint32_t mask);

bool parse_subnet_mask(const char* mask_str, uint32_t* mask);

#endif