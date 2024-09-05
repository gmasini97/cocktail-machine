ARDUINO_CLI_VERSION := 1.0.4
ARDUINO_ESP32_VERSION := 2.0.17
LIB_ARDUINO_MENU_VERSION := 4.21.4
LIB_QDEC_VERSION := 2.1.0
LIB_FAST_ACCEL_STEPPER := 0.30.14
LIB_ESP32_SERVO_VERSION := 3.0.5
LIB_WIFI_MANAGER := 2.0.17

install:
	sudo python -m pip install pyserial
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh -s ${ARDUINO_CLI_VERSION}
	bin/arduino-cli config init --overwrite
	bin/arduino-cli config set library.enable_unsafe_install true
	bin/arduino-cli core update-index
	bin/arduino-cli core install esp32:esp32@${ARDUINO_ESP32_VERSION}
	bin/arduino-cli lib install \
		"ArduinoMenu library"@${LIB_ARDUINO_MENU_VERSION} \
		QDEC@${LIB_QDEC_VERSION} \
		FastAccelStepper@${LIB_FAST_ACCEL_STEPPER} \
		ESP32Servo@${LIB_ESP32_SERVO_VERSION} \
		WifiManager@${LIB_WIFI_MANAGER}
	bin/arduino-cli lib install --git-url https://github.com/fmalpartida/New-LiquidCrystal.git

build: install
	bin/arduino-cli compile -b esp32:esp32:esp32doit-devkit-v1 --output-dir build --build-property "build.extra_flags=\"-DVERSION=v0.0.0\""

clean:
	rm -rf build