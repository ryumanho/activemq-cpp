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

#ifndef _ACTIVEMQ_UTIL_IDGENERATORTEST_H_
#define _ACTIVEMQ_UTIL_IDGENERATORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace activemq {
namespace util {

    class IdGeneratorTest : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE( IdGeneratorTest );
        CPPUNIT_TEST( testConstructor1 );
        CPPUNIT_TEST( testConstructor2 );
        CPPUNIT_TEST( testCompare );
        CPPUNIT_TEST_SUITE_END();

    public:

        IdGeneratorTest();
        virtual ~IdGeneratorTest();

        void testConstructor1();
        void testConstructor2();
        void testCompare();

    };

}}

#endif /* _ACTIVEMQ_UTIL_IDGENERATORTEST_H_ */
