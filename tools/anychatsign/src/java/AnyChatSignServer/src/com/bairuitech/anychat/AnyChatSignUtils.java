package com.bairuitech.anychat;


public class AnyChatSignUtils {

    private static final String PRIVATE_KEY =  
            "-----BEGIN RSA PRIVATE KEY-----\n" +
            "MIICWwIBAAKBgQDc/sgvXXKZrr8lX9pZgZMO9y8jRq/s3YYlJ/BayEvj9EIVhiXG\r"+
            "A3rZwhh0+L4UdkPE5o/t6Bh1oY6nlGvkFuENgFwkRzrn2qP7wl3MgJD8WW6OM4JA\r"+
            "1fd2Wwt/TUENQeoN30bluy4ZQPby+bGl3ic5JW0hXhEWHAjk7e0ruSxRbwIDAQAB\r"+
            "AoGALbcSyCGHlFz+s4eJjpxsRFtDyANWXyRQHJ2PbegjMsuTZAp1A+oyXpt1HbVa\r"+
            "9LamPDQJsAgkDylVbjsYun01Hoh0i+lV5rOwWpwZC1jo4ohS1MAVPaRofCD2BlCJ\r"+
            "ML3i+qIznqJu7VpC2YjULTVphUf5guUetr+iP1lkNrKhRNkCQQDxwn7BO9qw5V53\r"+
            "/5CG9z+PAPYR2Be+cD/cuGP8ooovkZ+tJ76UXSkwXwveDFf8civdkUB9v0P/EKyS\r"+
            "UMp8u4hNAkEA6gMtlFA1+ju6pTjMnxa8cmgPYXinY70OxgpOfyz7Erp2Xmq+4J3Y\r"+
            "AQeerY/aJ3K4itKgyyPXsi9cCPxv6UxeqwJAQHAS0PZfJ986+skHgLHOIxOigscS\r"+
            "LRRGMVKEdAXuxxcNdF2vkmPyYo4y35ByszrLLldU1S9xtD6BgM4/6lch0QJASVEn\r"+
            "laEv2C+ggaVzDqD798g8kWhQ4YHZQBj4kQXRwANllJ1TImKxy1jM0UoRqmxZ/zyQ\r"+
            "njSjnrMR3crhcTG5MwJANPjy150Mf+J3SHz6s1aRddggzLOMzDtObUs60ZQRi6PS\r"+
            "88K3sAbX5C1in9B0Dg5TOPanEEzsonYVIs1UZ6DqAg==\r"+
            "\n-----END RSA PRIVATE KEY-----\n"; 
    
    private static final String PUBLIC_KEY =   
            "-----BEGIN PUBLIC KEY-----\n"+
            "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDc/sgvXXKZrr8lX9pZgZMO9y8j\r"+
            "Rq/s3YYlJ/BayEvj9EIVhiXGA3rZwhh0+L4UdkPE5o/t6Bh1oY6nlGvkFuENgFwk\r"+
            "Rzrn2qP7wl3MgJD8WW6OM4JA1fd2Wwt/TUENQeoN30bluy4ZQPby+bGl3ic5JW0h\r"+
            "XhEWHAjk7e0ruSxRbwIDAQAB\r"+
            "\n-----END PUBLIC KEY-----\n";
    
    private static final String APP_ID = "CED78A73-134B-4403-9992-83B79702C4A0";
    
    public static SignResult getRsaSign(int userId) {
        SignResult result = new SignResult();
        AnyChatOutParam signResult =  new AnyChatOutParam();
        
        int errorcode = AnyChatSign.RsaSign(userId, APP_ID, PRIVATE_KEY, signResult);
        if(errorcode == 0)
        {
            int timestamp = signResult.GetIntValue();
            String sigStr = signResult.GetStrValue();
            result.setErrorcode(errorcode);
            result.setTimestamp(timestamp);
            result.setSigStr(sigStr);            
        }     

        return result;
    }
    
    public static int verifySign(int userId, String sigstr, int timestamp) {
        return AnyChatSign.RsaVerify(userId, APP_ID, sigstr, timestamp, PUBLIC_KEY);
    }
    
    public static void main(String[] args) {
        int userId = 2;
        SignResult signResult = AnyChatSignUtils.getRsaSign(userId);
        
        if (AnyChatSignUtils.verifySign(userId, signResult.getSigStr(), signResult.getTimestamp())==0) {
            System.out.println("signature verify pass.");
        }
    }
    
}
