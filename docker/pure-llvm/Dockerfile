FROM ubuntu:focal
RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install clang lldb lld
RUN ln -s /usr/bin/wasm-ld-10 usr/bin/wasm-ld