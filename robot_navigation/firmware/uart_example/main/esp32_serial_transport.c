#include "esp32_serial_transport.h"

#include "driver/uart.h"
#include "driver/gpio.h"

#include "sdkconfig.h"

#define UART_BUFFER_SIZE 512

#define UART_TXD CONFIG_MICROROS_UART_TXD
#define UART_RXD CONFIG_MICROROS_UART_RXD
#define UART_RTS CONFIG_MICROROS_UART_RTS
#define UART_CTS CONFIG_MICROROS_UART_CTS


bool esp32_serial_open(
    struct uxrCustomTransport *transport)
{
    size_t *uart_port = (size_t *)transport->args;

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    if (uart_param_config(*uart_port, &uart_config) != ESP_OK) {
        return false;
    }

    if (uart_set_pin(
            *uart_port,
            UART_TXD,
            UART_RXD,
            UART_RTS,
            UART_CTS) != ESP_OK)
    {
        return false;
    }

    if (uart_driver_install(
            *uart_port,
            UART_BUFFER_SIZE * 2,
            0,
            0,
            NULL,
            0) != ESP_OK)
    {
        return false;
    }

    return true;
}


bool esp32_serial_close(
    struct uxrCustomTransport *transport)
{
    size_t *uart_port = (size_t *)transport->args;

    return uart_driver_delete(*uart_port) == ESP_OK;
}


size_t esp32_serial_write(
    struct uxrCustomTransport *transport,
    const uint8_t *buffer,
    size_t length,
    uint8_t *error)
{
    (void)error;

    size_t *uart_port = (size_t *)transport->args;

    int written = uart_write_bytes(
        *uart_port,
        (const char *)buffer,
        length);

    return written > 0 ? (size_t)written : 0;
}


size_t esp32_serial_read(
    struct uxrCustomTransport *transport,
    uint8_t *buffer,
    size_t length,
    int timeout,
    uint8_t *error)
{
    (void)error;

    size_t *uart_port = (size_t *)transport->args;

    int received = uart_read_bytes(
        *uart_port,
        buffer,
        length,
        pdMS_TO_TICKS(timeout));

    return received > 0 ? (size_t)received : 0;
}
