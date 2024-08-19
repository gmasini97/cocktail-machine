ARG ARDUINO_CLI_VERSION=1.0.4
ARG ARDUINO_CLI_DIR=/usr/local/bin

FROM mcr.microsoft.com/devcontainers/universal:2

RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=${ARDUINO_CLI_DIR} sh -s ${ARDUINO_CLI_VERSION}