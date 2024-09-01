ARG ARDUINO_CLI_VERSION=1.0.4

FROM mcr.microsoft.com/devcontainers/universal:2

# Install Arduino Prerequisites
RUN ["dash", "-c", "\
    apt-get update --quiet \
    && apt-get install --assume-yes --no-install-recommends --quiet \
        bash \
        bash-completion \
        ca-certificates \
        curl \
        python-is-python3 \
        python3 \
        python3-pip \
        ssh \
        tree \
    && pip install \
        adafruit-nrfutil \
        pyserial \
"]

# Install arduino-cli as root
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh -s ${ARDUINO_CLI_VERSION}

# As non-root
USER codespace
RUN arduino-cli config init \
    && arduino-cli core update-index \
    && arduino-cli core install esp32:esp32@2.0.17 \
    && arduino-cli lib install "ArduinoMenu library"@4.21.4 \
    && arduino-cli lib install QDEC@2.1.0 \
    && arduino-cli lib install FastAccelStepper@0.30.14 \
    && arduino-cli lib install ESP32Servo@3.0.5 \
    && arduino-cli lib install WifiManager@2.0.17
WORKDIR /home/codespace/Arduino/libraries
RUN git clone https://github.com/fmalpartida/New-LiquidCrystal
