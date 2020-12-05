/*************************************************
 Layer 2 header file 
**************************************************/


#ifndef _HDR_LAYER2_
#define _HDR_LAYER2_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct mac_addr {
		char mac[6];
		} __attribute__((packed));;

typedef struct mac_addr mac_addr_t;


struct eth_hdr {
		mac_addr_t 	dest_mac;
		mac_addr_t 	src_mac;
		uint16_t 	type;
		char		data[256]; /*MAX can be 1500 */
		uint32_t	fcs;
} __attribute__((packed));;

typedef struct eth_hdr eth_hdr_t;


struct vlan_hdr {
                uint16_t  proto_id; /* 0x8100 */
                uint16_t  priority:3;
                uint16_t  del:1;
                uint16_t  vlan_id:12;
} __attribute__((packed));

typedef struct vlan_hdr vlan_hdr_t;

struct eth_vlan_hdr {
                    mac_addr_t  dest_mac;
                    mac_addr_t  src_mac;
                    vlan_hdr_t  vlan;
                    uint16_t    type;
                    char        data[256];
                    uint32_t    fcs;
} __attribute__((packed));;

typedef struct eth_vlan_hdr eth_vlan_hdr_t;

#define PROTO_8021Q_ID 0x8100

inline vlan_hdr_t * is_pkt_tagged (eth_hdr_t *eth_hdr)
{
  vlan_hdr_t *vlan_hdr = (vlan_hdr_t *)(eth_hdr + (sizeof(mac_addr_t) * 2));

  if (vlan_hdr->proto_id == PROTO_8021Q_ID) {
    return vlan_hdr;
  }
  return NULL;
}

#endif
