# EDJX C++ SDK

This repository contains builds of the EDJX C++ SDK. The `libedjx.a` library
in `lib/` and header files in `include/edjx/` are required to build EDJX C++
serverless functions. Please see
[EDJX C++ SDK example](https://github.com/edjx/edjfunction-example-cpp)
on how to build and use EDJX C++ Serverless functions.

## Version

EDJX C++ SDK version 0.1.0

This EDJX C++ SDK build was built against WASI SDK version 12
(see [wasi-sdk-12 release page](https://github.com/WebAssembly/wasi-sdk/releases/tag/wasi-sdk-12)).

## Installation Instructions

EDJX C++ SDK builds are provided separately for different
[WASI C++ SDK](https://github.com/WebAssembly/wasi-sdk/releases) versions.
For example, the `wasi-12` branch in this repository contains a build of
the EDJX C++ SDK that was built with WASI SDK 12 (the `wasi-sdk-12` release of
the WASI SDK).

To install the EDJX C++ SDK system-wide into the `/opt` directory so that
it can be used to build serverless applications with WASI SDK 12, run:

    git clone --branch wasi-12 --depth 1 https://github.com/edjx/edjx-cpp-sdk.git /opt/edjx-cpp-sdk

With the `--depth 1` argument, only the latest EDJX C++ SDK build for the
specific WASI SDK version is downloaded. Without the `--depth` parameter
specified, git commits with previous EDJX C++ SDK releases will also be
downloaded.
