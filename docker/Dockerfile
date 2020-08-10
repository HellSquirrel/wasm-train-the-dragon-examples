FROM python:slim

RUN set -eux; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
    ca-certificates gcc libc6-dev wget git xz-utils bzip2 pkg-config libssl-dev

RUN git clone https://github.com/emscripten-core/emsdk.git

ENV EMSDK_VERSION=1.40.1

RUN cd emsdk \
    && ./emsdk install ${EMSDK_VERSION} \
    && ./emsdk activate ${EMSDK_VERSION}

ENV PATH=/emsdk/upstream/emscripten:/emsdk:/emsdk/node/12.18.1_64bit/bin:/emsdk/upstream/bin:$PATH

ENV RUSTUP_HOME=/usr/local/rustup \
    CARGO_HOME=/usr/local/cargo \
    PATH=/usr/local/cargo/bin:$PATH \
    RUST_VERSION=1.45.1

RUN dpkgArch="$(dpkg --print-architecture)"; \
    case "${dpkgArch##*-}" in \
    amd64) rustArch='x86_64-unknown-linux-gnu'; rustupSha256='49c96f3f74be82f4752b8bffcf81961dea5e6e94ce1ccba94435f12e871c3bdb' ;; \
    armhf) rustArch='armv7-unknown-linux-gnueabihf'; rustupSha256='5a2be2919319e8778698fa9998002d1ec720efe7cb4f6ee4affb006b5e73f1be' ;; \
    arm64) rustArch='aarch64-unknown-linux-gnu'; rustupSha256='d93ef6f91dab8299f46eef26a56c2d97c66271cea60bf004f2f088a86a697078' ;; \
    i386) rustArch='i686-unknown-linux-gnu'; rustupSha256='e3d0ae3cfce5c6941f74fed61ca83e53d4cd2deb431b906cbd0687f246efede4' ;; \
    *) echo >&2 "unsupported architecture: ${dpkgArch}"; exit 1 ;; \
    esac; \
    url="https://static.rust-lang.org/rustup/archive/1.22.1/${rustArch}/rustup-init"; \
    wget "$url"; \
    echo "${rustupSha256} *rustup-init" | sha256sum -c -; \
    chmod +x rustup-init; \
    ./rustup-init -y --no-modify-path --profile minimal --default-toolchain $RUST_VERSION; \
    rm rustup-init; \
    chmod -R a+w $RUSTUP_HOME $CARGO_HOME;

RUN cargo install wasm-pack

RUN wget https://github.com/Kitware/CMake/releases/download/v3.18.1/cmake-3.18.1-Linux-x86_64.sh \
    -q -O /tmp/cmake-install.sh \
    && chmod u+x /tmp/cmake-install.sh \
    && mkdir /usr/local/cmake \
    && /tmp/cmake-install.sh --skip-license --prefix=/usr/local/cmake \
    && rm /tmp/cmake-install.sh

ENV PATH=/usr/local/cmake/bin:$PATH

RUN git clone --recursive https://github.com/WebAssembly/wabt

RUN apt-get install -y make g++
RUN mkdir wabt-build && cd wabt-build && CXX=`which g++` CC=`which gcc` cmake -DBUILD_TESTS=OFF /wabt && cmake --build .
ENV PATH=/wabt-build:$PATH

RUN apt-get remove -y --auto-remove \
    wget gcc g++ make; \
    rm -rf wabt; \
    rm -rf /var/lib/apt/lists/*;

