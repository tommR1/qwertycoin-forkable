// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2021, The Qwertycoin Group.
//
// This file is part of Qwertycoin.
//
// Qwertycoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Qwertycoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Qwertycoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <array>
#include <cstdint>
#include <streambuf>

namespace System {

class TcpConnection;

class TcpStreambuf : public std::streambuf {
public:
    explicit TcpStreambuf(TcpConnection &connection);
    TcpStreambuf(const TcpStreambuf &) = delete;
    ~TcpStreambuf() override;

    TcpStreambuf &operator=(const TcpStreambuf &) = delete;

private:
    std::streambuf::int_type overflow(std::streambuf::int_type ch) override;
    int sync() override;
    std::streambuf::int_type underflow() override;
    bool dumpBuffer(bool finalize);

private:
    TcpConnection &connection;
    std::array<char, 4096> readBuf;
    std::array<uint8_t, 1024> writeBuf;
};

} // namespace System