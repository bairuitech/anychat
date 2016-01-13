using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AnyChatSignDemo
{
    public class Program
    {
        public static void Main(string[] args)
        {
            String privatekey =
                    "-----BEGIN RSA PRIVATE KEY-----\n" +
                    "MIICWwIBAAKBgQDc/sgvXXKZrr8lX9pZgZMO9y8jRq/s3YYlJ/BayEvj9EIVhiXG\r" +
                    "A3rZwhh0+L4UdkPE5o/t6Bh1oY6nlGvkFuENgFwkRzrn2qP7wl3MgJD8WW6OM4JA\r" +
                    "1fd2Wwt/TUENQeoN30bluy4ZQPby+bGl3ic5JW0hXhEWHAjk7e0ruSxRbwIDAQAB\r" +
                    "AoGALbcSyCGHlFz+s4eJjpxsRFtDyANWXyRQHJ2PbegjMsuTZAp1A+oyXpt1HbVa\r" +
                    "9LamPDQJsAgkDylVbjsYun01Hoh0i+lV5rOwWpwZC1jo4ohS1MAVPaRofCD2BlCJ\r" +
                    "ML3i+qIznqJu7VpC2YjULTVphUf5guUetr+iP1lkNrKhRNkCQQDxwn7BO9qw5V53\r" +
                    "/5CG9z+PAPYR2Be+cD/cuGP8ooovkZ+tJ76UXSkwXwveDFf8civdkUB9v0P/EKyS\r" +
                    "UMp8u4hNAkEA6gMtlFA1+ju6pTjMnxa8cmgPYXinY70OxgpOfyz7Erp2Xmq+4J3Y\r" +
                    "AQeerY/aJ3K4itKgyyPXsi9cCPxv6UxeqwJAQHAS0PZfJ986+skHgLHOIxOigscS\r" +
                    "LRRGMVKEdAXuxxcNdF2vkmPyYo4y35ByszrLLldU1S9xtD6BgM4/6lch0QJASVEn\r" +
                    "laEv2C+ggaVzDqD798g8kWhQ4YHZQBj4kQXRwANllJ1TImKxy1jM0UoRqmxZ/zyQ\r" +
                    "njSjnrMR3crhcTG5MwJANPjy150Mf+J3SHz6s1aRddggzLOMzDtObUs60ZQRi6PS\r" +
                    "88K3sAbX5C1in9B0Dg5TOPanEEzsonYVIs1UZ6DqAg==\r" +
                    "\n-----END RSA PRIVATE KEY-----\n";

            String publickey =
                    "-----BEGIN PUBLIC KEY-----\n" +
                    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDc/sgvXXKZrr8lX9pZgZMO9y8j\r" +
                    "Rq/s3YYlJ/BayEvj9EIVhiXGA3rZwhh0+L4UdkPE5o/t6Bh1oY6nlGvkFuENgFwk\r" +
                    "Rzrn2qP7wl3MgJD8WW6OM4JA1fd2Wwt/TUENQeoN30bluy4ZQPby+bGl3ic5JW0h\r" +
                    "XhEWHAjk7e0ruSxRbwIDAQAB\r" +
                    "\n-----END PUBLIC KEY-----\n";

            int userid = -1;

            //应用Id
            String appid = "CED78A73-134B-4403-9992-83B79702C4A0";
            StringBuilder sbPrivateKey = new StringBuilder();
            sbPrivateKey.Append(privatekey);

            StringBuilder sbAppId = new StringBuilder();
            sbAppId.Append(appid);

            int signStrSize = 1024;
            StringBuilder outSignStr = new StringBuilder(signStrSize);

            try
            {                
                int timeStamp = 0;
                int errorcode = AnyChatSign.AnyChatRsaSign(userid, sbAppId, sbPrivateKey, outSignStr, signStrSize, ref timeStamp);
                if (errorcode == 0)
                {
                    string signStr = outSignStr.ToString();

                    System.Console.WriteLine("1. rsa sign result, timestamp: " + timeStamp + " signStr: " + signStr);

                    StringBuilder sbPublicKey = new StringBuilder();
                    sbPublicKey.Append(publickey);

                    errorcode = AnyChatSign.AnyChatRsaVerify(userid, sbAppId, outSignStr, timeStamp, sbPublicKey);
                    System.Console.WriteLine("2. rsa verify result, errorcode: " + errorcode);

                }
                else
                {
                    System.Console.WriteLine("rsa sign result, errorcode: " + errorcode);
                }
            }
            catch (Exception e)
            {
                System.Console.WriteLine("AnyChatSignDemo has exception, message: " + e.Message);
            }

            System.Console.WriteLine("=============按任意键退出！=============");
            Console.ReadKey();

        }
    }
}
