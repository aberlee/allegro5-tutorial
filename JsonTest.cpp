#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <jansson/jansson.h>
#include "JSONObject.h"

int mainJsonTest( int argc, const char *argv[] ) {

	json_error_t jsonError;
	json_t * root = json_loads("{\"key1\": \"value1\"}", 0, &jsonError);
	
	if (!root) {
		
		// report to the user the failure and their locations in the document.
		std::cout  << "Failed to parse configuration\n" << jsonError.text;
		std::cin.get();
		
		json_decref(root);
		return 0;
	}
	
	json_t * key = json_object_get(root, "key1");
	std::cout << json_string_value(key);
	std::cin.get();
	
	json_decref(root);
	
	JSONObject * j = new JSONObject("{\"key2\": \"value2\"}");
	
	j->putDouble("nha", 3.1);
	j->putString("nome", "thiago");
	j->putJSONObject("obj", new JSONObject("{\"chave\": \"valor\"}"));
	
	std::cout << j->getString("key2");
	std::cin.get();
	std::cout << j->getDouble("nha");
	std::cin.get();
	std::cout << j->getString("nome");
	std::cin.get();
	std::cout << j->getJSONObject("obj")->toJSONString();
	std::cin.get();
	std::cout << j->toJSONString();
	std::cin.get();

	return 0;
}


