/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "LoggingInputStream.h"
#include <sstream>
#include <iomanip>
#include <activemq/exceptions/ExceptionDefines.h>

using namespace std;
using namespace activemq;
using namespace activemq::io;
using namespace decaf::io;
using namespace decaf::lang::exceptions;

LOGDECAF_INITIALIZE( logger, LoggingInputStream, "activemq.io.LoggingInputStream")

////////////////////////////////////////////////////////////////////////////////
LoggingInputStream::LoggingInputStream( decaf::io::InputStream* inputStream, bool own )
 : decaf::io::FilterInputStream( inputStream, own ) {}

////////////////////////////////////////////////////////////////////////////////
LoggingInputStream::~LoggingInputStream() {}

////////////////////////////////////////////////////////////////////////////////
int LoggingInputStream::read() throw ( IOException ) {
    try {

        unsigned char c = FilterInputStream::read();
        log( &c, 1 );
        return c;
    }
    AMQ_CATCH_RETHROW( IOException )
    AMQ_CATCHALL_THROW( IOException )
}

////////////////////////////////////////////////////////////////////////////////
int LoggingInputStream::read( unsigned char* buffer, std::size_t size, std::size_t offset, std::size_t length )
    throw ( decaf::io::IOException,
            decaf::lang::exceptions::IndexOutOfBoundsException,
            decaf::lang::exceptions::NullPointerException ) {

    try {

        if( length == 0 ) {
            return 0;
        }

        if( buffer == NULL ) {
            throw NullPointerException(
                __FILE__, __LINE__,
                "LoggingInputStream::read - Passed Buffer is Null" );
        }

        if( length > size - offset ) {
            throw IndexOutOfBoundsException(
                __FILE__, __LINE__,
                "Given size{%d} - offset{%d} is less than length{%d}.", size, offset, length );
        }

        std::size_t numRead = FilterInputStream::read( buffer, size, offset, length );

        log( buffer, numRead );

        return (int)numRead;
    }
    AMQ_CATCH_RETHROW( IOException )
    AMQ_CATCHALL_THROW( IOException )
}

////////////////////////////////////////////////////////////////////////////////
void LoggingInputStream::log( const unsigned char* buffer, size_t len ) {

    ostringstream ostream;

    ostream << "TCP Trace: Reading: " << endl << "[";

    for( size_t ix=0; ix<len; ++ix ){
        ostream << setw(2) << setfill('0') << std::hex << (int)buffer[ix];

        if( ((ix+1) % 2) == 0 ){
            ostream << ' ';
        }
    }

    ostream << "] len: " << std::dec << len << " bytes";

    // Log the data
    LOGDECAF_INFO( logger, ostream.str() )
}