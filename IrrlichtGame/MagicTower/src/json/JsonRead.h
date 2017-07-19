#ifndef _JSON_READ_H_
#define _JSON_READ_H_

#include <rapidjson/rapidjson.h>

class JsonRead
{
public:
	JsonRead();
	void loadJsonFile(const char* path);
};

#endif // !_JSON_READ_H_

