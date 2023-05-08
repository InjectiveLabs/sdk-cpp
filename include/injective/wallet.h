//
// Created by a-ok123 on 5/7/23.
//

#ifndef INJECTIVESDK_WALLET_H
#define INJECTIVESDK_WALLET_H

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>

#include <fmt/format.h>
#include <bech32.h>
#include <sodium.h>
#include <bitcoin/wallet/mnemonic.hpp>
#include <bitcoin/wallet/hd_private.hpp>
#include <bitcoin/utility/data.hpp>
#include <bitcoin/utility/pseudo_random.hpp>
#include <bitcoin/math/elliptic_curve.hpp>

namespace inj_crypto {

    namespace detail {

        constexpr auto BECH32_PUBKEY_ACC_PREFIX = "injpub";
        constexpr auto BECH32_PUBKEY_VAL_PREFIX = "injvaloperpub";
        constexpr auto BECH32_PUBKEY_CONS_PREFIX = "injvalconspub";

        constexpr auto BECH32_ADDR_ACC_PREFIX = "inj";
        constexpr auto BECH32_ADDR_VAL_PREFIX = "injvaloper";
        constexpr auto BECH32_ADDR_CONS_PREFIX = "injvalcons";

        constexpr auto DEFAULT_DERIVATION_PATH = "m/44'/60'/0'/0/0";

        constexpr size_t ENTROPY_BITS = 128;
        constexpr size_t ENTROPY_BYTES = ENTROPY_BITS / 8;

    }  // namespace detail

    class PrivateKey {
      public:
        static std::tuple<std::vector<std::string>, PrivateKey> generate(const std::string& path
                                                            = detail::DEFAULT_DERIVATION_PATH) {

            bc::data_chunk entropy(detail::ENTROPY_BYTES);
            bc::pseudo_random_fill(entropy);

            auto phrase = bc::wallet::create_mnemonic(entropy);
            return {
                phrase,
                PrivateKey::from_mnemonic(phrase, path)
            };
        }

        static PrivateKey from_mnemonic(const std::vector<std::string>& words,
                                        const std::string& path = detail::DEFAULT_DERIVATION_PATH) {
            PrivateKey self;
            auto seed = bc::wallet::decode_mnemonic(words);
            self.signing_key = bc::wallet::hd_private(seed, bc::wallet::hd_public::mainnet);
            self.signing_key = self.signing_key.derive_private(bc::wallet::hd_key::to_prefix(path));
            return self;
        }

        static PrivateKey from_hex(const std::string& priv) {
            PrivateKey self;
            self.signing_key = bc::wallet::hd_private(bc::wallet::ec_secret(priv));
            return self;
        }

        std::string to_hex() const { return signing_key.secret().encode(); }

        // Other methods...

      private:
        PrivateKey() = default;

        bc::wallet::hd_private signing_key;
    };

    class PublicKey {
      private:
        bc::data_chunk verify_key;

      public:
        // Constructor
        PublicKey() {}

        // Initialize from compressed public key bytes
        void from_compressed(const bc::data_chunk& compressed_pubkey) {
            verify_key = compressed_pubkey;
        }

        // Get hex representation of the public key
        std::string to_hex() const { return bc::encode_base16(verify_key); }

        // Get Bech32 representation of the public key
        std::string to_bech32(const std::string& hrp) const {
            bc::data_chunk pubkey_data = bc::build_chunk({0xeb, 0x5a, 0xe9, 0x87, 0x21});
            bc::extend_data(pubkey_data, verify_key);
            return wallet::cashaddr::encode(hrp, pubkey_data);
        }

        // Verify signature
        bool verify(const bc::data_chunk& msg, const bc::data_chunk& sig) const {
            bc::short_hash hash;
            crypto_hash_sha256(reinterpret_cast<unsigned char*>(hash.data()), msg.data(),
                               msg.size());

            return crypto_sign_verify_detached(sig.data(), hash.data(), hash.size(),
                                               verify_key.data())
                   == 0;
        }
    };

    // PublicKey and Address classes...

}  // namespace inj_crypto

namespace injective {

    class wallet {};

}  // namespace injective

#endif  // INJECTIVESDK_WALLET_H
