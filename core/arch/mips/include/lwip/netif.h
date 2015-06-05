#ifndef __FAKE_LWIP_NETIF_H__
#define __FAKE_LWIP_NETIF_H__

struct netif;

typedef int (*netif_status_callback_fn)();

static inline int netif_is_up(struct netif *nf) {
    return 0;
}

#endif //__FAKE_LWIP_NETIF_H__
