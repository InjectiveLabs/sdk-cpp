#include <doctest/doctest.h>
#include <injective/network.h>
#include <injectivesdk/version.h>

#include <string>

TEST_CASE("Network") {
  using namespace injective;

  Network injective("Tests");

  CHECK(injective.greet(LanguageCode::EN) == "Hello, Tests!");
  CHECK(injective.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK(injective.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK(injective.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("Network version") {
  static_assert(std::string_view(INJECTIVESDK_VERSION) == std::string_view("1.0"));
  CHECK(std::string(INJECTIVESDK_VERSION) == std::string("1.0"));
}
