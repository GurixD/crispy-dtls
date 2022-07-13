#pragma once

#include "ExtensionType.hpp"
#include "../bigendian/integer.hpp"
#include <cstddef>
#include <vector>

// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1

namespace dtls
{
    struct Extension
    {
        // ExtensionType extension_type;
        bigendian::uint16 extension_type;
        bigendian::uint16 extension_data_length; // <0..2 ^ 16 - 1>
        std::vector<std::byte> extension_data;

        static const ExtensionType SupportedExtensions[];
        static const ExtensionType RecommandedExtensions[];
        static constexpr bool isSupported(ExtensionType extension);
        static constexpr bool isRecommanded(ExtensionType extension);
    };

    inline constexpr ExtensionType Extension::SupportedExtensions[] =
        {
            ExtensionType::renegotiation_info};

    inline constexpr ExtensionType Extension::RecommandedExtensions[] =
        {
            ExtensionType::server_name,
            ExtensionType::client_certificate_url,
            ExtensionType::trusted_ca_keys,
            ExtensionType::status_request,
            ExtensionType::user_mapping,
            ExtensionType::supported_groups,
            ExtensionType::ec_point_formats,
            ExtensionType::signature_algorithms,
            ExtensionType::use_srtp,
            ExtensionType::heartbeat,
            ExtensionType::application_layer_protocol_negotiation,
            ExtensionType::status_request_v2,
            ExtensionType::client_certificate_type,
            ExtensionType::server_certificate_type,
            ExtensionType::padding,
            ExtensionType::encrypt_then_mac,
            ExtensionType::extended_master_secret,
            ExtensionType::token_binding,
            ExtensionType::cached_info,
            ExtensionType::compress_certificate,
            ExtensionType::record_size_limit,
            ExtensionType::session_ticket,
            ExtensionType::supported_ekt_ciphers,
            ExtensionType::pre_shared_key,
            ExtensionType::early_data,
            ExtensionType::supported_versions,
            ExtensionType::cookie,
            ExtensionType::psk_key_exchange_modes,
            ExtensionType::certificate_authorities,
            ExtensionType::oid_filters,
            ExtensionType::post_handshake_auth,
            ExtensionType::signature_algorithms_cert,
            ExtensionType::key_share,
            ExtensionType::transparency_info,
            ExtensionType::external_id_hash,
            ExtensionType::external_session_id,
            ExtensionType::quic_transport_parameters,
            ExtensionType::ticket_request,
            ExtensionType::renegotiation_info};

    inline constexpr bool Extension::isSupported(ExtensionType extension)
    {
        for (auto ext : SupportedExtensions)
        {
            if (ext == extension)
                return true;
        }
        return false;
    }

    inline constexpr bool Extension::isRecommanded(ExtensionType extension)
    {
        for (auto ext : RecommandedExtensions)
        {
            if (ext == extension)
                return true;
        }
        return false;
    }
}