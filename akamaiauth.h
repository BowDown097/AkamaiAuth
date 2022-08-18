#ifndef AKAMAIAUTH_H
#define AKAMAIAUTH_H

#include "md5.h"
#define MD5_DIGEST_LENGTH 16

// Generates an Akamai GDA token. This is different from an Akamai HMAC token.
// pathname: Target URL pathname for the token (ie. for https://google.com/search, the pathname would be "/search")
// exp: Expiration time for the token as a Unix timestamp
// salt: A salt to significantly alter the token result, highly recommended to use for security
// extract: Additional data to be added to initially tokenized string
char* generateGDAToken(const char* pathname, long exp, unsigned char* salt, const char* extract);

#endif // AKAMAIAUTH_H