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

#include "WriterTest.h"

#include <decaf/io/Writer.h>
#include <decaf/nio/CharBuffer.h>
#include <decaf/lang/exceptions/IndexOutOfBoundsException.h>

using namespace std;
using namespace decaf;
using namespace decaf::io;
using namespace decaf::nio;
using namespace decaf::lang::exceptions;

////////////////////////////////////////////////////////////////////////////////
namespace decaf{
namespace io{

    class MockWriter : public Writer {
    private:

        char* contents;
        std::size_t length;
        std::size_t offset;

    public:

        MockWriter( std::size_t capacity ) {
            contents = new char[capacity];
            length = capacity;
            offset = 0;
        }

        virtual ~MockWriter() {
            close();
        }

        virtual void close() throw( decaf::io::IOException ) {
            flush();
            delete contents;
            contents = NULL;
        }

        virtual void flush() throw( decaf::io::IOException ) {
        }

        virtual void write( const char* buffer, std::size_t offset, std::size_t count )
            throw( decaf::io::IOException, lang::exceptions::NullPointerException ) {

            if( NULL == contents ) {
                throw IOException( __FILE__, __LINE__, "Writer was already closed." );
            }

            if( offset >= count ) {
                throw IndexOutOfBoundsException( __FILE__, __LINE__, "offset must be less than count." );
            }

            for( std::size_t i = 0; i < count; i++ ) {
                contents[this->offset + i] = buffer[offset + i];
            }

            this->offset += count;

        }

        virtual void write( char v )
            throw( IOException ) {

            Writer::write( v );
        }

        virtual void write( const std::vector<char>& buffer )
            throw( IOException ) {

            Writer::write( buffer );
        }

        virtual void write( const std::string& str )
            throw( IOException ) {

            Writer::write( str );
        }

        virtual void write( const std::string& str, std::size_t offset, std::size_t count )
            throw( IOException, lang::exceptions::IndexOutOfBoundsException ) {

            Writer::write( str, offset, count );
        }

        std::vector<char> getContents() {

            std::vector<char> result( offset );

            for( std::size_t i = 0; i < offset; i++ ) {
                result[i] = contents[i];
            }

            return result;
        }
    };

}}

////////////////////////////////////////////////////////////////////////////////
WriterTest::WriterTest() {
}

////////////////////////////////////////////////////////////////////////////////
WriterTest::~WriterTest() {
}

////////////////////////////////////////////////////////////////////////////////
void WriterTest::testWriteChar() {

    std::string testString = "My Test String";
    MockWriter writer( 20 );

    std::string::const_iterator iter = testString.begin();
    for( ; iter != testString.end(); ++iter ) {
        writer.write( *iter );
    }

    std::vector<char> result = writer.getContents();
    CPPUNIT_ASSERT_EQUAL( testString, std::string( result.begin(), result.end() ) );
}

////////////////////////////////////////////////////////////////////////////////
void WriterTest::testWriteVector() {

    std::string testString = "My Test String";
    MockWriter writer( 20 );

    std::vector<char> buffer( testString.begin(), testString.end() );
    writer.write( buffer );

    std::vector<char> result = writer.getContents();
    CPPUNIT_ASSERT_EQUAL( testString, std::string( result.begin(), result.end() ) );
}

////////////////////////////////////////////////////////////////////////////////
void WriterTest::testWriteString() {

    std::string testString = "My Test String";
    MockWriter writer( 20 );

    writer.write( testString );

    std::vector<char> result = writer.getContents();
    CPPUNIT_ASSERT_EQUAL( testString, std::string( result.begin(), result.end() ) );
}

////////////////////////////////////////////////////////////////////////////////
void WriterTest::testWriteStringOffsetCount() {

    std::string testString = "My Test String";
    MockWriter writer( 20 );

    writer.write( testString, 0, testString.length() );

    std::vector<char> result = writer.getContents();
    CPPUNIT_ASSERT_EQUAL( testString, std::string( result.begin(), result.end() ) );
}

////////////////////////////////////////////////////////////////////////////////
void WriterTest::testAppendChar() {

    char testChar = ' ';
    MockWriter writer(20);

    writer.append( testChar );

    CPPUNIT_ASSERT_EQUAL( testChar, writer.getContents()[0] );

    writer.close();
}

////////////////////////////////////////////////////////////////////////////////
void WriterTest::testAppendCharSequence() {

    std::string testString = "My Test String";
    MockWriter writer( 20 );

    CharBuffer* buffer = CharBuffer::allocate( testString.size() );
    buffer->put( testString );
    buffer->rewind();

    writer.append( buffer );

    std::vector<char> result = writer.getContents();
    CPPUNIT_ASSERT_EQUAL( testString, std::string( result.begin(), result.end() ) );

    writer.close();

    delete buffer;
}

////////////////////////////////////////////////////////////////////////////////
void WriterTest::testAppendCharSequenceIntInt() {

    std::string testString = "My Test String";
    MockWriter writer(20);

    CharBuffer* buffer = CharBuffer::allocate( testString.size() );
    buffer->put( testString );
    buffer->rewind();

    writer.append( buffer, 1, 3 );

    std::vector<char> result = writer.getContents();
    CPPUNIT_ASSERT_EQUAL( testString.substr( 1, 2 ), std::string( result.begin(), result.end() ) );

    writer.close();

    delete buffer;
}
