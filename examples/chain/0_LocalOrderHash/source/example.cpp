#include <injective/network.h>
#include <injective/chain_client.h>  // CChainClient class

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "json.h"            // nlohmann/json

using namespace injective;

auto main() -> int {
    // Load network
    const auto& network = Network::LoadNetwork("testnet", "k8s");
    std::cout << network.LcdEndpoint << std::endl;

    // Initialize ChainClient
    ChainClient ChainClient(network);

    // Initialize sender address and Cosmos keyring
    std::string senderAddress;
    CosmosKeyring cosmosKeyring;
    InitCosmosKeyring(senderAddress, cosmosKeyring);

    // Initialize gRPC client
    ClientContext clientCtx = NewClientContext(chainClient, senderAddress, cosmosKeyring);

    // Prepare tx msg
//    SpotOrderData spotOrderData{/* ... */};
//    DerivativeOrderData derivativeOrderData{/* ... */};
//
//    SpotOrder spotOrder = chainClient.SpotOrder(spotOrderData);
//    DerivativeOrder derivativeOrder = chainClient.DerivativeOrder(derivativeOrderData);
//
//    // Create messages
//    MsgBatchCreateSpotLimitOrders msg;
//    msg.sender = senderAddress;
//    msg.orders.push_back(spotOrder);
//
//    MsgBatchCreateDerivativeLimitOrders msg1;
//    msg1.sender = senderAddress;
//    msg1.orders.push_back(derivativeOrder);
//    msg1.orders.push_back(derivativeOrder);
//
//    // Compute local order hashes
//    OrderHashes orderHashes = chainClient.ComputeOrderHashes(msg.orders, msg1.orders);
//
//    std::cout << "computed spot order hashes: " << orderHashes.spot << std::endl;
//    std::cout << "computed derivative order hashes: " << orderHashes.derivative << std::endl;
//
//    // Broadcast messages
//    chainClient.QueueBroadcastMsg(msg, msg1);
//
//    std::this_thread::sleep_for(std::chrono::seconds(5));
//
//    // Get gas fee
//    double gasFee = chainClient.GetGasFee();
//
//    std::cout << "gas fee: " << gasFee << " INJ" << std::endl;

    return 0;
}
