#*******************************************************************************
#This file is part of ta-machine.                                              *
#                                                                              *
#ta-machine is free software: you can redistribute it and/or modify            *
#it under the terms of the GNU General Public License as published by          *
#the Free Software Foundation, either version 3 of the License, or             *
#(at your option) any later version.                                           *
#                                                                              *
#ta-machine is distributed in the hope that it will be useful,                 *
#but WITHOUT ANY WARRANTY; without even the implied warranty of                *
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
#GNU General Public License for more details.                                  *
#                                                                              *
#You should have received a copy of the GNU General Public License             *
#along with ta-machine. If not, see <http://www.gnu.org/licenses/>.            *
#******************************************************************************/

#COMMANDS
GCC=gcc
GCCOPTS=-O3 -Wall -lcrypto

#Check these paths
OPENSSL=/usr/local/opt/openssl

# Root directory
ROOT_TAM=.

################################################################################
#below this should not need any modifications
################################################################################

#Directory path
SRCDIR=$(ROOT_TAM)/src
INCDIR=$(ROOT_TAM)/inc
BINDIR=$(ROOT_TAM)/bin
ARGTABLEDIR=$(ROOT_TAM)/lib/argtable3

#target
EXEFILE=$(BINDIR)/ta-machine

#incdirs
INCPATHS=	-I$(ARGTABLEDIR) \
			-I$(OPENSSL)/include \
			-I$(INCDIR)

#files
SRCFILES=								\
			$(ARGTABLEDIR)/argtable3.c	\
			$(SRCDIR)/ta-machine-packet.c \
			$(SRCDIR)/ta-machine-main.c

#Get the Git version of the code
$(eval TAM_HASH = $(shell cd ${ROOT_TAM}; git rev-parse --short HEAD))
#echo "Version of TA-Machine used in compile is $(TAM_HASH)"

all: $(BINDIR) version $(EXEFILE) 


#argtable3:
#	if [ ! -d "$(ARGTABLEDIR)" ]; then \
#		echo "please install argtable3 v3.0.3"; exit(1); \
#	else \
#		HASH := $(shell git rev-parse --short HEAD); \
#		ifne ($(HASH), "611d160") \
#			error("Checkout argtable to HASH 611d160);\
#		endif \
#	fi

$(BINDIR):
	if [ ! -d "$(BINDIR)" ]; then  \
		mkdir -p $(BINDIR); \
	fi

version: 
	sed -i -e 's/TAM_VERSION.*/TAM_VERSION 0x$(TAM_HASH)/g' $(INCDIR)/ta-machine-version.h

$(EXEFILE): $(SRCFILES) $(INCFILES)
	$(GCC) 							\
	$(GCCOPTS) 						\
	$(GPGINC) 						\
	$(shell gpgme-config --cflags --libs)	\
	$(INCPATHS) 					\
	$(SRCFILES) 					\
	-o $(EXEFILE)

clean:
	rm -rf $(EXEFILE)
