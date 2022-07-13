#pragma once

#include "ProtocolVersion.hpp"
#include "Random.hpp"
#include "SessionID.hpp"
#include <cstdint>
#include <cstddef>
#include <vector>
#include "../bigendian/integer.hpp"
#include "CipherSuite.hpp"
#include "CompressionMethod.hpp"
#include "Extension.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../DataReader.hpp"

// https://datatracker.ietf.org/doc/html/rfc6347#section-4.3.2 (dtls)
// https://datatracker.ietf.org/doc/html/rfc5246#appendix-A.4.1 (tls for extensions)

namespace dtls
{

    struct ClientHello
    {
        ProtocolVersion client_version;
        Random random;
        SessionID session_id;
        std::uint8_t cookie_length;                         // <0..2 ^ 8 - 1>
        std::vector<std::byte> cookie; 
        bigendian::uint16 cipher_suites_length;             // <2..2 ^ 16 - 1>
        std::vector<CipherSuite> cipher_suites;
        std::uint8_t compression_methods_length;            // <1..2 ^ 8 - 1>
        std::vector<CompressionMethod> compression_methods;
        bigendian::uint16 extensions_length;                // <0..2 ^ 16 - 1>
        std::vector<Extension> extensions;

        static std::tuple<ClientHello, bool> fromData(DataReader& dr)
        {
            ClientHello clientHello{};
            dr.startTransaction();

            clientHello.client_version.major = dr.read<std::uint8_t>();
            clientHello.client_version.minor = dr.read<std::uint8_t>();

            clientHello.random.fromData(dr);

            clientHello.session_id.session_id_length = dr.read<std::uint8_t>();
            dr.read(clientHello.session_id.session_id, clientHello.session_id.session_id_length);

            clientHello.cookie_length = dr.read<std::uint8_t>();
            dr.read(clientHello.cookie, clientHello.cookie_length);

            clientHello.cipher_suites_length = dr.read<bigendian::uint16>();
            dr.read(clientHello.cipher_suites, clientHello.cipher_suites_length.get());

            clientHello.compression_methods_length = dr.read<std::uint8_t>();
            dr.read(clientHello.compression_methods, clientHello.compression_methods_length);

            bool ok = dr.checkTransaction();

            if (dr.left() > 0)
            {
                dr.startTransaction();
                clientHello.extensions_length = dr.read<bigendian::uint16>();
                do
                {
                    Extension ext;
                    ext.extension_type = dr.read<bigendian::uint16>();
                    ext.extension_data_length = dr.read<bigendian::uint16>(); // <0..2 ^ 16 - 1>
                    dr.read(ext.extension_data, ext.extension_data_length.get());

                    clientHello.extensions.push_back(ext);
                } while (dr.left() > 0);

                if (!dr.checkTransaction())
                {
                    clientHello.extensions_length = 0;
                    clientHello.extensions.clear();
                    std::cerr << "Data after ClientHello but transaction failed" << std::endl;
                }
            }
            else
            {
                clientHello.extensions_length = 0;
            }

            return { clientHello , ok };
        }

        std::string toString()
        {
            std::ostringstream ss;

            //ProtocolVersion client_version;
            //Random random;
            //SessionID session_id;
            //std::uint8_t cookie_length;                         // <0..2 ^ 8 - 1>
            //std::vector<std::byte> cookie;
            //bigendian::uint16 cipher_suites_length;             // <2..2 ^ 16 - 1>
            //std::vector<CipherSuite> cipher_suites;
            //std::uint8_t compression_methods_length;            // <1..2 ^ 8 - 1>
            //std::vector<CompressionMethod> compression_methods;
            //bigendian::uint16 extensions_length;                // <0..2 ^ 16 - 1>
            //std::vector<Extension> extensions;


            ss << "ClientHello: " << std::endl;
            ss << "ProtocolVersion: " << static_cast<std::uint16_t>(this->client_version.major) << "." << static_cast<std::uint16_t>(this->client_version.minor) << std::endl;
            ss << this->random.toString() << std::endl;


            return ss.str();
        }
    };

}