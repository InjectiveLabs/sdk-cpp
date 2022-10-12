#include <fmt/format.h>
#include <injective/network.h>

#include <map>

using namespace injective;

Network Network::LoadNetwork(std::string name, std::string) {
  static std::map<std::string, Network> net
      = {{"testnet", Network{"https://k8s.testnet.lcd.injective.network",
                             "wss://k8s.testnet.tm.injective.network/websocket",
                             "k8s.testnet.chain.grpc.injective.network:443",
                             "k8s.testnet.exchange.grpc.injective.network:443", "injective-888",
                             "int", "testnet"}},
         {"devnet", Network{"https://devnet.lcd.injective.dev",
                            "wss://devnet.tm.injective.dev/websocket", "devnet.injective.dev:9900",
                            "devnet.injective.dev:9910", "injective-777", "inj", "devnet"}},
         {"mainet_k8s", Network{"https://k8s.mainnet.lcd.injective.network:443",
                                "wss://k8s.mainnet.tm.injective.network:443/websocket",
                                "k8s.mainnet.chain.grpc.injective.network:443",
                                "k8s.mainnet.exchange.grpc.injective.network:443", "injective-1",
                                "inj", "mainnet"}},
         {"mainet_lb", Network{"https://k8s.global.mainnet.lcd.injective.network:443",
                               "wss://k8s.global.mainnet.tm.injective.network:443/websocket",
                               "k8s.global.mainnet.chain.grpc.injective.network:443",
                               "k8s.global.mainnet.exchange.grpc.injective.network:443",
                               "injective-1", "inj", "mainnet"}},
         {"mainet_sentry0",
          Network{"https://lcd.injective.network", "ws://sentry0.injective.network:26657/websocket",
                  "sentry0.injective.network:9900", "sentry0.injective.network:9910", "injective-1",
                  "inj", "mainnet"}},
         {"mainet_sentry1",
          Network{"https://lcd.injective.network", "ws://sentry1.injective.network:26657/websocket",
                  "sentry1.injective.network:9900", "sentry1.injective.network:9910", "injective-1",
                  "inj", "mainnet"}},
         {"mainet_sentry2",
          Network{"https://lcd.injective.network", "ws://sentry2.injective.network:26657/websocket",
                  "sentry2.injective.network:9900", "sentry2.injective.network:9910", "injective-1",
                  "inj", "mainnet"}},
         {"mainet_sentry3",
          Network{"https://lcd.injective.network", "ws://sentry3.injective.network:26657/websocket",
                  "sentry3.injective.network:9900", "sentry3.injective.network:9910", "injective-1",
                  "inj", "mainnet"}}};
  return net[name];
}