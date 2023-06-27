#include "stack_user_cfg.h"

#if (defined(CONTROLLER_MASTER_ENABLED) &&\
     (CONTROLLER_MASTER_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus aci_gap_start_connection_update(uint16_t Connection_Handle,
                                           uint16_t Conn_Interval_Min,
                                           uint16_t Conn_Interval_Max,
                                           uint16_t Conn_Latency,
                                           uint16_t Supervision_Timeout,
                                           uint16_t Minimum_CE_Length,
                                           uint16_t Maximum_CE_Length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus aci_gap_send_pairing_req(uint16_t Connection_Handle,
                                    uint8_t Force_Rebond)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

tBleStatus aci_gap_set_scan_configuration(uint8_t duplicate_filtering,
                                          uint8_t scanning_filter_policy,
                                          uint8_t phy,
                                          uint8_t scan_type,
                                          uint16_t scan_interval,
                                          uint16_t scan_window)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus aci_gap_set_connection_configuration(uint8_t phy,
                                                uint16_t conn_interval_min,
                                                uint16_t conn_interval_max,
                                                uint16_t conn_latency,
                                                uint16_t supervision_timeout,
                                                uint16_t minimum_ce_length,
                                                uint16_t maximum_ce_length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus aci_gap_create_connection(uint8_t Initiating_PHY,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

tBleStatus aci_gap_start_procedure(uint8_t procedure_code,
                                   uint8_t phys,
                                   uint16_t duration,
                                   uint16_t period)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus aci_gap_discover_name(uint8_t PHYs,
                                 uint8_t Peer_Address_Type,
                                 uint8_t Peer_Address[6])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

tBleStatus aci_gap_terminate_proc(uint8_t Procedure_Code)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_create_sync(uint8_t Options,
                                                    uint8_t Advertising_SID,
                                                    uint8_t Advertising_Address_Type,
                                                    uint8_t Advertiser_Address[6],
                                                    uint16_t Skip,
                                                    uint16_t Sync_Timeout,
                                                    uint8_t Sync_CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_create_sync_cancel(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_terminate_sync(uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_periodic_advertising_receive_enable(uint16_t Sync_Handle,
                                                           uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_add_device_to_periodic_advertiser_list(uint8_t Advertiser_Address_Type,
                                                          uint8_t Advertiser_Address[6],
                                                          uint8_t Advertising_SID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_remove_device_from_periodic_advertising_list(uint8_t Advertiser_Address_Type,
                                                                uint8_t Advertiser_Address[6],
                                                                uint8_t Advertising_SID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_clear_periodic_advertiser_list(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_read_periodic_advertiser_list_size(uint8_t* Periodic_Advertiser_List_Size)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1)) &&\
    (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                      uint16_t Service_Data,
                                                      uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1)) &&\
    (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                     uint8_t Mode,
                                                                     uint16_t Skip,
                                                                     uint16_t Sync_Timeout,
                                                                     uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1)) &&\
    (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus aci_gap_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                             uint16_t Skip,
                                                                             uint16_t Sync_Timeout,
                                                                             uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus aci_l2cap_connection_parameter_update_resp(uint16_t Connection_Handle,
                                                      uint16_t Conn_Interval_Min,
                                                      uint16_t Conn_Interval_Max,
                                                      uint16_t Slave_latency,
                                                      uint16_t Timeout_Multiplier,
                                                      uint16_t Minimum_CE_Length,
                                                      uint16_t Maximum_CE_Length,
                                                      uint8_t Identifier,
                                                      uint8_t Accept)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus hci_le_create_connection(uint16_t LE_Scan_Interval,
                                    uint16_t LE_Scan_Window,
                                    uint8_t Initiator_Filter_Policy,
                                    uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6],
                                    uint8_t Own_Address_Type,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus hci_le_create_connection_cancel(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_extended_create_connection(uint8_t Initiating_Filter_Policy,
                                             uint8_t Own_Address_Type,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Initiating_PHYs,
                                             Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus hci_le_start_encryption(uint16_t Connection_Handle,
                                   uint8_t Random_Number[8],
                                   uint16_t Encrypted_Diversifier,
                                   uint8_t Long_Term_Key[16])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_extended_scan_parameters(uint8_t Own_Address_Type,
                                               uint8_t Scanning_Filter_Policy,
                                               uint8_t Scanning_PHYs,
                                               Extended_Scan_Parameters_t* Extended_Scan_Parameters)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_extended_scan_enable(uint8_t Enable,
                                           uint8_t Filter_Duplicates,
                                           uint16_t Duration,
                                           uint16_t Period)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_create_sync(uint8_t Options,
                                                   uint8_t Advertising_SID,
                                                   uint8_t Advertising_Address_Type,
                                                   uint8_t Advertiser_Address[6],
                                                   uint16_t Skip,
                                                   uint16_t Sync_Timeout,
                                                   uint8_t Sync_CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_create_sync_cancel(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_terminate_sync(uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_add_device_to_periodic_advertiser_list(uint8_t Advertiser_Address_Type,
                                                         uint8_t Advertiser_Address[6],
                                                         uint8_t Advertising_SID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_remove_device_from_periodic_advertising_list(uint8_t Advertiser_Address_Type,
                                                               uint8_t Advertiser_Address[6],
                                                               uint8_t Advertising_SID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_clear_periodic_advertiser_list(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_read_periodic_advertiser_list_size(uint8_t* Periodic_Advertiser_List_Size)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_periodic_advertising_receive_enable(uint16_t Sync_Handle,
                                                          uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1)) &&\
    (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                            uint16_t Skip,
                                                                            uint16_t Sync_Timeout,
                                                                            uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1)) &&\
    (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                    uint8_t Mode,
                                                                    uint16_t Skip,
                                                                    uint16_t Sync_Timeout,
                                                                    uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1)) &&\
    (defined(CONTROLLER_PERIODIC_ADV_ENABLED) &&\
            (CONTROLLER_PERIODIC_ADV_ENABLED == 1)) &&\
    (defined(CONTROLLER_EXT_ADV_SCAN_ENABLED) &&\
            (CONTROLLER_EXT_ADV_SCAN_ENABLED == 1))
tBleStatus hci_le_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                     uint16_t Service_Data,
                                                     uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

tBleStatus hci_le_set_scan_parameters(uint8_t LE_Scan_Type,
                                      uint16_t LE_Scan_Interval,
                                    uint16_t LE_Scan_Window,
                                    uint8_t Own_Address_Type,
                                      uint8_t Scanning_Filter_Policy)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_scan_enable(uint8_t LE_Scan_Enable,
                                  uint8_t Filter_Duplicates)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

#if (defined(CONNECTION_ENABLED) &&\
            (CONNECTION_ENABLED == 1))
tBleStatus hci_le_connection_update(uint16_t Connection_Handle,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}
#endif

#endif
