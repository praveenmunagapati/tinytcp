//----------------------------------------------------------------------------
// Copyright( c ) 2015, Robert Kimball
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------------------

#ifndef PROTOCOLIPV4_H
#define PROTOCOLIPV4_H

#include <inttypes.h>
#include "osQueue.h"
#include "DataBuffer.h"

#define IP_HEADER_SIZE (20)

class ProtocolIPv4
{
public:
   static const int AddressSize = 4;
   struct AddressInfo
   {
      bool  DataValid;
      uint8_t Address[ AddressSize ];
      uint32_t IpAddressLeaseTime;
      uint32_t RenewTime;
      uint32_t RebindTime;
      uint8_t SubnetMask[ AddressSize ];
      uint8_t Gateway[ AddressSize ];
      uint8_t DomainNameServer[ AddressSize ];
      uint8_t BroadcastAddress[ AddressSize ];
   };

   static void Initialize();

   static void ProcessRx( DataBuffer*, const uint8_t* hardwareAddress );

   static void Transmit( DataBuffer*, uint8_t protocol, const uint8_t* targetIP, const uint8_t* sourceIP );
   static void Retransmit( DataBuffer* );

   static void Retry();

   static uint8_t* GetUnicastAddress();
   static uint8_t* GetBroadcastAddress();
   static uint8_t* GetGatewayAddress();
   static uint8_t* GetSubnetMask();
   static void SetAddressInfo( const AddressInfo& info );
   
   static DataBuffer* GetTxBuffer();
   static void FreeTxBuffer( DataBuffer* );
   static void FreeRxBuffer( DataBuffer* );

   static void Show( osPrintfInterface* out );

private:
   static bool IsLocal( const uint8_t* addr );

   static uint16_t PacketID;
   static osQueue UnresolvedQueue;

   static AddressInfo Address;

   ProtocolIPv4();
   ProtocolIPv4( ProtocolIPv4& );
};

#endif