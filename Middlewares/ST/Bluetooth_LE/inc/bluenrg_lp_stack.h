#ifndef BLUENRGLP_STACK_H
#define BLUENRGLP_STACK_H
/**
  ******************************************************************************
 * @file    bluenrg_lp_stack.h
  * @author  AMS - RF Application team
 * @brief   Header file for BlueNRG-LP Bluetooth LE stack
 *
  ******************************************************************************
  * @attention
  *
 * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
  *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
  ******************************************************************************
  */
#include <stdint.h>
#include "ble_status.h"
#include "bluenrg_lp_api.h"
#include "bluenrg_lp_events.h"

#define MIN(a,b)                        (((a) < (b))? (a) : (b))
#define MAX(a,b)                        (((a) > (b))? (a) : (b))
#define DIV_CEIL(x, y)                  (((x) + (y) - 1) / (y))

/** 
 * BLE_STACK_DEFAULT_ATT_MTU: minimum mtu value that GATT must support.
 * 5.2.1 ATT_MTU, BLUETOOTH SPECIFICATION Version 4.2 [Vol 3, Part G]
 */
#define BLE_STACK_DEFAULT_ATT_MTU                 (23U)

#define BLE_STACK_MEM_BLOCK_SIZE                  (32U)


/**
 * @name  BLE_STACK_L2CAP_MPS_OCTETS
 * @brief Minimum and Maximum supported MPS values for L2CAP component.
 * @see   BLE Spec. v.5.2, Vol.3, Part A, Sec.4.1, Table 4.1
 * @{
 */
#define BLE_STACK_L2CAP_MPS_OCTETS_MIN             (23U)
#define BLE_STACK_L2CAP_MPS_OCTETS_MAX             (1024U) /* MPS limited to 1KB */
/**
 * @}
 */


/**
 * BLE_STACK_SM_SECURE_CONN_MTU: mtu size needed for Security Manager Channel Configuration
 * Parameters with LE Secure Connections.
 * 3.2 SECURITY MANAGER CHANNEL OVER L2CAP, BLUETOOTH SPECIFICATION Version 4.2
 * [Vol 3, Part H]
 */
#define BLE_STACK_SM_SECURE_CONN_MTU              (65U)

/*
 * BLE_STACK_MAX_ATT_MTU: maximum supported ATT_MTU size.
 */
#define BLE_STACK_MAX_ATT_MTU                     (1024U - 4U)  // (4 bytes for L2CAP header)

/**
 * BLE_STACK_DEFAULT_MAX_ATT_MTU: default max ATT_MTU size.
 */
#define BLE_STACK_DEFAULT_MAX_ATT_MTU             (251U - 4U) // (4 bytes for L2CAP header)

/**
 * BLE_STACK_DEFAULT_MAX_ATT_SIZE: maximum attribute size.
 */
#define BLE_STACK_DEFAULT_MAX_ATT_SIZE            (512U)

/**
 * BLE_STACK_MEM_BLOCK_X_MTU(mtu, n_links): compute how many memory blocks are needed to
 * support a maximum number (n_links)of simultaneous connections that use ATT
 * packet with ATT_MTU=mtu.
 * 7.2 FRAGMENTATION AND RECOMBINATION, BLUETOOTH SPECIFICATION Version 4.2
 * [Vol 3, Part A]
 */

#define BLE_STACK_MEM_BLOCK_X_TX(mtu)             (DIV_CEIL((mtu) + 4U, BLE_STACK_MEM_BLOCK_SIZE) + 1U)
#define BLE_STACK_MEM_BLOCK_X_RX(mtu, n_link)     ((DIV_CEIL((mtu) + 4U, BLE_STACK_MEM_BLOCK_SIZE) + 2U) * (n_link) + 1U)
#define BLE_STACK_MEM_BLOCK_X_MTU(mtu, n_link)    (BLE_STACK_MEM_BLOCK_X_TX(mtu) + BLE_STACK_MEM_BLOCK_X_RX(mtu, n_link))

/**
 * Minimum number of blocks required for secure connections
 */
#define BLE_STACK_MBLOCKS_SECURE_CONNECTIONS      (4U)

/**
 * BLE_STACK_MBLOCKS_CALC(mtu, n_link): minimum number of buffers needed by the stack.
 * This is the minimum racomanded value and depends on:
 *  - mtu: ATT_MTU size
 *  - n_link: maximum number of simultaneous connections
 */
#define BLE_STACK_MBLOCKS_CALC(mtu, n_link)       MAX(BLE_STACK_MEM_BLOCK_X_MTU(mtu, n_link), BLE_STACK_MBLOCKS_SECURE_CONNECTIONS)

/**
 * Default memory blocks count
 */
#define BLE_STACK_DEFAULT_MBLOCKS_COUNT           BLE_STACK_MBLOCKS_CALC(BLE_STACK_DEFAULT_MAX_ATT_MTU, BLE_STACK_NUM_LINKS)

/**
 * Amount of memory used for each GATT attribute entry.
 */
#define BLE_STACK_GATT_ATTRIBUTE_SIZE                       (8U)

/**
 * Number of GATT attributes used for mandatory profiles (GATT and GAP).
 */
#define BLE_STACK_NUM_GATT_MANDATORY_ATTRIBUTES             (17U)

/**
 * Amount of memory needed by each GATT Client procedure context
 */
#define COEFF_NUM_GATT_CLIENT_PROCS (36U)

/**
 * Amount of memory needed by GATT when connection support is enabled
 */
#define BLE_STACK_GATT_SIZE(CONN_SUPP_EN, GATT_ATTRIBUTES, GATT_CLIENT_PROCS) \
    (((CONN_SUPP_EN) == 1U) ? BLE_STACK_GATT_ATTRIBUTE_SIZE * (GATT_ATTRIBUTES) + COEFF_NUM_GATT_CLIENT_PROCS * (GATT_CLIENT_PROCS) : 0U)

/**
 * A part of the RAM, is dinamically allocated by initializing all the pointers
 * defined in a global context variable "mem_alloc_ctx_p".
 * This initialization is made in the Dynamic_allocator functions, which
 * assing a portion of RAM given by the external application to the above
 * mentioned "global pointers".
 *
 * The size of this Dynamic RAM is made of 2 main components:
 * - a part that is parameters-dependent (num of links, GATT buffers, ...),
 *   and whose value is explicited by the following macros BLE_STACK_*_SIZE;
 * - a part, that may be considered "fixed", i.e., independent from the above
 *   mentioned parameters.
*/
#define BLE_STACK_FIXED_BUFFER_SIZE_BYTES (1498U)

/**
 * Amount of memory needed by each radio link
 */
#   define COEFF_CONN_SUPP_EN   (752U + BLE_STACK_GATT_ATTRIBUTE_SIZE * BLE_STACK_NUM_GATT_MANDATORY_ATTRIBUTES)
#   define COEFF_NUM_OF_LINKS_0 (48U)  // [DB] scheduler's tasks
#   define COEFF_NUM_OF_LINKS_1 (636U)
#   define BLE_STACK_LINKS_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) \
    (((CONN_SUPP_EN) == 1U) || ((NUM_OF_LINKS) > 0U) ? COEFF_CONN_SUPP_EN * (CONN_SUPP_EN) + COEFF_NUM_OF_LINKS_0 * (NUM_OF_LINKS) + COEFF_NUM_OF_LINKS_1 * (CONN_SUPP_EN) * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed for mem. blocks allocated for connections
 */
#define BLE_STACK_MBLOCK_SIZE(CONN_SUPP_EN, MEM_BLOCK_COUNT) (((CONN_SUPP_EN) == 1U) ? (4U + BLE_STACK_MEM_BLOCK_SIZE) * (MEM_BLOCK_COUNT) : 0U)

/**
 * Amount of memory needed to support PHY Update feature
 */
#define BLE_STACK_PHY_UPD_SIZE(CONN_SUPP_EN, PHY_UPD_EN, NUM_OF_LINKS) (((PHY_UPD_EN) == 1U) ? 8U + 48U * (CONN_SUPP_EN) * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed to support extended advertising and scanning feature. Note that if 
 * extended advertising is enabled the memory required by the legacy advertising set must be
 * subracted from the total
 */
#define BLE_STACK_CONTROLLER_EXT_ADV_SIZE(ENABLED, NUM_ADV_SET, NUM_AUX_EVENT, NUM_OF_LINKS) \
    (((ENABLED) == 1U) ? -292U + 384U * (NUM_ADV_SET) + 0U * (NUM_AUX_EVENT) + 0U * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed for the white list and, if connections are supported, also for connection ID list
 */
#define BLE_STACK_WHITE_LIST_SIZE(WL_SIZE_LOG2) (8U * (1U << (WL_SIZE_LOG2)))
#define BLE_STACK_CONN_ID_LIST_SIZE(CONN_SUPP_EN, WL_SIZE_LOG2) (((CONN_SUPP_EN) == 1U) ? BLE_STACK_WHITE_LIST_SIZE(WL_SIZE_LOG2) : 0U)

/**
 * Amount of memory needed to support L2CAP COCs (Connection Oriented Channels)
 */
#define BLE_STACK_L2C_COCS_SIZE(CONN_SUPP_EN, L2C_COS_EN, NUM_OF_COCS) (((CONN_SUPP_EN) == 1U) && ((L2C_COS_EN) == 1U) ? 76U * (NUM_OF_COCS) : 0U)

/**
 * Amount of memory needed to support Data Length Extension feature
 */
#define BLE_STACK_D_LEN_EXT_SIZE(LEN_EXT_ENABLED, ADV_EXT_ENABLED) ((((LEN_EXT_ENABLED) == 1U) | ((ADV_EXT_ENABLED) == 1U)) ? 440U : 0U)

/**
 * Amount of memory needed to support periodic advertising and synchronizing feature
 */
#define BLE_STACK_CONTROLLER_PERIODIC_ADV_SIZE(PER_ADV_EN, CONN_SUPP_EN, NUM_OF_LINKS, NUM_ADV_SET) \
    (((PER_ADV_EN) == 1U) ? 168U * (NUM_ADV_SET) + 32U * (CONN_SUPP_EN) * (NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed to support the master feature
 */
#define BLE_STACK_BASE_SIZE(CONN_SUPP_EN) (((CONN_SUPP_EN) == 1U) ? 32U : 20U)

#define BLE_STACK_PAST_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) ? 24U * (NUM_OF_LINKS) : 0U)
        
#define BLE_STACK_PER_SYNC_SIZE(PER_ADV_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE)\
    (((PER_ADV_EN) == 1U) ? BLE_STACK_BASE_SIZE(CONN_SUPP_EN) + 184U * (NUM_SYNC_SLOTS) + 8U * (1U << (ADV_LIST_LIZE)) + BLE_STACK_PAST_SIZE(CONN_SUPP_EN, NUM_OF_LINKS) : 0U)

#define BLE_STACK_CONTROLLER_MASTER_SIZE(MASTER_EN, EXT_ADV_EN, PER_ADV_EN, CONN_SUPP_EN, NUM_AUX_EVENT, NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE) \
    (((MASTER_EN) == 1U) ? 76U + (184U + 72U * (NUM_AUX_EVENT) + BLE_STACK_PER_SYNC_SIZE(PER_ADV_EN, CONN_SUPP_EN, NUM_SYNC_SLOTS, NUM_OF_LINKS, ADV_LIST_LIZE)) * (EXT_ADV_EN) : 0U)

/**
 * Amount of memory needed to support controller privacy feature
 */
#define BLE_STACK_CONTROLLER_PRIV_SIZE(ENABLED, WHITE_LIST_SIZE_LOG2) (((ENABLED) == 1U) ? 8U + 80U * (1U << (WHITE_LIST_SIZE_LOG2)) : 0U)

/**
 * Amount of memory needed to support CTE feature
 */
#define BLE_STACK_CTE_NUM_OF_LINKS(CONN_SUPP_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) ? 8U * (NUM_OF_LINKS) : 0U)
#define BLE_STACK_CTE_NUM_OF_ANT_IDS(CONN_SUPP_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS)\
    (((NUM_OF_ANT_IDS) > 0U) ? (1U + 0U * (CONN_SUPP_EN) * (NUM_OF_LINKS)) * (1U + (((NUM_OF_ANT_IDS) - 1U) | 3U)) : 0U)
    /** In the macro above, note that:
     *  - the contribution associated with the nr. of links is 0 because the macro CONN_ANT_PATT is not defined
     *  - the contribution associated with the nr. of antenna IDs is adapted to the word alignment
     */
#define BLE_STACK_CTE_NUM_OF_IQ_SAMPLES(NUM_OF_IQSAMPLES) (4U * (NUM_OF_IQSAMPLES))
#define BLE_STACK_CTE_TIMER(MASTER_EN, EXT_ADV_EN, PER_ADV_EN, NUM_OF_IQSAMPLES) \
        ((((MASTER_EN) == 1U) && ((EXT_ADV_EN) == 1U) && ((PER_ADV_EN) == 1U) && ((NUM_OF_IQSAMPLES) > 0U)) ? 24U : 0U)

#define BLE_STACK_CTE_SIZE(MASTER_EN, EXT_ADV_EN, PER_ADV_EN, CONN_SUPP_EN, CTE_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS, NUM_OF_IQSAMPLES) \
    (((CTE_EN) == 1U) ? 12U + \
                        BLE_STACK_CTE_NUM_OF_LINKS(CONN_SUPP_EN, NUM_OF_LINKS) + \
                        BLE_STACK_CTE_NUM_OF_ANT_IDS(CONN_SUPP_EN, NUM_OF_LINKS, NUM_OF_ANT_IDS) + \
                        BLE_STACK_CTE_NUM_OF_IQ_SAMPLES(NUM_OF_IQSAMPLES) + \
                        BLE_STACK_CTE_TIMER(MASTER_EN, EXT_ADV_EN, PER_ADV_EN, NUM_OF_IQSAMPLES) : \
                                                                                      0U)

/**
 * Amount of memory needed to support PCL feature
 */
#define BLE_STACK_PCL_NUM_OF_LINKS(NUM_OF_LINKS)  (32U * (NUM_OF_LINKS))
#define BLE_STACK_PCL_SIZE(CONN_SUPP_EN, PCL_EN, NUM_OF_LINKS) (((CONN_SUPP_EN) == 1U) && ((PCL_EN) == 1U) ? 20U + BLE_STACK_PCL_NUM_OF_LINKS(NUM_OF_LINKS) : 0U)

/**
 * Amount of memory needed by FIFOs
 */
#define CALC_FIFO_SIZE(FS) ((((FS) + 3U) >> 2U) << 2U)
#define BLE_STACK_FIFO_SIZE(ISR0_FS, ISR1_FS, USER_FS) (CALC_FIFO_SIZE(ISR0_FS) + CALC_FIFO_SIZE(ISR1_FS) + CALC_FIFO_SIZE(USER_FS))

/**
 *
 * This macro returns the amount of memory, in bytes, needed for the storage of GATT database elements
 * and other data structures whose size depends on the number of supported connections.
 *
 * @param BLE_STACK_NUM_LINKS: Maximum number of simultaneous connections that the device will support. 
 * @param BLE_STACK_NUM_GATT_ATTRIBUTES: Maximum number of Attributes (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services) that can be stored in the GATT database. Note that certain characteristics and relative descriptors are added automatically during device initialization so this parameters should be 9 plus the number of user Attributes
 * @param BLE_STACK_NUM_GATT_CLIENT_PROCS: Maximum number of concurrent GATT Client Procedures.
 * @param BLE_STACK_MBLOCKS_COUNT: Number of memory blocks allocated for packets.
 * @param BLE_STACK_D_LEN_EXT_EN: Enable or disable the Extended Packet length feature. Valid values are 0 or 1.
 * @param BLE_STACK_PHY_UPD_EN: Enable or disable the PHY Update feature. Valid values are 0 or 1.
 * @param BLE_STACK_EXT_ADV_SCAN_EN: Enable or disable the Extended Advertising and Scan feature. Valid values are 0 or 1.
 * @param BLE_STACK_CTRL_PRIV_EN: Enable or disable the Controller privacy feature. Valid values are 0 or 1.
 * @param BLE_STACK_SEC_CONN_EN: Enable or disable the secure connection feature. Valid values are 0 or 1.
 * @param BLE_STACK_MASTER_EN: Enable or disable the Master role feature. Valid values are 0 or 1.
 * @param NUM_ADV_SET: Number of advertising set.
 * @param NUM_AUX_EVENT: Number of auxiliary events.
 * @param WHITE_LIST_SIZE_LOG2: log2 ceiling of white list size.
 * @param BLE_STACK_L2CAP_COS_EN:
 * @param NUM_L2CAP_COCS:
 * @param BLE_STACK_CTE_EN: Enable or disable the CTE feature. Valid values are 0 or 1.
 * @param NUM_CTE_ANT_IDS: Maximum antenna switching pattern length 
 * @param NUM_CTE_IQSAMPLES: Maximum number of IQ-Samples in the buffer
 * @param BLE_STACK_PCL_EN: Enable or disable the Power Control & Path Loss Monitoring feature. Valid values are 0 or 1.
 * @param BLE_STACK_CONN_SUPP_EN: Enable or disable the support of ACL connections.
 * @param ISR0_FIFO_SIZE: Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets)
 * @param ISR1_FIFO_SIZE: Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports)
 * @param USER_FIFO_SIZE: Size of the internal FIFO used for controller and host events produced outside the ISR
 */
#define BLE_STACK_TOTAL_BUFFER_SIZE_EXT(\
    BLE_STACK_NUM_LINKS,\
    BLE_STACK_NUM_GATT_ATTRIBUTES,\
    BLE_STACK_NUM_GATT_CLIENT_PROCS,\
    BLE_STACK_MBLOCKS_COUNT,\
    BLE_STACK_D_LEN_EXT_EN,\
    BLE_STACK_PHY_UPD_EN,\
    BLE_STACK_EXT_ADV_SCAN_EN,\
    BLE_STACK_CTRL_PRIV_EN,\
    BLE_STACK_SEC_CONN_EN,\
    BLE_STACK_MASTER_EN,\
    NUM_ADV_SET,\
    NUM_AUX_EVENT,\
    WHITE_LIST_SIZE_LOG2,\
    BLE_STACK_L2CAP_COS_EN,\
    NUM_L2CAP_COCS,\
    CONTROLLER_PERIODIC_ADV_EN,\
    NUM_SYNC_SLOTS,\
    BLE_STACK_CTE_EN,\
    NUM_CTE_ANT_IDS,\
    NUM_CTE_IQSAMPLES,\
    BLE_STACK_PCL_EN,\
    BLE_STACK_CONN_SUPP_EN,\
    ISR0_FIFO_SIZE,\
    ISR1_FIFO_SIZE,\
    USER_FIFO_SIZE)\
(\
  BLE_STACK_FIXED_BUFFER_SIZE_BYTES                                                                             + \
  BLE_STACK_LINKS_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_NUM_LINKS)                                             + \
  BLE_STACK_GATT_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_NUM_GATT_ATTRIBUTES, BLE_STACK_NUM_GATT_CLIENT_PROCS)   + \
  BLE_STACK_MBLOCK_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_MBLOCKS_COUNT)                                        + \
  BLE_STACK_D_LEN_EXT_SIZE(BLE_STACK_D_LEN_EXT_EN, BLE_STACK_EXT_ADV_SCAN_EN)                                   + \
  BLE_STACK_PHY_UPD_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_PHY_UPD_EN, BLE_STACK_NUM_LINKS)                     + \
  BLE_STACK_CONTROLLER_EXT_ADV_SIZE(BLE_STACK_EXT_ADV_SCAN_EN, NUM_ADV_SET, NUM_AUX_EVENT, BLE_STACK_NUM_LINKS) + \
  BLE_STACK_WHITE_LIST_SIZE(WHITE_LIST_SIZE_LOG2)                                                               + \
  BLE_STACK_CONN_ID_LIST_SIZE(BLE_STACK_CONN_SUPP_EN, WHITE_LIST_SIZE_LOG2)                                     + \
  BLE_STACK_CONTROLLER_PRIV_SIZE(BLE_STACK_CTRL_PRIV_EN, WHITE_LIST_SIZE_LOG2)                                  + \
  (0U * (BLE_STACK_SEC_CONN_EN))                                                                                + \
  BLE_STACK_CONTROLLER_MASTER_SIZE(                                                                               \
    BLE_STACK_MASTER_EN, BLE_STACK_EXT_ADV_SCAN_EN, CONTROLLER_PERIODIC_ADV_EN, BLE_STACK_CONN_SUPP_EN,           \
    NUM_AUX_EVENT, NUM_SYNC_SLOTS, BLE_STACK_NUM_LINKS, WHITE_LIST_SIZE_LOG2)                                   + \
  BLE_STACK_L2C_COCS_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_L2CAP_COS_EN, NUM_L2CAP_COCS)                       + \
  BLE_STACK_CONTROLLER_PERIODIC_ADV_SIZE(                                                                         \
    CONTROLLER_PERIODIC_ADV_EN, BLE_STACK_CONN_SUPP_EN, BLE_STACK_NUM_LINKS, NUM_ADV_SET)                       + \
  BLE_STACK_CTE_SIZE(\
    BLE_STACK_MASTER_EN, BLE_STACK_EXT_ADV_SCAN_EN, CONTROLLER_PERIODIC_ADV_EN, BLE_STACK_CONN_SUPP_EN,           \
    BLE_STACK_CTE_EN, BLE_STACK_NUM_LINKS, NUM_CTE_ANT_IDS, NUM_CTE_IQSAMPLES)                                  + \
  BLE_STACK_PCL_SIZE(BLE_STACK_CONN_SUPP_EN, BLE_STACK_PCL_EN, BLE_STACK_NUM_LINKS)                             + \
  BLE_STACK_FIFO_SIZE(ISR0_FIFO_SIZE, ISR1_FIFO_SIZE, USER_FIFO_SIZE)                                             \
)

/**
 *
 * This macro acts like the BLE_STACK_TOTAL_BUFFER_SIZE_EXT macro while makes use of the
 * modularity parameters defined in the bluenrgx_user_cfg.h file
 *
 * @param BLE_STACK_NUM_LINKS: Maximum number of simultaneous radio tasks that the device will support (Radio controller supports up to 128 simultaneous radio tasks, but actual usable max value depends 
on the available device RAM)
 * @param BLE_STACK_NUM_GATT_ATTRIBUTES: Maximum number of Attributes (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services) that can be stored in the GATT database. Note that certain characteristics and relative descriptors are added automatically during device initialization so this parameters should be 9 plus the number of user Attributes
 * @param BLE_STACK_NUM_GATT_CLIENT_PROCS: Maximum number of concurrent GATT Client Procedures.
 * @param BLE_STACK_MBLOCKS_COUNT: Number of memory blocks allocated for packets.
 * @param BLE_STACK_NUM_ADV_SET: Number of advertising set.
 * @param BLE_STACK_NUM_AUX_EVENT: Number of auxiliary scan slots.
 * @param BLE_STACK_WHITE_LIST_SIZE_LOG2: log2 ceiling of white list size.
 * @param BLE_STACK_NUM_L2CAP_COCS: number of L2CAP Connection Oriented Channels supported.
 * @param BLE_STACK_NUM_CTE_ANT_IDS: Maximum antenna switching pattern length . 
 * @param BLE_STACK_NUM_IQSAMPLES: Maximum number of IQ-Samples in the buffer.
 * @param ISR0_FIFO_SIZE: Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets).
 * @param ISR1_FIFO_SIZE: Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports).
 * @param USER_FIFO_SIZE: Size of the internal FIFO used for controller and host events produced outside the ISR.
 */
#define BLE_STACK_TOTAL_BUFFER_SIZE(\
    BLE_STACK_NUM_LINKS,\
    BLE_STACK_NUM_GATT_ATTRIBUTES,\
    BLE_STACK_NUM_GATT_CLIENT_PROCS,\
    BLE_STACK_MBLOCKS_COUNT,\
    BLE_STACK_NUM_ADV_SET,\
    BLE_STACK_NUM_AUX_EVENT,\
    BLE_STACK_WHITE_LIST_SIZE_LOG2,\
    BLE_STACK_NUM_L2CAP_COCS,\
    NUM_SYNC_SLOTS,\
    BLE_STACK_NUM_CTE_ANT_IDS,\
    BLE_STACK_NUM_IQSAMPLES,\
    ISR0_FIFO_SIZE,\
    ISR1_FIFO_SIZE,\
    USER_FIFO_SIZE)\
(\
    BLE_STACK_TOTAL_BUFFER_SIZE_EXT(\
        BLE_STACK_NUM_LINKS,\
        BLE_STACK_NUM_GATT_ATTRIBUTES,\
        BLE_STACK_NUM_GATT_CLIENT_PROCS,\
        BLE_STACK_MBLOCKS_COUNT,\
        CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED,\
        CONTROLLER_2M_CODED_PHY_ENABLED,\
        CONTROLLER_EXT_ADV_SCAN_ENABLED,\
        CONTROLLER_PRIVACY_ENABLED,\
        SECURE_CONNECTIONS_ENABLED,\
        CONTROLLER_MASTER_ENABLED,\
        BLE_STACK_NUM_ADV_SET,\
        BLE_STACK_NUM_AUX_EVENT,\
        BLE_STACK_WHITE_LIST_SIZE_LOG2,\
        L2CAP_COS_ENABLED,\
        BLE_STACK_NUM_L2CAP_COCS,\
        CONTROLLER_PERIODIC_ADV_ENABLED,\
        NUM_SYNC_SLOTS,\
        CONTROLLER_CTE_ENABLED,\
        BLE_STACK_NUM_CTE_ANT_IDS,\
        BLE_STACK_NUM_IQSAMPLES,\
        CONTROLLER_POWER_CONTROL_ENABLED,\
        CONNECTION_ENABLED,\
        ISR0_FIFO_SIZE,\
        ISR1_FIFO_SIZE,\
        USER_FIFO_SIZE\
))

/**
*
* This structure contains memory and low level hardware configuration data for the device
*/
typedef struct {
  uint8_t* BLEStartRamAddress;  /**< Start address of the RAM buffer required by the Bluetooth stack. It must be 32-bit aligned. Use BLE_STACK_TOTAL_BUFFER_SIZE to calculate the correct size. */
  uint32_t TotalBufferSize;     /**< BLE_STACK_TOTAL_BUFFER_SIZE return value, used to check the MACRO correctness*/
  uint16_t NumAttrRecords;      /**< Maximum number of Attributes that can be stored in the GATT database. */
  uint8_t MaxNumOfClientProcs;  /**< Maximum number of concurrent Client's Procedures. This value shall be less or equal to NumOfLinks. */
  uint8_t NumOfLinks;           /**< Maximum number of simultaneous radio tasks. Radio controller supports up to 128 simultaneous radio tasks, but actual usable max value depends on the available device RAM (NUM_LINKS used in the calculation of BLE_STACK_TOTAL_BUFFER_SIZE). */
  uint16_t NumBlockCount;       /**< Number of allocated memory blocks */
  uint16_t ATT_MTU;             /**< Maximum supported ATT_MTU size [23-1020]*/
  uint32_t MaxConnEventLength;  /**< Maximum duration of the connection event when the device is in Slave mode in units of 625/256 us (~2.44 us) */
  uint16_t SleepClockAccuracy;  /**< Sleep clock accuracy (ppm value)*/
  uint8_t NumOfAdvDataSet;      /**< Maximum number of Advertising Data Set, valid only when Advertising Extension Feature is enabled  */
  uint8_t NumOfAuxScanSlots;    /**< Maximum number of slots for scanning on the secondary advertising channel, valid only when Advertising Extension Feature is enabled  */
  uint8_t NumOfSyncSlots;       /**< Maximum number of slots for synchronizing, valid only when Periodic Advertising and Synchronizing Feature is enabled  */
  uint8_t WhiteListSizeLog2;    /**< Two's logarithm of white, resolving and advertiser list size. */
  uint16_t L2CAP_MPS;           /**< The maximum size of payload data in octets that the L2CAP layer entity is capable of accepting [0-1024].*/
  uint8_t L2CAP_NumChannels;    /**< Maximum number of channels in LE Credit Based Flow Control mode [0-255].*/
  uint8_t CTE_MaxNumAntennaIDs; /**< Maximum number of Antenna IDs in the antenna pattern used in CTE connection oriented mode. */
  uint8_t CTE_MaxNumIQSamples;  /**< Maximum number of IQ samples in the buffer used in CTE connection oriented mode. */
  uint16_t isr0_fifo_size;      /**< Size of the internal FIFO used for critical controller events produced by the ISR (e.g. rx data packets)*/
  uint16_t isr1_fifo_size;      /**< Size of the internal FIFO used for non-critical controller events produced by the ISR (e.g. advertising or IQ sampling reports)*/
  uint16_t user_fifo_size;      /**< Size of the internal FIFO used for controller and host events produced outside the ISR */
} BLE_STACK_InitTypeDef;


/**
 * @brief This function executes the processing of all Host Stack layers.
 *
 * The BLE Stack Tick function has to be executed regularly to process incoming Link Layer packets and to process Host Layers procedures. All
 * stack callbacks are called by this function.
 *
 * If Low Speed Ring Oscillator is used instead of the LS Crystal oscillator this function performs also the LS RO calibration and hence must
 * be called at least once at every system wake-up in order to keep the 500 ppm accuracy (at least 500 ppm accuracy is mandatory if acting as a master).
 *
 * No BLE stack function must be called while the BLE_STACK_Tick is running. For example, if a BLE stack function may be called inside an
 * interrupt routine, that interrupt must be disabled during the execution of BLE_STACK_Tick(). Example (if a stack function may be called inside
 * UART ISR):
 * @code
 * NVIC_DisableIRQ(UART_IRQn);
 * BLE_STACK_Tick();
 * NVIC_EnableIRQ(UART_IRQn);
 * @endcode

 * @note The API name and parameters are subject to change in future releases.
 * @return None
 */
void BLE_STACK_Tick(void);

/**
 * @brief The BLE Stack initialization routine
 *
 * @note The API name and parameters are subject to change in future releases.
 *
 * @param[in]  BLE_STACK_InitStruct      pointer to the const structure containing memory and low level
 *                                              hardware configuration data for the device
 *
 * @return Value indicating success or error code.
 *
 */
tBleStatus BLE_STACK_Init(const BLE_STACK_InitTypeDef *BLE_STACK_InitStruct);


/**
 * @brief Returns the BLE Stack matching sleep mode
 *
 * @note The API name and parameters are subject to change in future releases.
 *
 * @return
 *  SLEEPMODE_RUNNING       = 0,
 *  SLEEPMODE_NOTIMER       = 3,
 */
uint8_t BLE_STACK_SleepCheck(void);

/**
 *
 * @brief Radio ISR routine.
 *
 * This is the base function called for any radio ISR.
 *
 * @param[in]  BlueInterrupt    value of the radio interrupt register
 *
 * @return None
 */
void BLE_STACK_RadioHandler(uint32_t BlueInterrupt);

/**
  * @brief This function provide information when a new radio activity will be performed.
Information provided includes type of radio activity and absolute time in system ticks when a new radio activity is schedule, if any.
  * @param NextStateSysTime 32bit absolute current time expressed in internal time units.
  * @retval Value indicating the next state:
  - 0x00: Idle
  - 0x01: Advertising
  - 0x02: Connection event slave
  - 0x03: Scanning
  - 0x04: Connection request
  - 0x05: Connection event master
  - 0x06: TX test mode
  - 0x07: RX test mode
  */
uint8_t BLE_STACK_ReadNextRadioActivity(uint32_t *NextStateSysTime);

/* Statistics per link */
typedef struct llc_conn_per_statistic_s {

    uint16_t num_pkts;          /**< The number of received packets, valid or with CRC errors. */
    uint16_t num_crc_err;       /**< The number of packets received with CRC errors. */
    uint16_t num_evts;          /**< The number of past connection events, including missed ones. */
    uint16_t num_miss_evts;     /**< The number of missed RX packets, because of RX timeout or invalid packet length. */

} llc_conn_per_statistic_st;

/**
 * @brief     LLC function to collect statistics per link:
 *             - statistics are stored in a buffer allocated by the application
 *             - counters are reset every time the function is called
 *             - counters are stopped when the function is called with a pointer to NULL
 *
 * @param[in] conn_handle Connection handle that identifies the connection
 * @param[in] statistics_p pointer to the structure where statistics will be noted
 * @return    BLE_ERROR_UNKNOWN_CONNECTION_ID in case of invalid conn_handle
 *            BLE_STATUS_SUCCESS otherwise
 */
tBleStatus llc_conn_per_statistic(uint16_t conn_handle,
                                  llc_conn_per_statistic_st *statistics_p);


/* Statistics per link and per channel */
#define LLC_MAX_NUM_DATA_CHAN 37U

typedef struct llc_conn_per_statistic_by_channel_s {
    uint16_t num_pkts[LLC_MAX_NUM_DATA_CHAN];              /**< The number of received packets, valid or with CRC errors. */  
    uint16_t num_crc_err[LLC_MAX_NUM_DATA_CHAN];           /**< The number of packets received with CRC errors. */
    uint16_t num_miss_evts[LLC_MAX_NUM_DATA_CHAN];         /**< The number of missed RX events, because of RX timeout or invalid packet length. */
    
} llc_conn_per_statistic_by_channel_st;

/**
 * @brief     LLC function to collect statistics per link and per channel:
 *             - statistics are stored in a buffer allocated by the application
 *             - counters are reset every time the function is called
 *             - counters are stopped when the function is called with a pointer to NULL
 *
 * @param[in] conn_handle - connection handle that identifies the connection
 * @param[in] statistics_p - pointer to the structure where statistics will be noted
 * @return    BLE_ERROR_UNKNOWN_CONNECTION_ID in case of invalid conn_handle
 *            BLE_STATUS_SUCCESS otherwise
 */
tBleStatus llc_conn_per_statistic_by_channel(uint16_t conn_handle,
                                             llc_conn_per_statistic_by_channel_st *statistics_p);


#endif /* BLUENRGLP_STACK_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

