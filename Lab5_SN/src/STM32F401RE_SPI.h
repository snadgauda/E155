// STM32F401RE_FLASH.h
// Header for FLASH functions

#ifndef STM32F4_SPI_H
#define STM32F4_SPI_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define SPI2_BASE (0x40003800UL) // base address of RCC

///////////////////////////////////////////////////////////////////////////////
// Bitfield structs
///////////////////////////////////////////////////////////////////////////////

typedef struct {
  __IO uint32_t CHPA     :1;        // Clock Phase
  __IO uint32_t CPOL     :1;        // Clock Polarity
  __IO uint32_t MSTR     :1;        // Master Select
  __IO uint32_t BR       :3;        // Baud Rate Control
  __IO uint32_t SPE      :1;        // SPI Enable
  __IO uint32_t LSBFIRST :1;        // Frame Format
  __IO uint32_t SSI      :1;        // Internal Slave Select
  __IO uint32_t SSM      :1;        // Software Slave Management
  __IO uint32_t RXONLY   :1;        // Recieve Only
  __IO uint32_t DFF      :1;        // Data Frame Format
  __IO uint32_t CRCNEXT  :1;        // CRC Transfer next
  __IO uint32_t CRCEN    :1;        // Hardware CRC Caclulation Enable
  __IO uint32_t BIDIOD   :1;        // Ouptput Enable in Bi-Directional Mode
  __IO uint32_t BIDIMODE :1;        // Bi-Directional Data Mode Enable
  __IO uint32_t          :16;       // Reserved
} Control_Register_1_bits;

typedef struct {
  __IO uint32_t RXDMAEN  :1;        // RX Buffer DMA Enable
  __IO uint32_t TXDMAEN  :1;        // TX Buffer DMA Enable
  __IO uint32_t SSOE     :1;        // SS Output Enable
  __IO uint32_t          :1;        // Baud Rate Control
  __IO uint32_t FRF      :1;        // Frame Format
  __IO uint32_t ERRIE    :1;        // Error Interrupt Enable
  __IO uint32_t RXNEIE   :1;        // Internal Slave Select
  __IO uint32_t TXEIE    :1;        // Data Frame Format
  __IO uint32_t          :24;       // Reserved
} Control_Register_2_bits;

typedef struct {
  __IO uint32_t RNXE     :1;        // Receive Buffer not Empty
  __IO uint32_t TXE      :1;        // Transmit Buffer not Empty
  __IO uint32_t CHSIDE   :1;        // Channel Side
  __IO uint32_t UDR      :1;        // Uderrun flag
  __IO uint32_t CRCERR   :1;        // CRC Error Flag
  __IO uint32_t MODF     :1;        // Mode Fault
  __IO uint32_t OVR      :1;        // Overrun Flag
  __IO uint32_t BSY      :1;        // Busy Flag
  __IO uint32_t FRE      :1;        // Frame Format Error
  __IO uint32_t          :23;       // Reserved
} Status_Register_bits;

typedef struct {
  __IO uint32_t CHLEN    :1;        // Channel Length
  __IO uint32_t DATLEN   :2;        // Data Length to be Transfered
  __IO uint32_t CKPOL    :1;        // Steady State Clock Polarity
  __IO uint32_t I2SSTD   :2;        // I2S Standard Selection
  __IO uint32_t          :1;        // Reserved
  __IO uint32_t PCMSYNC  :1;        // PCM Frame Aynchronization
  __IO uint32_t I2SCFG   :2;        // I2S Configuration Mode
  __IO uint32_t I2SE     :1;        // I2S Enable
  __IO uint32_t I2SMOD   :1;        // I2S Mode Selection
  __IO uint32_t          :20;       // Reserved
} Configuration_Register_bits;

typedef struct {
  __IO uint32_t I2SDIV   :8;        // I2S Linear prescaler
  __IO uint32_t ODD      :1;        // Odd Prescaler
  __IO uint32_t MCKOE    :1;        // Master Clock Output Enable
  __IO uint32_t          :22;       // Reserved
} Prescaler_Register_bits;

typedef struct {
  __IO Control_Register_1_bits      CR1;        /*!< control register 1,        Address offset: 0x00 */
  __IO Control_Register_2_bits      CR2;        /*!< control register 2,        Address offset: 0x04 */
  __IO Status_Register_bits         SR;         /*!< status register,           Address offset: 0x08 */
  __IO uint32_t                     DR;         /*!< data register,             Address offset: 0x0C */
  __IO uint32_t                     CRCPR;      /*!< CRC  polynomial register,  Address offset: 0x10 */
  __IO uint32_t                     RXCRCR;     /*!< RX CRC register,           Address offset: 0x14 */
  __IO uint32_t                     TXCRCR;     /*!< TX CRC register,           Address offset: 0x18 */
  __IO Configuration_Register_bits  I2SCFGR;    /*!< configuration register,    Address offset: 0x18 */
  __IO Prescaler_Register_bits      I2SPR;      /*!< prescaler register,        Address offset: 0x18 */

} SPI_TypeDef;

#define SPI2 ((SPI_TypeDef *) SPI2_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initSPI();
void writeSquare(int frequency);
void writeSin(uint16_t freqOut, uint16_t freq, int resolution, float duty, int* table);

#endif