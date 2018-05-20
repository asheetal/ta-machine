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

#ifndef _TA_MACHINE_PACKET_H
#define _TA_MACHINE_PACKET_H

#include <gpgme.h>
#include <openssl/sha.h>

#define SIGNED_CERTIFICATE_LEN 256

/* maximum structure size must be 2048 bytes or 16 kilobits*/

typedef struct struct_tam_packet
{
	unsigned char signed_certificate[SIGNED_CERTIFICATE_LEN]; 
	unsigned char packet_sha256[SHA256_DIGEST_LENGTH];       /* 32 bytes */
} struct_tam_packet;

/* functions defined in this structure */
int function_tam_command_add_sha256(struct_tam_packet *ptr_packet);

#endif /* _TA_MACHINE_PACKET_H */
