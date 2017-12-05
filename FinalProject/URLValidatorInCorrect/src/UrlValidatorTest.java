/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.util.Random;




/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

	private boolean printStatus = false;
	private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

	public UrlValidatorTest(String testName) {
		super(testName);
	}
	
	public void testManualTest()
	{
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		System.out.println(urlVal.isValid("http://www.amazon.com"));


	}


	public void testYourFirstPartition()
	{

	}

	public void testYourSecondPartition(){

	}
	
	public void testIsValid() {
		testIsValid(testUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
	}
	/*
	 * Object[] testUrlParts = {testSchemes, testAuthority, testPort, testPath};
	 * rand.nextInt((max - min) + 1) + min;
	 */
	public void testIsValid(Object[] urlParts, long options)
	{
		Random rand = new Random();
		UrlValidator urlVal = new UrlValidator(null, null, options);
		assertTrue(urlVal.isValid("http://www.oregonstate.edu"));
		assertTrue(urlVal.isValid("http://www.oregonstate.edu/"));
		
		int numCases  =  25;
		System.out.println("TESTING "+numCases+" CASES");
		for (int i = 0; i < numCases; i++ ) {
			System.out.println("TEST "+i);
			boolean expectedValid = true;
			StringBuffer partbuffer = new StringBuffer();
			
			for( int indicesIndex = 0; indicesIndex < 4; indicesIndex++) {
				int whichPart = rand.nextInt(testPartsIndices[indicesIndex]);
				ResultPair[] part = (ResultPair[]) urlParts[indicesIndex];
				partbuffer.append(part[whichPart].item);
				expectedValid &= part[whichPart].valid;
			}
			
			String url = partbuffer.toString();
			boolean actualValid = urlVal.isValid(url);
			
			if(expectedValid == actualValid) {
				System.out.println("CASE \""+url+"\" : PASSED");
				System.out.println("	EXPECTED:"+expectedValid+"  isValid output:"+actualValid+"\n");
			}
			else {
				System.out.println("CASE \""+url+"\" : FAILED");
				System.out.println("	EXPECTED:"+expectedValid+"  isValid output:"+actualValid+"\n");
			}
			
		}
	}



	public void testAnyOtherUnitTest()
	{
	
	}
	/**
	 * Create set of tests by taking the testUrlXXX arrays and
	 * running through all possible permutations of their combinations.
	 *
	 * @param testObjects Used to create a url.
	 */

	
	/*Data parts for tests
	 * 
	 */
	ResultPair[] testSchemes = {
		new ResultPair("http://", true),
		new ResultPair("https://", true),
		new ResultPair("httpa://", false)
	}; 
	
	ResultPair[] testAuthority = {
			new ResultPair("www.oregonstate.edu", true),
			new ResultPair("a.com", true),
			new ResultPair("a.co1", false),
			new ResultPair("a.cc",true),
			new ResultPair("a", false),
			new ResultPair(".abcd", false),
			new ResultPair("-a.131.com", false),
			new ResultPair("123.com", true),
			new ResultPair("255.255.255.255", true),
			new ResultPair("1.1.1.", false),
			new ResultPair(".1.1.1", false),
			new ResultPair("hello.1", false)
	};
	ResultPair[] testPort = {
			new ResultPair("", true),
			new ResultPair(":65656", true),
			new ResultPair(":80", true),
			new ResultPair(":8080", true),
			new ResultPair("1111", false),
			new ResultPair(":123q", false),
			new ResultPair(":qwerty", false),
			new ResultPair(":-67", false)
	};
	
	ResultPair[] testPath = {
			new ResultPair("/hello", true),
			new ResultPair("/hello/", true),
			new ResultPair("/hello/world", true),
			new ResultPair("/r2", true),
			new ResultPair("/r2/d2", true),
			new ResultPair("/$55", true),
			new ResultPair("", true),
			new ResultPair("/hello//world", false),
			new ResultPair(".", false),
			new ResultPair("/..", false),
			new ResultPair("/../", false),
			new ResultPair("/../thing", false),
			new ResultPair("/..//thing", false),
			new ResultPair("/#", true),
			new ResultPair("/#/one", true)
	};


	Object[] testUrlParts = {testSchemes, testAuthority, testPort, testPath};
	int[] testPartsIndices = {testSchemes.length,testAuthority.length,testPort.length,testPath.length};

}
