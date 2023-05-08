//
// Created by a-ok123 on 5/7/23.
//

#include <injective/chain_client.h>

using namespace injective;

ChainClient::ChainClient(injective::Network _network/*, std::vector<common::ClientOption> options*/)
    : network(std::move(_network)) {
    std::string protoAddr = network.ChainGrpcEndpoint;
    grpc_channel = grpc::CreateChannel(protoAddr, grpc::InsecureChannelCredentials());

    //    bank_query_stub = bank::Query::NewStub(grpc_channel);

    // process options, setup connection, initialize members, etc.
}

bool ChainClient::CanSignTransactions() {
    // implementation
}

sdk::AccAddress ChainClient::FromAddress() {
    // implementation
}

grpc::ClientConn ChainClient::QueryClient() {
    // implementation
}

client::Context ChainClient::ClientContext() {
    // implementation
}

// ... more method implementations

ChainClient::~ChainClient() {
    // clean up resources
}

