#include "Extension.hpp"

#include <sstream>
#include "../Helper.hpp"

namespace crispy
{
    inline constexpr ExtensionType Extension::SupportedExtensions[] =
    {
        ExtensionType::renegotiation_info 
    };

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
        ExtensionType::renegotiation_info };

    std::string Extension::toString() const
    {
        std::ostringstream oss;
        oss << "Extension: " << std::endl;
        oss << "\tType: " << this->extension_type.get() << std::endl;
        oss << "\tData length: " << this->extension_data_length.get() << std::endl;
        oss << "\tData: " << Helper::byteArrayToString(this->extension_data.data(), this->extension_data.size());
        oss << std::boolalpha;
        oss << "\tIs supported: " << Extension::isSupported(static_cast<ExtensionType>(this->extension_type.get())) << std::endl;
        oss << "\tIs recommanded: " << Extension::isRecommanded(static_cast<ExtensionType>(this->extension_type.get())) << std::endl;
        return oss.str();
    }

    bool Extension::isSupported(ExtensionType extension)
    {
        for (auto ext : SupportedExtensions)
        {
            if (ext == extension)
                return true;
        }
        return false;
    }

    bool Extension::isRecommanded(ExtensionType extension)
    {
        for (auto ext : RecommandedExtensions)
        {
            if (ext == extension)
                return true;
        }
        return false;
    }
}