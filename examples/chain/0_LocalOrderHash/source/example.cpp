#include <injective/network.h>
#include "restc-cpp/restc-cpp.h"
#include <iostream>

using namespace injective;
using namespace std;
using namespace restc_cpp;

void DoGet(Context& ctx) {
    // Here we are in a co-routine, running in a worker-thread.

    // Asynchronously connect to a server and fetch some data.
    auto reply = ctx.Get("http://jsonplaceholder.typicode.com/posts/1");

    // Asynchronously fetch the entire data-set and return it as a string.
    auto json = reply->GetBodyAsString();

    // Just dump the data.
    cout << "Received data: " << json << endl;
}

auto main() -> int {
  const auto& network = Network::LoadNetwork("testnet", "k8s");
  cout << network.LcdEndpoint << endl;

  auto rest_client = RestClient::Create();

  rest_client->Process(DoGet);

  rest_client->CloseWhenReady(true);
  return 0;
}