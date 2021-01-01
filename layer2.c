#include <stdio.h>
#include "layer2.h"


inline bool l2_inf_check(interface_t *inf, eth_hdr_t *eth_hdr)
{
  uint16_t out_vlan_id = 0;

  vlan_hdr_t *vlan_hdr = is_pkt_tagged(eth_hdr);

  /* if in ACCESS mode and no vlan assiged then return */
  if (IF_L2_MODE(inf) == ACCESS && 
      get_vlan_from_interface(inf)){
    return FALSE;
  }
  
  /* in ACCESS mode and vlan configured */
  uint16_t inf_vlan = 0;
  uint16_t pkt_vlan = 0;
  if (IF_L2_MODE(inf) == ACCESS) {
        inf_vlan = get_vlan_from_interface(inf);
        if (!vlan_hdr && inf_vlan) {
          out_vlan_id = inf_vlan;
          return TRUE;
        }
        pkt_vlan = GET_VLAN_ID(vlan_hdr);
        if (pkt_vlan == inf_vlan) {
            /* if interface vlan is same */
            return TRUE;
        } else 
            return FALSE;
  }
  if (IF_L2_MODE(inf) == TRUNK) {
      if (!vlan_hdr) {
        /* if pkt is not tagged return */
          return FALSE;
      }

  }
  /* trunk mode and tagged packet */
  if (IF_L2_MODE(inf) == TRUNK && vlan_hdr) {
    pkt_vlan = GET_VLAN_ID(vlan_hdr);
    if (is_inf_vlan_range(inf, pkt_vlan)){
      return TRUE;
    } else {
      return FALSE;
    }
  }
  /* L3 mode and vlan tagged packet received, drop */
  if (IF_L3_MODE(inf) && vlan_hdr) {
    return FALSE;
  }
  /* if L3 mode and dst_mac == interface mac */
  if (IF_L3_MODE(inf) && (memcmp(IF_MAC(inf), eth_hdr->dst_mac.mac, sizeof(mac_addr_t)) == 0)) {
    return TRUE;
  }

  /* accept broadcast frames also */
  if (IF_L3_MODE(inf) && IS_BCAST_MAC(eth_hdr->dst_mac.mac)) {
    return TRUE;
  }
     
 return FALSE;

}

bool layer2_frame_recv(interface_t *inf, char *pkt, uint32_t pkt_size)
{
  eth_hdr_t *eth_hdr = (eth_hdr_t *) pkt;

  /* Basic check for the interface properties */
  l2_inf_check(inf, eth_hdr);

  if (IF_L3_INTERFACE(inf)) {
      send_to_upper_layer(pkt);
  } else if (IF_L2_MODE(inf) == ACCESS || 
            IF_L2_MODE(inf) == TRUNK ) {
          l2_frame_recv(inf, pkt);
  } else
          return; /* drop packet */
}


