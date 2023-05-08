//
// Created by a-ok123 on 5/6/23.
//

#ifndef INJECTIVESDK_CHAIN_CLIENT_H
#define INJECTIVESDK_CHAIN_CLIENT_H

#include <grpcpp/grpcpp.h>
// #include "injective/bank_service.grpc.pb.h"

#include "network.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

namespace injective {
    class ChainClient {
      private:
        std::shared_ptr<Channel> grpc_channel;
        injective::Network network;

//        client::Context ctx;
//        common::ClientOptions opts;

//        std::unique_ptr<bank::Query::Stub> bank_query_stub;

      public:
        ChainClient(injective::Network _network/*, std::vector<common::ClientOption> options*/);

        bool CanSignTransactions();
        sdk::AccAddress FromAddress();
        grpc::ClientConn QueryClient();
        client::Context ClientContext();
        //...

        //        bank::AllBalancesResponse GetBankBalances(const grpc::ClientContext& context,
        //                                                  const bank::AllBalancesRequest&
        //                                                  request);

        virtual ~ChainClient() = default;
    };
}  // namespace injective

#endif  // INJECTIVESDK_CHAIN_CLIENT_H
