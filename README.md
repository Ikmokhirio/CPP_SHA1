# C++ implementation of Secure Hash Algorithm 1 (SHA1)
Simple C++ SHA 1 implementation based on [RFC-3174]("https://tools.ietf.org/html/rfc3174") document

# Example

1. With i/o streams

    ```
        HasherSHA h;
        std::cin >> h;
        std::cout << h;
    ```

2. Pass string in constructor

    ```
        std::string testString = "abcde";
        HasherSHA h(testString);
        std::cout << h << std::endl;
    ```
3. Pass string to 'hashString' method
   ```
        std::string testString = "abcde";
        HasherSHA h;
        h.hashString(testString);
        std::cout << h.getHashedString() << std::endl;
   ```
4. Multiple rounds of hashing
   ```
       std::string testString = "abcde";
       HasherSHA h(testString);
   
       for(int i = 0; i < 5; i++) {
           h.hashString(h.getHashedString());
           std::cout << h << std::endl;
       }
   
   ```
   
---
##Additional information
As long as you pass data to the **Hasher** as std::string it should be working fine

However, I have not check its work on something except simple strings

#Warning

You should not use SHA-1 unless you have to!

This algorithm is not secure anymore