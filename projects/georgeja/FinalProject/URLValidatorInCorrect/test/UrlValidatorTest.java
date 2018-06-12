
import org.junit.Assert;
import java.util.regex.Pattern;
import org.junit.Test;
import junit.framework.TestCase;
import java.util.Random;

import java.io.Console;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   @Test
   public void testManualTest()
   {
//You can use this function to implement your manual testing
      Console console = System.console();
      String[] schemes = {"http","https"};
      UrlValidator urlTest = new UrlValidator(schemes, UrlValidator.ALLOW_ALL_SCHEMES);

      // The following tests should pass
      String URL = "http://www.google.com";
      boolean result = urlTest.isValid(URL);
      Assert.assertTrue(result);
      if (!result)
      {
         console.printf("Test failed with URL: %s", URL);
      }

      URL = "http://www.google.com/";
      result = urlTest.isValid(URL);
      Assert.assertTrue(result);
      if (!result)
      {
         console.printf("Test failed with URL: %s", URL);
      }

      URL = "https://www.google.com";
      result = urlTest.isValid(URL);
      Assert.assertTrue(result);
      if (!result)
      {
         console.printf("Test failed with URL: %s", URL);
      }

      URL = "https://www.google.com/";
      result = urlTest.isValid(URL);
      Assert.assertTrue(result);
      if (!result)
      {
         console.printf("Test failed with URL: %s", URL);
      }

      // This should be a nonsense string
      result = urlTest.isValid("lkajdsfhgvkljdafshnbvkbjl");
      Assert.assertFalse(result);
       if (!result)
       {
           console.printf("Test failed with URL: %s", URL);
       }
   }

   /***********************************************************
    * Partition A
    * 	This partition should test URLS that should be valid.
    * 		ex. https://www.google.com
    *
    * 	Note some of these URLS may not actually go anywhere,
    * 		but are still valid.
    *
    **********************************************************/
   @Test
   public void testPartitionA() {
      System.out.println("Valid - Partition");
      UrlValidator urlValidator = new UrlValidator();
      String urls[] = new String[5];
      urls[0] = "https://www.google.com";
      urls[1] = "https://stackoverflow.com";
      urls[2] = "https://oregonstate.instructure.com/courses/00000"; // 00000 is a random id
      urls[3] = "https://www.google.com/search?q=google+search";
      urls[4] = "https://localhost:8080/index.html";

      for(int i = 0; i < 5; i++) {
         if (urlValidator.isValid(urls[i])) {
            System.out.printf("\tvalid\t%s\n", urls[i]);
         } else {
            System.out.printf("\tinvalid\t%s\n", urls[i]);
         }
      }
   }

   /***********************************************************
    * Partition B
    * 	This partition should test URLS that should be invalid.
    **********************************************************/
   @Test
   public void testPartitionB() {
      System.out.println("inalid - Partition");
      UrlValidator urlValidator = new UrlValidator();
      String urls[] = new String[5];
      urls[0] = "invalid.url.4";
      urls[1] = "http://.com";
      urls[2] = "notAscheme:\\index.html";
      urls[3] = "ftp:google.com";
      urls[4] = "https://google.com.edu.org";

      for(int i = 0; i < 5; i++) {
         if (urlValidator.isValid(urls[i])) {
            System.out.printf("\tvalid\t%s\n", urls[i]);
         } else {
            System.out.printf("\tinvalid\t%s\n", urls[i]);
         }
      }
   }

   /***********************************************************
    * Partition C
    * 	This partition should test URLS that are 'edge' cases
    **********************************************************/
   @Test
   public void testPartitionC() {
      System.out.println("Edge - Partition");
      UrlValidator urlValidator = new UrlValidator();
      String urls[] = new String[3];
      urls[0] = "https://www.google.com/(a)"; //Valid, but should give 404
      urls[1] = "www.subdomain.validDomain.org"; //valid, should give 404
      urls[2] = "file:///C:/file.txt"; //Valid, if file.txt exists in C:/

      for(int i = 0; i < 3; i++) {
         if (urlValidator.isValid(urls[i])) {
            System.out.printf("\tvalid\t%s\n", urls[i]);
         } else {
            System.out.printf("\tinvalid\t%s\n", urls[i]);
         }
      }

   }

   @Test
   public void testIsValid() {
      UrlBuilder bldr = new UrlBuilder();
      UrlValidator urlValidator = new UrlValidator();
      System.out.println("Programming Based");
      for(int i = 0 ; i < 10; i ++) {
         boolean res = bldr.getNextType();
         String url = "";
         if(res) {
            url = bldr.buildValid();
         }else {
            url = bldr.buildInvalid();
         }

         if (urlValidator.isValid(url) == res) {
            System.out.printf("\tPASS\t'%s' was %s\n", url, (res)?("Valid"):("Invalid"));
         } else {
            System.out.printf("\tFAILED\t'%s' should have been %s\n", url, (res)?("Valid"):("Invalid"));
         }
      }
   }

   public class UrlBuilder{
      Random rng = new Random();
      String schemesValid[] = {"",
              "http://",
              "ftp://",
              "https://",
              "file://"};

      String hostsValid[] = {	"google.com",
              "www.google.com",
              "stackoverflow.com",
              "255.255.255.255",
              "0.0.0.0"};

      String pathsValid[] = {	"/index.html",
              "/someDirectory/",
              "",
              "/dir//file.txt",
              "/aRandomFile.txt",
              "/chained/path/that/is/kinda/long/index.html"};

      String querysValid[] = {	"?q=google+search",
              "?data=one+two+three",
              ""};

      String schemesInvalid[] = {"htpp://",
              "http:",
              "://",
              "invalidScheme://"};

      String hostsInvalid[] = {"-1.256.-1.256",
              "255.255.255.256",
              "notGood.abc",
              ".com",
              ".org"};

      String pathsInvalid[] = {"/../../..",
              "/..//index.html"};

      public String buildValid() {
         return schemesValid[rng.nextInt(schemesValid.length)]
                 + hostsValid[rng.nextInt(hostsValid.length)]
                 + pathsValid[rng.nextInt(pathsValid.length)]
                 + querysValid[rng.nextInt(querysValid.length)];
      }
      public boolean getNextType() {
         return rng.nextBoolean();
      }
      public String buildInvalid() {
         String tempStrs[] = {
                 schemesValid[rng.nextInt(schemesValid.length)],
                 hostsValid[rng.nextInt(hostsValid.length)],
                 pathsValid[rng.nextInt(pathsValid.length)]
         };
         switch(rng.nextInt(3)) {
            case 0:
               tempStrs[0] = schemesInvalid[rng.nextInt(schemesInvalid.length)];
               break;
            case 1:
               tempStrs[1] = hostsInvalid[rng.nextInt(hostsInvalid.length)];
               break;
            case 2:
               tempStrs[2] = pathsInvalid[rng.nextInt(pathsInvalid.length)];
               break;
         }
         return tempStrs[0] + tempStrs[1] + tempStrs[2];
      }
   }

}
