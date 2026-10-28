#ifndef ESP32_SERIAL_TRANSPORT_H
#define ESP32_SERIAL_TRANSPORT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <uxr/client/transport.h>

#ifdef __cplusplus
extern "C" {
#endif

bool esp32_serial_open(
    struct uxrCustomTransport *transport);

bool esp32_serial_close(
    struct uxrCustomTransport *transport);

size_t esp32_serial_write(
    struct uxrCustomTransport *transport,
    const uint8_t *buffer,
    size_t length,
    uint8_t *error);

size_t esp32_serial_read(
    struct uxrCustomTransport *transport,
    uint8_t *buffer,
    size_t length,
    int timeout,
    uint8_t *error);

#ifdef __cplusplus
}
#endif

#endif