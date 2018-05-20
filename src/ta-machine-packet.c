/*******************************************************************************
*This file is part of ta-machine.                                              *
*                                                                              *
*ta-machine is free software: you can redistribute it and/or modify            *
*it under the terms of the GNU General Public License as published by          *
*the Free Software Foundation, either version 3 of the License, or             *
*(at your option) any later version.                                           *
*                                                                              *
*ta-machine is distributed in the hope that it will be useful,                 *
*but WITHOUT ANY WARRANTY; without even the implied warranty of                *
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
*GNU General Public License for more details.                                  *
*                                                                              *
*You should have received a copy of the GNU General Public License             *
*along with ta-machine. If not, see <http://www.gnu.org/licenses/>.            *
*******************************************************************************/

//System includes
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <gpgme.h>

//Library includes

//local includes
#include "ta-machine.h"
#include "ta-machine-packet.h"

/* create SHA256 for the packet */
int function_tam_command_add_sha256(struct_tam_packet *ptr_packet)
{
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, ptr_packet->signed_certificate, SIGNED_CERTIFICATE_LEN);
    SHA256_Final(ptr_packet->packet_sha256, &ctx);

	return 0;
}
