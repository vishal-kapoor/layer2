
/********************************************
 *      Filename:     arp.h
 *      Description:  Sample ARP implementation 
 *      Version:      1.0
 *      Author:       Vishal Kapoor
 *
 *
 *    ARP ethernet packet format
 *    [DST MAC][SRC MAC][TYPE 806][payload][FCS] 
 *      6B       6B        2B      46-1500  4B
 *
 *    ARP payload
 *    [hw type][proto type][hw address length][proto address length][OPCODE][SRC MAC][SRC IP][TARGET MAC][TARGET IP]
 *
 *  ARP table
 *  [IP Address]  [MAC Address]  [Outgoing Interface]
 */


#ifndef ARP_H
#define ARP_H

#include "../layer2.h"

/*ARP header */
struct arp_hdr {
                            uint16_t    hw_type;
                            uint16_t    proto_type;
                            uint8_t     hw_addr_len;
                            uint8_t     protp_addr_len;
                            uint16_t    op_code;
                            mac_addr_t  src_mac;
                            uint32_t    src_ip;
                            mac_addr_t  target_mac;
                            uint32_t    target_ip;
} __attribute__((packed));

typedef struct arp_hdr arp_hdr_t;

/* ARP entry in the ARP table */
typedef struct arp_entry {
                          ip_addr_t         ip_addr;
                          mac_addr_t        mac_addr;
                          interface_t       oif;
                          struct arp_entry  *next;
}arp_entry_t;
                            
typedef struct arp_table {
                          arp_entry_t       *arp_entry_head;
                          uint32_t          num_of_nodes;
}arp_table_t;


/* Function declarations */

void
init_arp_table(arp_table_t **arp_table);

bool 
arp_table_entry_add(arp_table_t **arp_table, arp_entry_t *new_entry);

bool 
arp_table_entry_del(arp_table_t **arp_table, char *ip_addr);

bool 
arp_table_entry_update(arp_table_t **arp_table, arp_entry_t *arp_entry);

arp_entry_t *
arp_table_entry_lookup(arp_table_t *arp_table, char *ip_addr);

void 
dump_arp_table(arp_table_t *arp_table);

#endif
