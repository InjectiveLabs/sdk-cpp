#pragma once

#include <string>

namespace injective {

  class Network {
  public:
    std::string LcdEndpoint;
    std::string TmEndpoint;
    std::string ChainGrpcEndpoint;
    // ChainTlsCert         credentials.TransportCredentials
    std::string ExchangeGrpcEndpoint;
    // ExchangeTlsCert      credentials.TransportCredentials
    std::string ChainId;
    std::string Fee_denom;
    std::string Name;

  public:
    static Network LoadNetwork(std::string name, std::string node);
  };

}  // namespace injective
