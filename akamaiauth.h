#include "md5.h"
#define MD5_DIGEST_LENGTH 16

// Generates an Akamai GDA token. This is different from an Akamai HMAC token.
// pathname: Target URL pathname for the token (ie. for https://google.com/search, the pathname would be "/search")
// exp: Expiration time for the token as a Unix timestamp
// salt: A salt to significantly alter the token result, highly recommended to use for security
// extract: Additional data to be added to initially tokenized string
char* generateGDAToken(const char* pathname, long exp, unsigned char* salt, const char* extract)
{
    MD5Context ctx;
    // create primary data string (pathname + extract + salt)
    size_t saltlen = strlen(salt);
    unsigned char data[strlen(pathname) + strlen(extract) + saltlen + 1];
    snprintf(data, sizeof(data), "%s%s%s", pathname, extract, salt);
    size_t datalen = strlen(data);

    // convert exp to array of bytes, only of int size
    unsigned char expBytes[sizeof(int)];
    for (int i = 0; i < sizeof(int); i++)
        expBytes[i] = (unsigned char)((exp >> (8*i)) & 0xFF);

    // create a combination of expBytes and data
    size_t buffer1sz = sizeof(int) + datalen;
    unsigned char buffer1[buffer1sz];
    memcpy(buffer1, expBytes, sizeof(int));
    memcpy(&buffer1[sizeof(int)], data, datalen);

    // create MD5 digest of what we just did
    md5Init(&ctx);
    md5Update(&ctx, buffer1, buffer1sz);
    md5Finalize(&ctx);
    unsigned char digest1[MD5_DIGEST_LENGTH];
    memcpy(digest1, ctx.digest, MD5_DIGEST_LENGTH);

    // create a combination of salt and MD5 digest
    size_t binaryStringsz = saltlen + MD5_DIGEST_LENGTH;
    unsigned char binaryString[binaryStringsz];
    memcpy(binaryString, salt, binaryStringsz);
    memcpy(&binaryString[saltlen], digest1, MD5_DIGEST_LENGTH);

    // create MD5 digest of what we just did again (finally we're done with this)
    md5Init(&ctx);
    md5Update(&ctx, binaryString, binaryStringsz);
    md5Finalize(&ctx);
    unsigned char binaryToken[MD5_DIGEST_LENGTH];
    memcpy(binaryToken, ctx.digest, MD5_DIGEST_LENGTH);

    // convert final result to a hexadecimal string and return it
    char hexout[MD5_DIGEST_LENGTH * 2];
    for (int i = 0, j = 0; i < MD5_DIGEST_LENGTH; ++i, j += 2)
        sprintf(hexout + j, "%02x", binaryToken[i] & 0xff);
    return strdup(hexout);
}