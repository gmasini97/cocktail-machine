ARG ARDUINO_CLI_VERSION=1.0.4

FROM mcr.microsoft.com/devcontainers/universal:2

# Install arduino-cli as root
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh -s ${ARDUINO_CLI_VERSION}

# As non-root
USER codespace
RUN arduino-cli config init \
    && arduino-cli core update-index \
    && arduino-cli core install esp32:esp32@2.0.17 \
    && arduino-cli lib install "ArduinoMenu library"@4.21.4 \
    && arduino-cli lib install "LiquidCrystal I2C"@1.1.2 \
    && arduino-cli lib install QDEC@2.1.0 \
    && arduino-cli lib install FastAccelStepper@0.30.14
