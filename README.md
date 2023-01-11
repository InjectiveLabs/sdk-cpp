# Injective C++ SDK
## Currently under development

# Build

This assumes protobuf and gRPC have been installed using cmake.
If not already, follow this [link](https://grpc.io/docs/languages/cpp/quickstart/)

## Build using all target

```bash
rm -rf build
cmake -S all -B build
cmake --build build
```
