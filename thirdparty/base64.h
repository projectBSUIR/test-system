#ifndef _BASE64_H_
#define _BASE64_H_

#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

void decodeBase64(std::string&& data,  std::vector<unsigned char>& result);

#endif
