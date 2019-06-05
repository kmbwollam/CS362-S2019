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

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision$
 */
public class UrlValidatorTest extends TestCase {

   private final boolean printStatus = false;
   private final boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }


    public static final String randomUrlSeed = "abcdefghijklmnopqrstuvwxyz";

    public static String randomUrl(int count){
        StringBuilder builder = new StringBuilder();
        while (count-- != 0){
            int character = (int)(Math.random()*randomUrlSeed.length());
            builder.append(randomUrlSeed.charAt(character));
        }
        return builder.toString();
    }

    public void testRandomScheme() {
        UrlValidator urlValidator = new UrlValidator(schemes, UrlValidator.ALLOW_ALL_SCHEMES);
        for (int i = 0; i < 100; i++) {
            String testScheme = randomUrl((int) (Math.random() * 10 + 1));
            String testUrl = testScheme + "://www.google.com";
            isValidTester(urlValidator, testUrl, true);
        }
    }

    public void testRandomPortAndScheme(){
        UrlValidator urlValidator = new UrlValidator(schemes, UrlValidator.ALLOW_ALL_SCHEMES);
        for (int i = 0; i < 100; i++){
            String testScheme= randomUrl((int)(Math.random()*10+1));
            int testPort = (int)(Math.random()*10000+1);
            String testUrl = testScheme + "://www.google.com:" + testPort;
            isValidTester(urlValidator,testUrl,true);
        }
    }

   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */

    public boolean isValidTester(UrlValidator testVal, String customUrl, boolean expected) {
        if(testVal.isValid(customUrl) == expected) {
            System.out.println(customUrl + " test passed");
            return true;
        }
        else {
            System.out.println(customUrl + " test expected " + expected + " but received " + !expected);
            return false;
        }
    }


   //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   private final String[] schemes = {"http", "gopher", "g0-To+.",
           "not_valid" // TODO this will need to be dropped if the ctor validates schemes
   };

    ResultPair[] testScheme = {new ResultPair("http", true),
            new ResultPair("ftp", false),
            new ResultPair("httpd", false),
            new ResultPair("gopher", true),
            new ResultPair("g0-to+.", true),
            new ResultPair("not_valid", false), // underscore not allowed
            new ResultPair("HtTp", true),
            new ResultPair("telnet", false)};



}
