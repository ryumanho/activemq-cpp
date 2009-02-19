/**
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.apache.activemq.openwire.tool;

import org.codehaus.jam.JAnnotation;
import org.codehaus.jam.JAnnotationValue;
import org.codehaus.jam.JClass;
import org.codehaus.jam.JProperty;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;

/**
 *
 * @version $Revision: 381410 $
 */
public class AmqCppTestMarshallingClassesGenerator extends AmqCppTestMarshallingHeadersGenerator {

    protected String getFilePostFix() {
        return ".cpp";
    }

    protected void generateFile(PrintWriter out) throws Exception {
        generateLicence(out);

out.println("");
out.println("#include <activemq/wireformat/openwire/marshal/v"+getOpenwireVersion()+"/"+className+".h>");
out.println("");
out.println("#include <activemq/wireformat/openwire/marshal/v"+getOpenwireVersion()+"/"+super.getTargetClassName(jclass)+".h>");
out.println("#include <activemq/commands/"+jclass.getSimpleName()+".h>");
out.println("");
out.println("CPPUNIT_TEST_SUITE_REGISTRATION( activemq::wireformat::openwire::marshal::v"+getOpenwireVersion()+"::"+className+" );");
out.println("");
out.println("#include <activemq/wireformat/openwire/OpenWireFormat.h>");
out.println("#include <activemq/commands/DataStructure.h>");
out.println("#include <activemq/wireformat/openwire/utils/BooleanStream.h>");
out.println("#include <decaf/io/DataInputStream.h>");
out.println("#include <decaf/io/DataOutputStream.h>");
out.println("#include <decaf/io/IOException.h>");
out.println("#include <decaf/io/ByteArrayOutputStream.h>");
out.println("#include <decaf/io/ByteArrayInputStream.h>");
out.println("#include <decaf/util/Properties.h>");
out.println("//");
out.println("//     NOTE!: This file is autogenerated - do not modify!");
out.println("//            if you need to make a change, please see the Java Classes in the");
out.println("//            activemq-core module");
out.println("//");
out.println("");
out.println("using namespace std;");
out.println("using namespace activemq;");
out.println("using namespace activemq::util;");
out.println("using namespace activemq::exceptions;");
out.println("using namespace activemq::commands;");
out.println("using namespace activemq::wireformat;");
out.println("using namespace activemq::wireformat::openwire;");
out.println("using namespace activemq::wireformat::openwire::marshal;");
out.println("using namespace activemq::wireformat::openwire::utils;");
out.println("using namespace activemq::wireformat::openwire::marshal::v"+getOpenwireVersion()+";");
out.println("using namespace decaf::io;");
out.println("using namespace decaf::lang;");
out.println("using namespace decaf::util;");
out.println("");
out.println("///////////////////////////////////////////////////////////////////////////////");
out.println("void "+className+"::test() {");
out.println("");
out.println("    "+ super.getTargetClassName(jclass) + " myMarshaller;");
out.println("    "+ jclass.getSimpleName() + " myCommand;");
out.println("    "+ jclass.getSimpleName() + "* myCommand2;");
out.println("");
out.println("    CPPUNIT_ASSERT( myMarshaller.getDataStructureType() == myCommand.getDataStructureType() );");
out.println("    myCommand2 = dynamic_cast<"+jclass.getSimpleName()+"*>( myMarshaller.createObject() );");
out.println("    CPPUNIT_ASSERT( myCommand2 != NULL );");
out.println("    delete myCommand2;");
out.println("}");
out.println("");
out.println("///////////////////////////////////////////////////////////////////////////////");
out.println("void "+className+"::testLooseMarshal() {");
out.println("");
out.println("    "+ super.getTargetClassName(jclass) +" marshaller;");
out.println("    Properties props;");
out.println("    OpenWireFormat openWireFormat( props );");
out.println("");
out.println("    // Configure for this test.");
out.println("    openWireFormat.setVersion( "+getOpenwireVersion()+" );");
out.println("    openWireFormat.setTightEncodingEnabled( false );");
out.println("");
out.println("    "+jclass.getSimpleName()+" outCommand;");
out.println("    "+jclass.getSimpleName()+" inCommand;");
out.println("");
out.println("    try {");
out.println("");
out.println("        // Marshal the dataStructure to a byte array.");
out.println("        ByteArrayOutputStream baos;");
out.println("        DataOutputStream dataOut( &baos );");
out.println("        dataOut.writeByte( outCommand.getDataStructureType() );");
out.println("        marshaller.looseMarshal( &openWireFormat, &outCommand, &dataOut );");
out.println("");
out.println("        // Now read it back in and make sure it's all right.");
out.println("        ByteArrayInputStream bais( baos.toByteArray(), baos.size() );");
out.println("        DataInputStream dataIn( &bais );");
out.println("        unsigned char dataType = dataIn.readByte();");
out.println("        CPPUNIT_ASSERT( dataType == outCommand.getDataStructureType() );");
out.println("        marshaller.looseUnmarshal( &openWireFormat, &inCommand, &dataIn );");
out.println("");
out.println("        CPPUNIT_ASSERT( inCommand.equals( &outCommand ) == true );");
out.println("");
out.println("    } catch( ActiveMQException& e ) {");
out.println("        e.printStackTrace();");
out.println("        CPPUNIT_ASSERT( false );");
out.println("    } catch( ... ) {");
out.println("        CPPUNIT_ASSERT( false );");
out.println("    }");
out.println("}");
out.println("");
out.println("///////////////////////////////////////////////////////////////////////////////");
out.println("void "+className+"::testTightMarshal() {");
out.println("");
out.println("    "+ super.getTargetClassName(jclass) +" marshaller;");
out.println("    Properties props;");
out.println("    OpenWireFormat openWireFormat( props );");
out.println("");
out.println("    // Configure for this test.");
out.println("    openWireFormat.setVersion( "+getOpenwireVersion()+" );");
out.println("    openWireFormat.setTightEncodingEnabled( true );");
out.println("");
out.println("    "+jclass.getSimpleName()+" outCommand;");
out.println("    "+jclass.getSimpleName()+" inCommand;");
out.println("");
out.println("    try {");
out.println("");
out.println("        // Marshal the dataStructure to a byte array.");
out.println("        ByteArrayOutputStream baos;");
out.println("        DataOutputStream dataOut( &baos );");
out.println("        // Phase 1 - count the size");
out.println("        int size = 1;");
out.println("        BooleanStream bs;");
out.println("        size += marshaller.tightMarshal1( &openWireFormat, &outCommand, &bs );");
out.println("        size += bs.marshalledSize();");
out.println("        // Phase 2 - marshal");
out.println("        dataOut.writeByte( outCommand.getDataStructureType() );");
out.println("        bs.marshal( &dataOut );");
out.println("        marshaller.tightMarshal2( &openWireFormat, &outCommand, &dataOut, &bs );");
out.println("");
out.println("        // Now read it back in and make sure it's all right.");
out.println("        ByteArrayInputStream bais( baos.toByteArray(), baos.size() );");
out.println("        DataInputStream dataIn( &bais );");
out.println("");
out.println("        unsigned char dataType = dataIn.readByte();");
out.println("        CPPUNIT_ASSERT( dataType == outCommand.getDataStructureType() );");
out.println("        bs.clear();");
out.println("        bs.unmarshal( &dataIn );");
out.println("        marshaller.tightUnmarshal( &openWireFormat, &inCommand, &dataIn, &bs );");
out.println("");
out.println("        CPPUNIT_ASSERT( inCommand.equals( &outCommand ) == true );");
out.println("");
out.println("    } catch( ActiveMQException& e ) {");
out.println("        e.printStackTrace();");
out.println("        CPPUNIT_ASSERT( false );");
out.println("    } catch( ... ) {");
out.println("        CPPUNIT_ASSERT( false );");
out.println("    }");
out.println("}");
out.println("");
    }

}
