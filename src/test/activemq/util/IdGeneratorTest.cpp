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

#include "IdGeneratorTest.h"

#include <activemq/util/IdGenerator.h>

using namespace activemq;
using namespace activemq::util;

////////////////////////////////////////////////////////////////////////////////
IdGeneratorTest::IdGeneratorTest() {
}

////////////////////////////////////////////////////////////////////////////////
IdGeneratorTest::~IdGeneratorTest() {
}

////////////////////////////////////////////////////////////////////////////////
void IdGeneratorTest::testConstructor1() {

    IdGenerator idGen;

    CPPUNIT_ASSERT( idGen.generateId() != "" );
    CPPUNIT_ASSERT( idGen.generateId() != "" );
}

////////////////////////////////////////////////////////////////////////////////
void IdGeneratorTest::testConstructor2() {

    IdGenerator idGen( "TEST-PREFIX" );

    std::string id = idGen.generateId();
    std::size_t pos = id.find( "TEST-PREFIX" );

    CPPUNIT_ASSERT( pos != std::string::npos );
}

////////////////////////////////////////////////////////////////////////////////
void IdGeneratorTest::testCompare() {

    IdGenerator idGen;

    std::string id1 = idGen.generateId();
    std::string id2 = idGen.generateId();

    CPPUNIT_ASSERT( IdGenerator::compare( id1, id1 ) == 0 );
    CPPUNIT_ASSERT( IdGenerator::compare( id1, id2 ) < 0 );
    CPPUNIT_ASSERT( IdGenerator::compare( id2, id1 ) > 0 );
}
