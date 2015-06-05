#ifndef __FAKE_LWIP_IPADDR_H__
#define __FAKE_LWIP_IPADDR_H__

struct ip_addr_t;
typedef  struct ip_addr_t  ip_addr_t;

static inline int ipaddr_aton(void *buf, ip_addr_t *addr) {
    printk("ipaddr_aton() called, TODO\n");
    return -NOT_FOUND;
}

#endif //__FAKE_LWIP_IPADDR_H__
