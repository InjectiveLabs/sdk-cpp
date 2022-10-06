#include <fmt/format.h>
#include <injective/network.h>

using namespace injective;

Network Network::LoadNetwork(std::string name, std::string node)
{
  {
    if (name == "testnet"){
      return Network{
        "https://k8s.testnet.lcd.injective.network",
        "wss://k8s.testnet.tm.injective.network/websocket",
        "k8s.testnet.chain.grpc.injective.network:443",
        "k8s.testnet.exchange.grpc.injective.network:443",
        "injective-888",
        "inj",
        "testnet",
      }; 
    }else if (name == "devnet"){
        return Network{
        "https://devnet.lcd.injective.dev",
        "wss://devnet.tm.injective.dev/websocket",
        "devnet.injective.dev:9900",
        "devnet.injective.dev:9910",
        "injective-777",
        "inj",
        "devnet",
        };
    }else if (name == "mainnet"){
        if (node == "k8s"){
        return Network{
          "https://k8s.mainnet.lcd.injective.network:443",
          "wss://k8s.mainnet.tm.injective.network:443/websocket",
          "k8s.mainnet.chain.grpc.injective.network:443",
          "k8s.mainnet.exchange.grpc.injective.network:443",
          "inj",
          "mainnet"
          };
      }else if (node == "lb"){
        return Network{
        "https://k8s.global.mainnet.lcd.injective.network:443",
        "wss://k8s.global.mainnet.tm.injective.network:443/websocket",
        "k8s.global.mainnet.chain.grpc.injective.network:443",
        "k8s.global.mainnet.exchange.grpc.injective.network:443",
        "inj",
        "mainnet"
        };
      }else if (node == "sentry0"){
        return Network{
        "https://lcd.injective.network",
        "ws://sentry0.injective.network:26657/websocket",
        "sentry0.injective.network:9900",
        "sentry0.injective.network:9910",
        "inj",
        "mainnet"
        };
      }else if (node == "sentry1"){
        return Network{
        "https://lcd.injective.network",
        "ws://sentry1.injective.network:26657/websocket",
        "sentry1.injective.network:9900",
        "sentry1.injective.network:9910",
        "inj",
        "mainnet"
        };
      }else if (node == "sentry2"){
        return Network{
        "https://lcd.injective.network",
        "ws://sentry2.injective.network:26657/websocket",
        "sentry2.injective.network:9900",
        "sentry2.injective.network:9910",
        "inj",
        "mainnet"
        };
      }else if (node == "sentry3"){
        return Network{
        "https://lcd.injective.network",
        "ws://sentry3.injective.network:26657/websocket",
        "sentry3.injective.network:9900",
        "sentry3.injective.network:9910",
        "inj",
        "mainnet"
        };
      }
    }
  }
  return Network{};
}
