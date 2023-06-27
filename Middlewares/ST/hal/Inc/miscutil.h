/**
  ******************************************************************************
  * @file    miscutil.h
  * @author  AMS - RF Application team
  * @brief   Header file for miscellaneous utility functions.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#ifndef __MISCUTIL_H_
#define __MISCUTIL_H_

/**
 * @brief This command is used to enable ANTENNA_ID signal by enabling the
 *        Alternate Function on the corresponding pins. Some IOs may not be
 *        enabled, depending on resources availability (e.g. IOs used for
 *        communication).
 * @param Antenna_IDs ANTENNA_ID pins to be enabled. Each bit in the mask
 *        enables the corresponding bit of the ANTENNA_ID signal, which is
 *        output on PB[0:7].
 *        Flags:
 *        - 0x01: ANTENNA_ID_0
 *        - 0x02: ANTENNA_ID_1
 *        - 0x04: ANTENNA_ID_2
 *        - 0x08: ANTENNA_ID_3
 *        - 0x10: ANTENNA_ID_4
 *        - 0x20: ANTENNA_ID_5
 *        - 0x40: ANTENNA_ID_6
 * @param Antenna_ID_Shift This parameter can be set to a value different from
 *        zero to shift the ANTENNA_ID signal by the given number of bits. This
 *        number does not affect the pin selected by Antenna_IDs parameter. E.g.
 *        to have the ANTENNA_ID signal output on PB[2:4], set Antenna_IDs to
 *        enable ANTENNA_ID[2:4] (Antenna_IDs = 0x1C) and Antenna_ID_Shift to 2.
 *        Values:
 *        - 0 ... 6
 * @param Default_Antenna_ID The ID of antenna that the controller will select
 *        for regular communication. The antenna to be used when sending or
 *        receiving the CTE field needs to be specified through the Antenna_IDs
 *        parameter of the dedicated HCI commands (i.e.
 *        hci_le_set_connectionless_cte_transmit_parameters,
 *        hci_le_set_connectionless_iq_sampling_enable,
 *        hci_le_set_connection_cte_receive_parameters and
 *        hci_le_set_connection_cte_transmit_parameters).
 *        Values:
 *        - 0x00 ... 0x7F
 * @param RF_Activity_Enable Enable or disable the RF Activity signal, if
 *        supported by the device. This signal can be used to enable the antenna
 *        switch only when necessary.
 *        Values:
 *        - 0x00: DISABLED
 *        - 0x01: ENABLED
 * @retval Value indicating success or error code.
 */
tBleStatus aci_hal_set_antenna_switch_parameters(uint8_t Antenna_IDs,
                                                 uint8_t Antenna_ID_Shift,
                                                 uint8_t Default_Antenna_ID,
                                                 uint8_t RF_Activity_Enable);

#endif /* __MISCUTIL_H_ */
