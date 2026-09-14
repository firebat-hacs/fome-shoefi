/**
 * Hardware UART transport for TunerStudio.
 * Restored without Bluetooth support.
 */

#include "pch.h"
#include "tunerstudio_io.h"

#if defined(TS_PRIMARY_UxART_PORT) && HAL_USE_UART

void UartTsChannel::start(uint32_t baud) {
	// 8N1 on STM32F4: one stop bit is represented by STOP=00, so no STOP mask is required.
	// Use member assignment instead of aggregate initialization to stay compatible with
	// the current ChibiOS UARTConfig definition.
	m_config = UARTConfig{};
	m_config.speed = baud;
	m_config.cr1 = 0;
	m_config.cr2 = USART_CR2_LINEN;
	m_config.cr3 = 0;

	uartStart(m_driver, &m_config);
}

void UartTsChannel::stop() {
	uartStop(m_driver);
}

void UartTsChannel::write(const uint8_t* buffer, size_t size, bool) {
	uartSendTimeout(m_driver, &size, buffer, BINARY_IO_TIMEOUT);
}

size_t UartTsChannel::readTimeout(uint8_t* buffer, size_t size, int timeout) {
	uartReceiveTimeout(m_driver, &size, buffer, timeout);
	return size;
}

#endif // defined(TS_PRIMARY_UxART_PORT) && HAL_USE_UART
