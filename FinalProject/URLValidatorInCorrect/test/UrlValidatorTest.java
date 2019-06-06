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

    public void testUnitScheme(){
        UrlValidator urlVal = new UrlValidator(schemes, UrlValidator.ALLOW_ALL_SCHEMES);
        // Test Schemes...keep same valid Authority test different schemes
        isValidTester(urlVal, "http://www.google.com", true);
        isValidTester(urlVal, "https://www.google.com", true);
        isValidTester(urlVal, "https://www.google.com", true);
        isValidTester(urlVal, "ssh://www.google.com", true);
        isValidTester(urlVal, "mailto://www.google.com", true);
        isValidTester(urlVal, "go://www.google.com", true);
        isValidTester(urlVal, "://www.google.com", false);
    }

    public void testUnitAuthorities(){
        UrlValidator urlVal = new UrlValidator();

        // Test Authorities ... keep same valid scheme test different Authorities
        isValidTester(urlVal, "http://w89er.google.jfla;", false);
        isValidTester(urlVal, "http://www.google.com", true);
        isValidTester(urlVal, "http://www.google.edu", true);
        isValidTester(urlVal, "http://www.google.gov", true);
        isValidTester(urlVal, "http://google\\ffaklg.com", false);
        isValidTester(urlVal, "http://www.google.cc", true);
        isValidTester(urlVal, "http://65.173.211", true);
        isValidTester(urlVal, "http://[2600::aaaa]:8080", true);
        isValidTester(urlVal, "http://www.youtube.com", true);
        isValidTester(urlVal, "http://www.baidu.com", true);
        isValidTester(urlVal, "http://www.wikipedia.org", true);
        isValidTester(urlVal, "http://www.sina.com.cn", true);
        isValidTester(urlVal, "http://www.yahoo.co.jp", true);
        isValidTester(urlVal, "http://www.google.de", true);
        isValidTester(urlVal, "http://www.chinadaily.com.cn", true);
        isValidTester(urlVal, "http://www.google.co.id", true);
        isValidTester(urlVal, "http://www.doubleclick.net", true);
        isValidTester(urlVal, "http://www.twitch.tv", true);
        isValidTester(urlVal, "http://www.answers.yahoo.com", true);
        isValidTester(urlVal, "http://www.google.com.ph", true);
        isValidTester(urlVal, "http://www.accuweather.com", true);



    }

    public void testUnitPath() {
        UrlValidator urlVal = new UrlValidator();
        // Test a known good URL and add different paths to test
        isValidTester(urlVal, "http://www.example.com/././foo", true);
        isValidTester(urlVal, "http://www.example.com/test123", true);
        isValidTester(urlVal, "http://www.example.com/!@#$%^&*()", true);
        isValidTester(urlVal, "http://www.example.com/test/a/longish/path/that/keeps/on/going", true);
        isValidTester(urlVal, "http://www.example.com/#?", true);
        isValidTester(urlVal, "http://www.example.com/.../", true);
        isValidTester(urlVal, "http://www.example.com/ / /", false);
        isValidTester(urlVal, "http://www.example.com//", false);
    }

    public void testUnitQuery() {
        UrlValidator urlVal = new UrlValidator();
        // Test a known good URL and add different queries to test
        isValidTester(urlVal, "http://example.com/path/there?name=game", true);
        isValidTester(urlVal, "http://example.com/path/to/page?name=game&type=dominion", true);
        isValidTester(urlVal, "http://www.example.com/field1=value1&field2=value2&field3=value3", true);
        isValidTester(urlVal, "http://example.com/path/ ", false);
    }

    public void testUnitManual() {
        UrlValidator urlVal = new UrlValidator();
// Used online Random URL Generator  www.randomlists.com to create a few
        isValidTester(urlVal, "http://www.example.net/", true);
        isValidTester(urlVal, "https://www.example.com/apparel.htm", true);
        isValidTester(urlVal, "http://baseball.example.com/?balance=animal&brother=bed", true);
        isValidTester(urlVal, "http://bee.example.com/", true);
        isValidTester(urlVal, "https://example.com/bed.html", true);
        isValidTester(urlVal, "https://www.example.com/agreement.html#act", true);
        isValidTester(urlVal, "http://books.example.com/bridge/bed#bear", true);
        isValidTester(urlVal, "https://example.com/ants.php", true);
// Used examples from Final Project Part A “5 Valid URL’s”
        isValidTester(urlVal, " http://go.cc:80/test1?action=view", true);
        isValidTester(urlVal, "ftp://go.au:0/t123?action=edit&mode=up", true);
        isValidTester(urlVal, "http://0.0.0.0/test1/?action=view", true);
        isValidTester(urlVal, "ftp://255.com:80/t123/file", true);
        isValidTester(urlVal, "http://go.com:65535/t123/file/?action=view", true);
// Used examples from Final Project Part A “5 Invalid URL’s”
        isValidTester(urlVal, "3ht://go.au", false);
        isValidTester(urlVal, "http://go.a", false);
        isValidTester(urlVal, "ftp://go.cc:65a", false);
        isValidTester(urlVal, "http://google.com:80/..", false);
        isValidTester(urlVal, "h3t://255.255.255.255:-1/#", false);

    }

    public void testUnitPort() {
        UrlValidator urlVal = new UrlValidator();
        // Test a known good URL and add different ports to test
        isValidTester(urlVal, "http://www.example.com:", true);
        isValidTester(urlVal, "http://www.example.com:0", true);
        isValidTester(urlVal, "http://www.example.com:80", true);
        isValidTester(urlVal, "http://www.example.com:65535", true);
        isValidTester(urlVal, "http://www.example.com:12345", true);
        isValidTester(urlVal, "http://www.example.com:-1", false);
        isValidTester(urlVal, "http://www.example.com:65536", false);
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
