/*****************************************************************************
 * SRT - Secure, Reliable, Transport
 * Copyright (c) 2017 Haivision Systems Inc.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; If not, see <http://www.gnu.org/licenses/>
 * 
 * Based on UDT4 SDK version 4.11
 *****************************************************************************/

/*****************************************************************************
Copyright (c) 2001 - 2011, The Board of Trustees of the University of Illinois.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the
  above copyright notice, this list of conditions
  and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the University of Illinois
  nor the names of its contributors may be used to
  endorse or promote products derived from this
  software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

/*****************************************************************************
written by
   Yunhong Gu, last updated 01/27/2011
modified by
   Haivision Systems Inc.
*****************************************************************************/

#ifndef __UDT_CHANNEL_H__
#define __UDT_CHANNEL_H__


#include "udt.h"
#include "packet.h"
#include "netinet_any.h"

class CChannel
{
    void createSocket(int family);
public:

   // XXX There's currently no way to access the socket ID set for
   // whatever the channel is currently working for. Required to find
   // some way to do this, possibly by having a "reverse pointer".
   // Currently just "unimplemented".
   std::string CONID() const { return ""; }

   CChannel();
   ~CChannel();

      /// Open a UDP channel.
      /// @param addr [in] The local address that UDP will use.

   void open(const sockaddr_any& addr);

   void open(int family);

      /// Open a UDP channel based on an existing UDP socket.
      /// @param udpsock [in] UDP socket descriptor.

   void attach(UDPSOCKET udpsock, const sockaddr_any& adr);

      /// Disconnect and close the UDP entity.

   void close() const;

      /// Get the UDP sending buffer size.
      /// @return Current UDP sending buffer size.

   int getSndBufSize();

      /// Get the UDP receiving buffer size.
      /// @return Current UDP receiving buffer size.

   int getRcvBufSize();

      /// Set the UDP sending buffer size.
      /// @param size [in] expected UDP sending buffer size.

   void setSndBufSize(int size);

      /// Set the UDP receiving buffer size.
      /// @param size [in] expected UDP receiving buffer size.

   void setRcvBufSize(int size);

      /// Query the socket address that the channel is using.
      /// @param addr [out] pointer to store the returned socket address.

   void getSockAddr(ref_t<sockaddr_any> addr) const;

      /// Query the peer side socket address that the channel is connect to.
      /// @param addr [out] pointer to store the returned socket address.

   void getPeerAddr(ref_t<sockaddr_any> addr) const;

      /// Send a packet to the given address.
      /// @param addr [in] pointer to the destination address.
      /// @param packet [in] reference to a CPacket entity.
      /// @return Actual size of data sent.

   int sendto(const sockaddr_any& addr, CPacket& packet) const;

      /// Receive a packet from the channel and record the source address.
      /// @param addr [in] pointer to the source address.
      /// @param packet [in] reference to a CPacket entity.
      /// @return Actual size of data received.

   EReadStatus recvfrom(ref_t<sockaddr_any> addr, CPacket& packet) const;

#ifdef SRT_ENABLE_IPOPTS
      /// Set the IP TTL.
      /// @param ttl [in] IP Time To Live.
      /// @return none.

   void setIpTTL(int ttl);

      /// Set the IP Type of Service.
      /// @param tos [in] IP Type of Service.

   void setIpToS(int tos);

      /// Get the IP TTL.
      /// @param ttl [in] IP Time To Live.
      /// @return TTL.

   int getIpTTL() const;

      /// Get the IP Type of Service.
      /// @return ToS.

   int getIpToS() const;
#endif

   int ioctlQuery(int type) const;
   int sockoptQuery(int level, int option) const;

   const sockaddr* bindAddress() { return &m_BindAddr; }
   const sockaddr_any& bindAddressAny() { return m_BindAddr; }

private:
   void setUDPSockOpt();

private:
   //int m_iIPversion;                    // IP version
   //int m_iSockAddrSize;                 // socket address structure size (pre-defined to avoid run-time test)

   UDPSOCKET m_iSocket;                 // socket descriptor
#ifdef SRT_ENABLE_IPOPTS
   int m_iIpTTL;
   int m_iIpToS;
#endif
   int m_iSndBufSize;                   // UDP sending buffer size
   int m_iRcvBufSize;                   // UDP receiving buffer size
   sockaddr_any m_BindAddr;
};


#endif
