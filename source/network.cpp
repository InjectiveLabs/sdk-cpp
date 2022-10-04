#include <fmt/format.h>
#include <injective/network.h>

using namespace injective;

Network Network::LoadNetwork(std::string name, std::string)
{
  if (name == "testnet"){
    return Network{
      "https://k8s.testnet.lcd.injective.network",
      "wss://k8s.testnet.tm.injective.network/websocket",
      "k8s.testnet.chain.grpc.injective.network:443",
      "k8s.testnet.exchange.grpc.injective.network:443",
      "injective-888",
      "int",
      "testnet"
    }; 
  }
  return Network{};
}