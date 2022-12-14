#include <doctest/doctest.h>
#include <injective/greeter.h>
#include <injectivesdk/version.h>

#include <string>

TEST_CASE("Greeter") {
  using namespace injective;

  Greeter injective("Tests");

  CHECK(injective.greet(LanguageCode::EN) == "Hello, Tests!");
  CHECK(injective.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK(injective.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK(injective.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("Greeter version") {
  static_assert(std::string_view(INJECTIVESDK_VERSION) == std::string_view("1.0"));
  CHECK(std::string(INJECTIVESDK_VERSION) == std::string("1.0"));
}
