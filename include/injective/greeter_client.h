#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;

namespace injective {

    class GreeterClient {
    public:
        GreeterClient(std::shared_ptr<Channel> channel)
          : stub_(Greeter::NewStub(channel)) {}

    private:
        std::unique_ptr<Greeter::Stub> stub_;
    };

}  // namespace injective
