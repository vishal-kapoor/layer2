
/*******************************************
 *
 *      Filename:     arp.c
 *      Description:  Sample ARP API implementation 
 *      Version:      1.0
 *      Author:       Vishal Kapoor
 *
 *******************************************/
#include "arp.h"
#include "../layer2.h"

/* initialize the arp table */
void init_arp_table(arp_table_t **arp_table)
{
    *arp_table = calloc(1, sizeof(arp_table_t));

}

/* Add entry to the ARP table */
bool arp_table_entry_add(arp_table_t **arp_table, arp_entry_t *new_entry)

{
  /* if entry exists already in the table */

  if (arp_table_entry_lookup(new_entry->ip_addr.ip_addr))
  {
    /*TODO: do not update entry as of now, will add in the future*/
    return false;
  }


  /*create a new entry at the head */
  new_entry->next = arp_table->arp_entry_head->next;
  arp_table->arp_entry_head = new_entry;
  /* increase number of entries*/
  arp_table->num_of_nodes++;

  return true;

}

bool arp_table_entry_del(arp_table_t *arp_table, char  *ip_addr)
{
  arp_entry_t *tmp = arp_table->arp_entry_head;
  if (!num_of_nodes)
  {
    printf("ARP table is empty");
    return false;
  }
  /* if entry is at the head (first entry in the table)*/
  if (memcmp(arp_table->arp_entry_head->ip_addr.ip_addr,ip_addr, sizeof(ip_addr)) == 0)
  {
    arp_table->arp_entry_head = arp_table->arp_entry_head->next;
    free(tmp);
    return true;

  }

  /* if entry is in the middle */
  while(tmp->next)
  {
    if (0 == memcmp(tmp->next->ip_addr.ip_addr, ip_addr, sizeof(ip_addr)))
    {
      arp_entry_t *delete_entry = tmp->next;
      tmp->next = tmp->next->next;
      free(delete_entry);
      return true;
    }
    tmp = tmp->next;
  }
  return false;

}
bool
arp_table_entry_lookup(arp_table_t *arp_table, char *ip_addr)
{
  arp_entry_t *tmp = arp_table->arp_entry_head;
  while (!tmp)
  {
    if (memcmp(ip_addr, tmp->ip_addr.ip_addr, sizeof(ip_addr)) == 0)
    {
      return true;
    }
    tmp = tmp->next;
  }
  return false;

}

 
