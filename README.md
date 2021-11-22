# EDJX C++ SDK

This repository contains builds of the EDJX C++ SDK.

## Installation Instructions

EDJX C++ SDK builds are provided separately for different
[WASI C++ SDK](https://github.com/WebAssembly/wasi-sdk/releases) versions.
For example, the `wasi-12` branch in this repository contains a build of
the EDJX C++ SDK that was built with WASI SDK 12 (the `wasi-sdk-12` release of
the WASI SDK).

To install the EDJX C++ SDK system-wide into the `/opt` directory so that
it can be used to build serverless applications with WASI SDK 12, run:

    git clone --branch wasi-12 https://github.com/edjx/edjx-cpp-sdk.git /opt/edjx-cpp-sdk
