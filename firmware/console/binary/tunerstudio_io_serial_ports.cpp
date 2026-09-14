/**
 * Initialize the primary hardware UART TunerStudio port.
 * UART-only restoration: no Bluetooth support.
 */

#include "pch.h"

#include "tunerstudio.h"
#include "tunerstudio_io.h"

#ifndef TS_PRIMARY_BAUD
#define TS_PRIMARY_BAUD 115200
#endif

extern bool main_loop_started;

#if EFI_PROD_CODE && defined(TS_PRIMARY_UxART_PORT) && HAL_USE_UART

static UartTsChannel primaryChannel(TS_PRIMARY_UxART_PORT);

struct PrimaryChannelThread : public TunerstudioThread {
	PrimaryChannelThread()
		: TunerstudioThread("Primary TS UART") {
	}

	TsChannelBase* setupChannel() override {
		// startConsole() runs before configuration load. Wait until normal firmware
		// startup is complete before exposing the UART TunerStudio transport.
		while (!main_loop_started) {
			chThdSleepMilliseconds(50);
		}

		efiSetPadMode("Primary UART RX", EFI_CONSOLE_RX_BRAIN_PIN, PAL_MODE_ALTERNATE(EFI_CONSOLE_AF));
		efiSetPadMode("Primary UART TX", EFI_CONSOLE_TX_BRAIN_PIN, PAL_MODE_ALTERNATE(EFI_CONSOLE_AF));

		primaryChannel.start(TS_PRIMARY_BAUD);
		return &primaryChannel;
	}
};

static PrimaryChannelThread primaryChannelThread;

#endif

void startSerialChannels() {
#if EFI_PROD_CODE && defined(TS_PRIMARY_UxART_PORT) && HAL_USE_UART
	primaryChannelThread.startThread();
#endif
}
