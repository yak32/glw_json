// test based on JsonBenchmarkCpp
// Copyright 2011 Lijo Antony
// https://github.com/lijoantony/JsonBenchmarkCpp

#include "../glw_json.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time.h>
#include <sstream>

#include "Windows.h" // QueryPerformanceCounter

using namespace std;
using namespace json;

#define ITERATION 100000

struct InitParam {
	string configGlossary_installationAt;
	string configGlossary_adminEmail;
	string configGlossary_poweredBy;
	string configGlossary_poweredByIcon;
	string configGlossary_staticPath;
	string templateProcessorClass;
	string templateLoaderClass;
	string templatePath;
	string templateOverridePath;
	string defaultListTemplate;
	string defaultFileTemplate;
	bool   useJSP;
	string jspListTemplate;
	string jspFileTemplate;
	int	cachePackageTagsTrack;
	int	cachePackageTagsStore;
	int	cachePackageTagsRefresh;
	int	cacheTemplatesTrack;
	int	cacheTemplatesStore;
	int	cacheTemplatesRefresh;
	int	cachePagesTrack;
	int	cachePagesStore;
	int	cachePagesRefresh;
	int	cachePagesDirtyRead;
	string searchEngineListTemplate;
	string searchEngineFileTemplate;
	string searchEngineRobotsDb;
	bool   useDataStore;
	string dataStoreClass;
	string redirectionClass;
	string dataStoreName;
	string dataStoreDriver;
	string dataStoreUrl;
	string dataStoreUser;
	string dataStorePassword;
	string dataStoreTestQuery;
	string dataStoreLogFile;
	int	dataStoreInitConns;
	int	dataStoreMaxConns;
	int	dataStoreConnUsageLimit;
	string dataStoreLogLevel;
	int	maxUrlLength;
	string mailHost;
	string mailHostOverride;
	int	log;
	string logLocation;
	string logMaxSize;
	int	dataLog;
	string dataLogLocation;
	string dataLogMaxSize;
	string removePageCache;
	string removeTemplateCache;
	string fileTransferFolder;
	int	lookInContext;
	int	adminGroupID;
	bool   betaServer;
};

template <typename T> bool serialize(T& t, InitParam& v) {
	bool b = true;

	b &= SERIALIZE(adminGroupID);
	b &= SERIALIZE(betaServer);
	b &= SERIALIZE(cachePackageTagsRefresh);
	b &= SERIALIZE(cachePackageTagsStore);
	b &= SERIALIZE(cachePackageTagsTrack);
	b &= SERIALIZE(cachePagesDirtyRead);
	b &= SERIALIZE(cachePagesRefresh);
	b &= SERIALIZE(cachePagesStore);
	b &= SERIALIZE(cachePagesTrack);
	b &= SERIALIZE(cacheTemplatesRefresh);
	b &= SERIALIZE(cacheTemplatesStore);
	b &= SERIALIZE(cacheTemplatesTrack);
	b &= t.process("configGlossary:adminEmail", v.configGlossary_adminEmail);
	b &= t.process("configGlossary:installationAt", v.configGlossary_installationAt);
	b &= t.process("configGlossary:poweredBy", v.configGlossary_poweredBy);
	b &= t.process("configGlossary:poweredByIcon", v.configGlossary_poweredByIcon);
	b &= t.process("configGlossary:staticPath", v.configGlossary_staticPath);
	b &= SERIALIZE(dataLog);
	b &= SERIALIZE(dataLogLocation);
	b &= SERIALIZE(dataLogMaxSize);
	b &= SERIALIZE(dataStoreClass);
	b &= SERIALIZE(dataStoreConnUsageLimit);
	b &= SERIALIZE(dataStoreDriver);
	b &= SERIALIZE(dataStoreInitConns);
	b &= SERIALIZE(dataStoreLogFile);
	b &= SERIALIZE(dataStoreLogLevel);
	b &= SERIALIZE(dataStoreMaxConns);
	b &= SERIALIZE(dataStoreName);
	b &= SERIALIZE(dataStorePassword);
	b &= SERIALIZE(dataStoreTestQuery);
	b &= SERIALIZE(dataStoreUrl);
	b &= SERIALIZE(dataStoreUser);
	b &= SERIALIZE(defaultFileTemplate);
	b &= SERIALIZE(defaultListTemplate);
	b &= SERIALIZE(fileTransferFolder);
	b &= SERIALIZE(jspFileTemplate);
	b &= SERIALIZE(jspListTemplate);
	b &= SERIALIZE(log);
	b &= SERIALIZE(logLocation);
	b &= SERIALIZE(logMaxSize);
	b &= SERIALIZE(lookInContext);
	b &= SERIALIZE(mailHost);
	b &= SERIALIZE(mailHostOverride);
	b &= SERIALIZE(maxUrlLength);
	b &= SERIALIZE(redirectionClass);
	b &= SERIALIZE(removePageCache);
	b &= SERIALIZE(removeTemplateCache);
	b &= SERIALIZE(searchEngineFileTemplate);
	b &= SERIALIZE(searchEngineListTemplate);
	b &= SERIALIZE(searchEngineRobotsDb);
	b &= SERIALIZE(templateLoaderClass);
	b &= SERIALIZE(templateOverridePath);
	b &= SERIALIZE(templatePath);
	b &= SERIALIZE(templateProcessorClass);
	b &= SERIALIZE(useDataStore);
	b &= SERIALIZE(useJSP);
	return b;
}

struct Servlet {
	string	servlet_name;
	string	servlet_class;
	InitParam init_param;
};

template <typename T> bool serialize(T& t, Servlet& v) {
	bool b = true;
	b &= t.process("init-param", v.init_param);
	b &= t.process("servlet-class", v.servlet_class);
	b &= t.process("servlet-name", v.servlet_name);
	return b;
}

struct ServletMapping {
	string cofaxCDS;
	string cofaxEmail;
	string cofaxAdmin;
	string fileServlet;
	string cofaxTools;
};

template <typename T> bool serialize(T& t, ServletMapping& v) {
	bool b = true;
	b &= SERIALIZE(cofaxAdmin);
	b &= SERIALIZE(cofaxCDS);
	b &= SERIALIZE(cofaxEmail);
	b &= SERIALIZE(cofaxTools);
	b &= SERIALIZE(fileServlet);
	return b;
}

struct TagLib {
	string taglib_uri;
	string taglib_location;
};

template <typename T> bool serialize(T& t, TagLib& v) {
	bool b = true;
	b &= t.process("taglib-location", v.taglib_location);
	b &= t.process("taglib-uri", v.taglib_uri);
	return b;
}

struct WebApp {
	vector<Servlet> servlet;
	ServletMapping  servletMapping;
	TagLib			taglib;
};

template <typename T> bool serialize(T& t, WebApp& v) {
	bool b = true;
	b &= SERIALIZE(servlet);
	b &= t.process("servlet-mapping", v.servletMapping);
	b &= SERIALIZE(taglib);
	return b;
}

struct Test {
	WebApp  web_app;
};

template <typename T> bool serialize(T& t, Test& v) {
	bool b = true;
	b &= t.process("web-app", v.web_app);
	return b;
}

bool glw_json_benchmark(const std::string& jsonString) {

	std::cout << std::setw(25) << "glw_json";

	// Parsing the string
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	if (!freq.QuadPart)
		return false;

	LARGE_INTEGER t;
	::QueryPerformanceCounter(&t);
	float t1 = (float)t.QuadPart / (float)freq.QuadPart;

	Test test;
	for (int i = 0; i < ITERATION; i++){
		test.web_app.servlet.clear();
		load_object_from_string(jsonString.data(), test);
	}

	::QueryPerformanceCounter(&t);
	float t2 = (float)t.QuadPart / (float)freq.QuadPart;

	printf("time to load, %d iterations: %f sec\n", ITERATION, t2-t1);

	::QueryPerformanceCounter(&t);
	float t3 = (float)t.QuadPart / (float)freq.QuadPart;

	// Serialize to string
	stringstream ss;
	for (int i = 0; i < ITERATION; i++) {
		ss.clear();
		save_object_to_stream(test, ss);
	}

	::QueryPerformanceCounter(&t);
	float t4 = (float)t.QuadPart / (float)freq.QuadPart;

	printf("time to save, %d iterations: %f sec\n", ITERATION, t4-t3);
	std::cout << std::endl;
	return true;
}

int main() {
	std::ifstream ifs("C:\\projects\\glw_json\\tests\\data.json", std::ifstream::in);
	std::string   buff = "";

	if (ifs.is_open()) {
		while (!ifs.eof()) {
			std::string temp;
			ifs >> temp;
			buff += temp;
		}
	}

	if (buff.empty()) {
		std::cout << "No data available for test, exiting!" << std::endl;
		exit(1);
	}
	glw_json_benchmark(buff);
	std::getchar();
	return 0;
}
