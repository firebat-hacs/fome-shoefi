
TUNERSTUDIO_SRC_CPP = $(PROJECT_DIR)/console/binary/tunerstudio_io.cpp \
	$(GENERATED_DIR)/live_data.cpp \
	$(PROJECT_DIR)/console/binary/ts_can_channel.cpp \
	$(PROJECT_DIR)/console/binary/serial_can.cpp \
	$(PROJECT_DIR)/console/binary/tunerstudio.cpp \
	$(PROJECT_DIR)/console/binary/tunerstudio_commands.cpp \
	$(PROJECT_DIR)/console/binary/signature.cpp \
	$(PROJECT_DIR)/console/binary/trigger_scope.cpp \

# Hardware UART TunerStudio transport is only valid for the real STM32F4 firmware.
# The simulator provides its own startSerialChannels() implementation.
ifeq ($(PROJECT_CPU),ARCH_STM32F4)
TUNERSTUDIO_SRC_CPP += $(PROJECT_DIR)/console/binary/tunerstudio_io_serial.cpp \
	$(PROJECT_DIR)/console/binary/tunerstudio_io_serial_ports.cpp
endif
