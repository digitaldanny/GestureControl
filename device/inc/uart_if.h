#ifndef _SRC_UART
#define _SRC_UART

/*
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
* INCLUDES
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

// Common target includes
#include "build_switches.h"
#include "target_hw_common.h"

/*
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
* DEFINES
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

#define UART_BUFFER_MAX_LENGTH                      100

// 12 MHz source
#define UART_BRDIV_CLK_12M_BAUDRATE_38400           19
#define UART_UCXBRF_CLK_12M_BAUDRATE_38400          8
#define UART_UCXBRS_CLK_12M_BAUDRATE_38400          85
#define UART_OVERSAMPLING_CLK_12M_BAUDRATE_38400    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION

#define UART_BRDIV_CLK_12M_BAUDRATE_115200           6
#define UART_UCXBRF_CLK_12M_BAUDRATE_115200          8
#define UART_UCXBRS_CLK_12M_BAUDRATE_115200          32
#define UART_OVERSAMPLING_CLK_12M_BAUDRATE_115200    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION

#define UART_BRDIV_CLK_12M_BAUDRATE_9600           78
#define UART_UCXBRF_CLK_12M_BAUDRATE_9600          2
#define UART_UCXBRS_CLK_12M_BAUDRATE_9600          0
#define UART_OVERSAMPLING_CLK_12M_BAUDRATE_9600    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION

// 16 MHz source
#define UART_BRDIV_CLK_16M_BAUDRATE_38400           26
#define UART_UCXBRF_CLK_16M_BAUDRATE_38400          0
#define UART_UCXBRS_CLK_16M_BAUDRATE_38400          214
#define UART_OVERSAMPLING_CLK_16M_BAUDRATE_38400    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION

#define UART_BRDIV_CLK_16M_BAUDRATE_9600           104
#define UART_UCXBRF_CLK_16M_BAUDRATE_9600          2
#define UART_UCXBRS_CLK_16M_BAUDRATE_9600          182
#define UART_OVERSAMPLING_CLK_16M_BAUDRATE_9600    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION

#define UART_NUMBYTES_WAITFORNL                     0xFF

/*
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
* ENUMS
* +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/
typedef enum
{
    BAUDRATE_38400,
    BAUDRATE_9600
} baudRate_e;

/*
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * DESCRIPTION: spiRxData_t
 * Struct for storing data received from SPI slave.
 *
 * Field Description:
 * @flagSpiReady - True if data has been received and stored into 'data' field.
 * @data - Data received from the SPI slave.
 * @idxBuffer - index of the buffer (used in RX interrupt so
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
typedef struct  {
    bool flagRxReady;
    char rxBuffer[UART_BUFFER_MAX_LENGTH];
    uint8_t idxBuffer;
} uartRxData_t;

namespace Uart {

    /*
    * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
    * PROTOTYPES
    * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
    */

    bool init (baudRate_e baudRate);
    bool send (char* txData, uint8_t numBytes);
    bool recv (char** rxData, uint8_t numBytes);
    bool resetBuffer();

#if TARGET_HW_MSP432
    namespace MSP432 {
        bool init (const eUSCI_UART_Config* config);
        bool resetBuffer();
        bool send (char* txData, uint8_t numBytes);
        bool recv (char** rxData, uint8_t numBytes);
    }
#endif // ENABLE_UART_C2000
}

#endif // _SRC_UART
