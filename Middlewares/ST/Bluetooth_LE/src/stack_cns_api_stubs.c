#include "stack_user_cfg.h"

#if (defined(CONNECTION_ENABLED) &&\
     (CONNECTION_ENABLED == 0))

#include <compiler.h>
#include "bluenrg_lp_api.h"

#define ERR_UNKNOWN_HCI_COMMAND (0x01)

/* API definitions */
tBleStatus aci_gap_slave_security_req(uint16_t Connection_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_io_capability(uint8_t IO_Capability)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_authentication_requirement(uint8_t Bonding_Mode,
                                                  uint8_t MITM_Mode,
                                                  uint8_t SC_Support,
                                                  uint8_t KeyPress_Notification_Support,
                                                  uint8_t Min_Encryption_Key_Size,
                                                  uint8_t Max_Encryption_Key_Size,
                                                  uint8_t Use_Fixed_Pin,
                                                  uint32_t Fixed_Pin)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_pass_key_resp(uint16_t Connection_Handle,
                                 uint32_t Pass_Key)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_get_security_level(uint16_t Connection_Handle,
                                      uint8_t* Security_Mode,
                                      uint8_t* Security_Level)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_terminate(uint16_t Connection_Handle,
                             uint8_t Reason)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_clear_security_db(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_remove_bonded_device(uint8_t peerIdentityAddressType,
                                        uint8_t peerIdentityDeviceAddress[6])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_allow_rebond(uint16_t Connection_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

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

tBleStatus aci_gap_send_pairing_req(uint16_t Connection_Handle,
                                    uint8_t Force_Rebond)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_get_bonded_devices(uint8_t Offset,
                                      uint8_t Max_Num_Of_Addresses,
                                      uint8_t* Num_of_Addresses,
                                      Bonded_Device_Entry_t* Bonded_Device_Entry)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_is_device_bonded(uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_numeric_comparison_value_confirm_yesno(uint16_t Connection_Handle,
                                                          uint8_t Confirm_Yes_No)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_passkey_input(uint16_t Connection_Handle,
                                 uint8_t Input_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_get_oob_data(uint8_t OOB_Data_Type,
                                uint8_t* Address_Type,
                                uint8_t Address[6],
                                uint8_t* OOB_Data_Len,
                                uint8_t OOB_Data[16])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_oob_data(uint8_t Device_Type,
                                uint8_t Address_Type,
                                uint8_t Address[6],
                                uint8_t OOB_Data_Type,
                                uint8_t OOB_Data_Len,
                                uint8_t OOB_Data[16])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

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

tBleStatus aci_gap_create_connection(uint8_t Initiating_PHY,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_discover_name(uint8_t PHYs,
                                 uint8_t Peer_Address_Type,
                                 uint8_t Peer_Address[6])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                      uint16_t Service_Data,
                                                      uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_periodic_advertising_set_info_transfer(uint16_t Connection_Handle,
                                                          uint16_t Service_Data,
                                                          uint8_t Advertising_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                     uint8_t Mode,
                                                                     uint16_t Skip,
                                                                     uint16_t Sync_Timeout,
                                                                     uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gap_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                             uint16_t Skip,
                                                                             uint16_t Sync_Timeout,
                                                                             uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_init(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_add_service(ble_gatt_srv_def_t* Serv_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_rm_service(uint16_t Serv_Attr_H)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

uint16_t aci_gatt_srv_get_service_handle(ble_gatt_srv_def_t* Serv_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_include_service(uint16_t Serv_Attr_H,
                                        uint16_t Incl_Serv_Attr_H)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_rm_include_service(uint16_t Incl_Serv_Attr_H)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

uint16_t aci_gatt_srv_get_include_service_handle(uint16_t Serv_Attr_H,
                                                 ble_gatt_srv_def_t* Included_Srv_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_add_char(ble_gatt_chr_def_t* Char_p,
                                 uint16_t Serv_Attr_H)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_rm_char(uint16_t Char_Decl_Attr_H)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

uint16_t aci_gatt_srv_get_char_decl_handle(ble_gatt_chr_def_t* Char_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_add_char_desc(ble_gatt_descr_def_t* Descr_p,
                                      uint16_t Char_Attr_H)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

uint16_t aci_gatt_srv_get_descriptor_handle(ble_gatt_descr_def_t* Descr_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_notify(uint16_t Connection_Handle,
                               uint16_t Attr_Handle,
                               uint8_t Flags,
                               uint16_t Val_Length,
                               uint8_t* Val_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_resp(uint16_t Connection_Handle,
                             uint16_t Attr_Handle,
                             uint8_t Error_Code,
                             uint16_t Data_Len,
                             uint8_t* Data_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_read_handle_value(uint16_t Attr_Handle,
                                          uint16_t* Val_Length_p,
                                          uint8_t** Val_pp)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_read_multiple_instance_handle_value(uint16_t Connection_Handle,
                                                            uint16_t Attr_Handle,
                                                            uint16_t* Val_Length_p,
                                                            uint8_t** Val_pp)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_srv_write_multiple_instance_handle_value(uint16_t Connection_Handle,
                                                             uint16_t Attr_Handle,
                                                             uint16_t Char_Value_Length,
                                                             uint8_t* Char_Value)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_set_event_mask(uint32_t GATT_Evt_Mask)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_exchange_config(uint16_t Connection_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_disc_all_primary_services(uint16_t Connection_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_disc_primary_service_by_uuid(uint16_t Connection_Handle,
                                                     uint8_t UUID_Type,
                                                     UUID_t* UUID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_disc_all_char_of_service(uint16_t Connection_Handle,
                                                 uint16_t Start_Handle,
                                                 uint16_t End_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_disc_char_by_uuid(uint16_t Connection_Handle,
                                          uint16_t Start_Handle,
                                          uint16_t End_Handle,
                                          uint8_t UUID_Type,
                                          UUID_t* UUID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_disc_all_char_desc(uint16_t Connection_Handle,
                                           uint16_t Char_Handle,
                                           uint16_t End_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_find_included_services(uint16_t Connection_Handle,
                                               uint16_t Start_Handle,
                                               uint16_t End_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_read(uint16_t Connection_Handle,
                             uint16_t Attr_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_read_long(uint16_t Connection_Handle,
                                  uint16_t Attr_Handle,
                                  uint16_t Val_Offset)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_read_using_char_uuid(uint16_t Connection_Handle,
                                             uint16_t Start_Handle,
                                             uint16_t End_Handle,
                                             uint8_t UUID_Type,
                                             UUID_t* UUID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_read_multiple_char_value(uint16_t Connection_Handle,
                                                 uint8_t Number_of_Handles,
                                                 Handle_Entry_t* Handle_Entry)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_write_without_resp(uint16_t Connection_Handle,
                                           uint16_t Attr_Handle,
                                           uint16_t Attribute_Val_Length,
                                           uint8_t* Attribute_Val)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_signed_write_without_resp(uint16_t Connection_Handle,
                                                  uint16_t Attr_Handle,
                                                  uint16_t Attribute_Val_Length,
                                                  uint8_t* Attribute_Val)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_write(uint16_t Connection_Handle,
                              uint16_t Attr_Handle,
                              uint16_t Attribute_Val_Length,
                              uint8_t* Attribute_Val)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_write_long(uint16_t Connection_Handle,
                                   ble_gatt_clt_write_ops_t* Write_Ops_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_write_char_reliable(uint16_t Connection_Handle,
                                            uint8_t Num_Attrs,
                                            ble_gatt_clt_write_ops_t* Write_Ops_p)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_prepare_write_req(uint16_t Connection_Handle,
                                          uint16_t Attr_Handle,
                                          uint16_t Val_Offset,
                                          uint16_t Attribute_Val_Length,
                                          uint8_t* Attribute_Val)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_execute_write_req(uint16_t Connection_Handle,
                                          uint8_t Execute)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_gatt_clt_confirm_indication(uint16_t Connection_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_hal_peripheral_latency_enable(uint16_t Connection_Handle,
                                             uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_hal_set_le_power_control(uint8_t Enable,
                                        uint8_t PHY,
                                        int8_t RSSI_Target,
                                        uint8_t RSSI_Hysteresis,
                                        int8_t Initial_TX_Power,
                                        uint8_t RSSI_Filtering_Coefficient)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_hal_get_anchor_point(uint16_t connection_handle,
                                    uint16_t* event_counter,
                                    uint32_t* anchor_point)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_connection_parameter_update_req(uint16_t Connection_Handle,
                                                     uint16_t Conn_Interval_Min,
                                                     uint16_t Conn_Interval_Max,
                                                     uint16_t Slave_latency,
                                                     uint16_t Timeout_Multiplier)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

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

tBleStatus aci_l2cap_cfc_connection_req(uint16_t Connection_Handle,
                                        uint16_t SPSM,
                                        uint16_t CID,
                                        uint16_t MTU,
                                        uint16_t MPS,
                                        uint8_t CFC_Policy,
                                        uint16_t RX_SDU_Buffer_Size,
                                        void* RX_SDU_Buffer)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_cfc_connection_resp(uint16_t Connection_Handle,
                                         uint8_t Identifier,
                                         uint16_t CID,
                                         uint16_t MTU,
                                         uint16_t MPS,
                                         uint16_t Result,
                                         uint8_t CFC_Policy,
                                         uint16_t RX_SDU_Buffer_Size,
                                         void* RX_SDU_Buffer)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_send_flow_control_credits(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t RX_Credits,
                                               uint8_t CFC_Policy,
                                               uint16_t* RX_Credit_Balance)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_disconnect(uint16_t Connection_Handle,
                                uint16_t CID)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_transmit_sdu_data(uint16_t Connection_Handle,
                                       uint16_t CID,
                                       uint16_t SDU_Length,
                                       uint8_t* SDU_Data)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus aci_l2cap_extract_sdu_data(uint16_t Connection_Handle,
                                      uint16_t CID,
                                      uint16_t SDU_Data_Buffer_Size,
                                      void* SDU_Data_Buffer,
                                      uint16_t* SDU_Length)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_read_remote_version_information(uint16_t Connection_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_remote_used_features(uint16_t Connection_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_read_transmit_power_level(uint16_t Connection_Handle,
                                         uint8_t Type,
                                         int8_t* Transmit_Power_Level)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_read_rssi(uint16_t Connection_Handle,
                         int8_t* RSSI)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_channel_map(uint16_t Connection_Handle,
                                   uint8_t LE_Channel_Map[5])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_disconnect(uint16_t Connection_Handle,
                          uint8_t Reason)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

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

tBleStatus hci_le_create_connection_cancel(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_extended_create_connection(uint8_t Initiating_Filter_Policy,
                                             uint8_t Own_Address_Type,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Initiating_PHYs,
                                             Extended_Create_Connection_Parameters_t* Extended_Create_Connection_Parameters)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_connection_cte_receive_parameters(uint16_t Connection_Handle,
                                                        uint8_t Sampling_Enable,
                                                        uint8_t Slot_Durations,
                                                        uint8_t Switching_Pattern_Length,
                                                        uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_connection_cte_transmit_parameters(uint16_t Connection_Handle,
                                                         uint8_t CTE_Type,
                                                         uint8_t Switching_Pattern_Length,
                                                         uint8_t* Antenna_IDs)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_connection_cte_request_enable(uint16_t Connection_Handle,
                                                uint8_t Enable,
                                                uint16_t CTE_Request_Interval,
                                                uint8_t Requested_CTE_Length,
                                                uint8_t Requested_CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_connection_cte_response_enable(uint16_t Connection_Handle,
                                                 uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_start_encryption(uint16_t Connection_Handle,
                                   uint8_t Random_Number[8],
                                   uint16_t Encrypted_Diversifier,
                                   uint8_t Long_Term_Key[16])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_long_term_key_request_reply(uint16_t Connection_Handle,
                                              uint8_t Long_Term_Key[16])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_long_term_key_requested_negative_reply(uint16_t Connection_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_local_p256_public_key(void)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_generate_dhkey(uint8_t Remote_P256_Public_Key[64])
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_read_authenticated_payload_timeout(uint16_t Connection_Handle,
                                                  uint16_t* Authenticated_Payload_Timeout)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_write_authenticated_payload_timeout(uint16_t Connection_Handle,
                                                   uint16_t Authenticated_Payload_Timeout)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_default_periodic_advertising_sync_transfer_parameters(uint8_t Mode,
                                                                            uint16_t Skip,
                                                                            uint16_t Sync_Timeout,
                                                                            uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_periodic_advertising_sync_transfer_parameters(uint16_t Connection_Handle,
                                                                    uint8_t Mode,
                                                                    uint16_t Skip,
                                                                    uint16_t Sync_Timeout,
                                                                    uint8_t CTE_Type)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_periodic_advertising_set_info_transfer(uint16_t Connection_Handle,
                                                         uint16_t Service_Data,
                                                         uint8_t Advertising_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_periodic_advertising_sync_transfer(uint16_t Connection_Handle,
                                                     uint16_t Service_Data,
                                                     uint16_t Sync_Handle)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_data_length(uint16_t Connection_Handle,
                                  uint16_t Tx_Octets,
                                  uint16_t Tx_Time)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_suggested_default_data_length(uint16_t* Suggested_Max_Tx_Octets,
                                                     uint16_t* Suggested_Max_Tx_Time)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_write_suggested_default_data_length(uint16_t Suggested_Max_Tx_Octets,
                                                      uint16_t Suggested_Max_Tx_Time)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_maximum_data_length(uint16_t* Supported_Max_Tx_Octets,
                                           uint16_t* Supported_Max_Tx_Time,
                                           uint16_t* Supported_Max_Rx_Octets,
                                           uint16_t* Supported_Max_Rx_Time)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_enhanced_read_transmit_power_level(uint16_t Connection_Handle,
                                                     uint8_t PHY,
                                                     int8_t* Current_TX_Power_Level,
                                                     int8_t* Max_TX_Power_Level)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_remote_transmit_power_level(uint16_t Connection_Handle,
                                                   uint8_t PHY)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_path_loss_reporting_parameters(uint16_t Connection_Handle,
                                                     uint8_t High_Threshold,
                                                     uint8_t High_Hysteresis,
                                                     uint8_t Low_Threshold,
                                                     uint8_t Low_Hysteresis,
                                                     uint16_t Min_Time_Spent)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_path_loss_reporting_enable(uint16_t Connection_Handle,
                                                 uint8_t Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_transmit_power_reporting_enable(uint16_t Connection_Handle,
                                                      uint8_t Local_Enable,
                                                      uint8_t Remote_Enable)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_read_phy(uint16_t Connection_Handle,
                           uint8_t* TX_PHY,
                           uint8_t* RX_PHY)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

tBleStatus hci_le_set_phy(uint16_t Connection_Handle,
                          uint8_t ALL_PHYS,
                          uint8_t TX_PHYS,
                          uint8_t RX_PHYS,
                          uint16_t PHY_options)
{
    return ERR_UNKNOWN_HCI_COMMAND;
}

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
