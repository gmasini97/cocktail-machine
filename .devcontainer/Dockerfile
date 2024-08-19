FROM mcr.microsoft.com/devcontainers/universal:2

ARG ARDUINO_CLI_VERSION=1.0.4
ARG USERNAME=maker
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Install arduino-cli as root
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh -s ${ARDUINO_CLI_VERSION}

# Create non-root user
#RUN groupadd --gid $USER_UID $USERNAME \
#    && useradd --uid $USER_UID --gid $USER_UID -m $USERNAME \
#    && apt-get update \
#    && apt-get install -y sudo \
#    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
#    && chmod 0440 /etc/sudoers.d/$USERNAME

# As non-root
USER codespace
RUN arduino-cli config init \
    && arduino-cli core update-index \
    && arduino-cli core install esp32:esp32@2.0.17 \
    && arduino-cli lib install "ArduinoMenu library"@4.21.4 \
    && arduino-cli lib install "LiquidCrystal I2C"@1.1.2 \
    && arduino-cli lib install QDEC@2.1.0 \
    && arduino-cli lib install FastAccelStepper@0.30.14
