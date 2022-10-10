#include <injective/network.h>
#include <iostream>

using namespace injective;

auto main() -> int {
    const auto& network = Network::LoadNetwork("testnet","k8s");
    std::cout << network.LcdEndpoint << std::endl;
    return 0;
}