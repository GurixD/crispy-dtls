#include "ClientHello.hpp"

#include "../DataReader.hpp"

namespace crispy
{
    std::tuple<ClientHello, bool> ClientHello::fromData(DataReader& dr)
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

        if (!ok)
            return { clientHello, false };

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

        return {clientHello, ok};
    }

    std::string ClientHello::toString() const
    {
        std::ostringstream ss;

        ss << "ClientHello: " << std::endl;
        ss << this->client_version.toString();
        ss << this->random.toString();
        ss << this->session_id.toString();
        ss << "Cookie length: " << static_cast<std::uint32_t>(this->cookie_length) << std::endl;
        ss << "Cookie: " << Helper::byteArrayToString(this->cookie.data(), this->cookie.size());
        ss << "Cipher suites length: " << this->cipher_suites_length.get() << std::endl;
        for (const auto& cipherSuite : this->cipher_suites)
        {
            ss << cipherSuite.toString();
        }
        ss << "Compression methods length: " << static_cast<std::uint32_t>(this->compression_methods_length) << std::endl;
        for (const auto& compressionMethod : this->compression_methods)
        {
            ss << static_cast<std::uint32_t>(compressionMethod) << std::endl;
        }
        ss << "Extensions length :" << this->extensions_length.get() << std::endl;
        for (const auto& extension : this->extensions)
        {
            ss << extension.toString();
        }

        return ss.str();
    }
}