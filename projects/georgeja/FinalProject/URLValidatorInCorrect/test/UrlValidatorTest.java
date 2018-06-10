
import org.junit.Assert;
import java.util.regex.Pattern;
import org.junit.Test;
import junit.framework.TestCase;

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
   
   @Test
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }

   @Test
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 

   @Test
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
