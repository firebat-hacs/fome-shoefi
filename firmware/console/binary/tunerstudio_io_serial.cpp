/**
 * Hardware UART transport for TunerStudio.
 * Restored without Bluetooth support.
 */

#include "pch.h"
#include "tunerstudio_io.h"

#if defined(TS_PRIMARY_UxART_PORT) && HAL_USE_UART

void UartTsChannel::start(uint32_t baud) {
	m_config = {
		.txend1_cb = NULL,
		.txend2_cb = NULL,
		.rxend_cb = NULL,
		.rxchar_cb = NULL,
		.rxerr_cb = NULL,
		.timeout_cb = NULL,
		.speed = baud,
		.cr1 = 0,
		.cr2 = USART_CR2_STOP1_BITS | USART_CR2_LINEN,
		.cr3 = 0,
		.rxhalf_cb = NULL
	};

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
