# MetaCall Embedding `matplotlib` Example

This example shows how to build and run Python `matplotlib` from C/C++ source code. The instructions are focused on Linux but it can be ported to other platforms easily.

## Install

Install MetaCall:

```bash
git clone https://github.com/metacall/core.git
mkdir core/build && cd core/build
cmake -DOPTION_BUILD_LOADERS_PY=On -DOPTION_BUILD_DETOURS=Off -DOPTION_BUILD_SCRIPTS=Off -DOPTION_BUILD_TESTS=Off ..
cmake --build . --target install
```

Install `matplotlib` dependency:

```bash
pip3 install --user matplotlib
```

## Build

Build example source code:

```bash
gcc -std=c11 main.c -lmetacall
```

## Run

Run executable previously built:

```bash
export LOADER_SCRIPT_PATH="`pwd`"
./a.out
```

## Docker

Building and running with Docker:

```bash
docker build -t metacall/embedding-matplotlib-example .
docker run --rm -it metacall/embedding-matplotlib-example ./a.out
```
