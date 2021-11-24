# EDJX C++ SDK

This repository contains EDJX C++ SDK builds.
See the [release page](https://github.com/edjx/edjx-cpp-sdk/releases)
for all downloads. Builds are provided for use with specific
[WASI SDK](https://github.com/WebAssembly/wasi-sdk) versions.

The `libedjx.a` library
in `lib/` and header files in `include/edjx/` are required to build EDJX C++
serverless functions. Please see
[EDJX C++ SDK examples](https://github.com/edjx/edjsamples-cpp)
on how to build and use EDJX C++ Serverless functions.

## Installation Instructions

The EDJX C++ SDK can be directly downloaded from the
[release page](https://github.com/edjx/edjx-cpp-sdk/releases).
Each build of the EDJX C++ SDK targets a specific WASI SDK version.
For example, `wasi-12` releases of the EDJX C++ SDK should be used with
[WASI SDK 12](https://github.com/WebAssembly/wasi-sdk/releases/tag/wasi-sdk-12).

To install the EDJX C++ SDK system-wide into the `/opt` directory so that
it can be used to build serverless applications, run:

    EDJX_SDK_VERSION=v21.11.1
    WASI_SDK_VERSION=12

    wget https://github.com/edjx/edjx-cpp-sdk/releases/download/${EDJX_SDK_VERSION}/edjx-cpp-sdk-${EDJX_SDK_VERSION}-wasi-${WASI_SDK_VERSION}.tar.gz
    tar -xvf edjx-cpp-sdk-${EDJX_SDK_VERSION}-wasi-${WASI_SDK_VERSION}.tar.gz -C /opt
    ln -s /opt/edjx-cpp-sdk-${EDJX_SDK_VERSION}-wasi-${WASI_SDK_VERSION} /opt/edjx-cpp-sdk

or alternatively (downloads the latest EDJX C++ SDK release, to be used with
[WASI SDK 12](https://github.com/WebAssembly/wasi-sdk/releases/tag/wasi-sdk-12)):

    git clone --depth 1 https://github.com/edjx/edjx-cpp-sdk.git /opt/edjx-cpp-sdk

With the `--depth 1` argument, only the latest EDJX C++ SDK build for the
specific WASI SDK version is downloaded. Without the `--depth` parameter
specified, git history with previous EDJX C++ SDK releases will also be
downloaded.
