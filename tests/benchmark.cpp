// test based on JsonBenchmarkCpp
// Copyright 2011 Lijo Antony
// https://github.com/lijoantony/JsonBenchmarkCpp

#include "../glw_json.h"
#include "benchmark/benchmark.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time.h>
#include <sstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>


#include <chrono>  // for high_resolution_clock

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

std::string load_json(const char* path){
	// Perform setup here
	std::ifstream ifs(path, std::ifstream::in);
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
	return buff;
}

static void BM_glw_json_load(benchmark::State& state) {

	std::string buff = load_json("data.json");

	Test test;
	test.web_app.servlet.clear();

	for (auto _ : state) {
	    // This code gets timed
		load_object_from_string(buff.data(), test);
	}

	//std::getchar();
}

static void BM_glw_json_save(benchmark::State& state) {

  	// Perform setup here
	std::string buff = load_json("data.json");

	// prepare the test data
	Test test;
	test.web_app.servlet.clear();
	load_object_from_string(buff.data(), test);

	for (auto _ : state) {
	    // This code gets timed
		stringstream ss;
		ss.clear();
		save_object_to_stream(test, ss);
	}
}

BENCHMARK(BM_glw_json_load);
BENCHMARK(BM_glw_json_save);

using namespace rapidjson;

static void BM_rapid_json_load(benchmark::State& state) {
    // 1. Parse a JSON string into DOM.
    std::string json = load_json("data.json");
    Document d;

	Test test;
	test.web_app.servlet.clear();

	for (auto _ : state) {
	    // This code gets timed
		d.Parse(json.c_str());
		if (d.HasParseError()){
			std::cout << "Failed to parse using rapid json, exiting!" << std::endl;
			exit(1);
		}


		const Value& web_app = d["web-app"];
		const Value& servlet = web_app["servlet"];

		if (web_app.HasMember("servlet-mapping")){
			const Value& servletMapping = web_app["servlet-mapping"];
			if (servletMapping.HasMember("cofaxCDS")) test.web_app.servletMapping.cofaxCDS = servletMapping["cofaxCDS"].GetString();
			if (servletMapping.HasMember("cofaxEmail")) test.web_app.servletMapping.cofaxEmail = servletMapping["cofaxEmail"].GetString();
			if (servletMapping.HasMember("cofaxAdmin")) test.web_app.servletMapping.cofaxAdmin = servletMapping["cofaxAdmin"].GetString();
			if (servletMapping.HasMember("fileServlet")) test.web_app.servletMapping.fileServlet = servletMapping["fileServlet"].GetString();
			if (servletMapping.HasMember("cofaxTools")) test.web_app.servletMapping.cofaxTools = servletMapping["cofaxTools"].GetString();
		}

		if (web_app.HasMember("taglib")) {
			const Value& tagLib = web_app["taglib"];
			if (tagLib.HasMember("taglib-location")) test.web_app.taglib.taglib_location = tagLib["taglib-location"].GetString();
			if (tagLib.HasMember("taglib-uri")) test.web_app.taglib.taglib_uri = tagLib["taglib-uri"].GetString();
		}

		assert(servlet.IsArray());	
		test.web_app.servlet.resize(servlet.Size());
		
		for (SizeType i = 0; i < servlet.Size(); i++){
			test.web_app.servlet[i].servlet_name = servlet[i]["servlet-name"].GetString();
			test.web_app.servlet[i].servlet_class = servlet[i]["servlet-class"].GetString();

			if (!servlet[i].HasMember("init-param"))
				continue;

			const Value& value = servlet[i]["init-param"];

			if (value.HasMember("configGlossary:installationAt")) test.web_app.servlet[i].init_param.configGlossary_installationAt = value["configGlossary:installationAt"].GetString();
			if (value.HasMember("configGlossary:adminEmail")) test.web_app.servlet[i].init_param.configGlossary_adminEmail = value["configGlossary:adminEmail"].GetString();
			if (value.HasMember("configGlossary:poweredBy")) test.web_app.servlet[i].init_param.configGlossary_poweredBy = value["configGlossary:poweredBy"].GetString();
			if (value.HasMember("configGlossary:poweredByIcon")) test.web_app.servlet[i].init_param.configGlossary_poweredByIcon = value["configGlossary:poweredByIcon"].GetString();
			if (value.HasMember("configGlossary:staticPath")) test.web_app.servlet[i].init_param.configGlossary_staticPath = value["configGlossary:staticPath"].GetString();
			if (value.HasMember("templateProcessorClass")) test.web_app.servlet[i].init_param.templateProcessorClass = value["templateProcessorClass"].GetString();
			if (value.HasMember("templateLoaderClass")) test.web_app.servlet[i].init_param.templateLoaderClass = value["templateLoaderClass"].GetString();
			if (value.HasMember("templatePath")) test.web_app.servlet[i].init_param.templatePath = value["templatePath"].GetString();
			if (value.HasMember("templateOverridePath")) test.web_app.servlet[i].init_param.templateOverridePath = value["templateOverridePath"].GetString();
			if (value.HasMember("defaultListTemplate")) test.web_app.servlet[i].init_param.defaultListTemplate = value["defaultListTemplate"].GetString();
			if (value.HasMember("defaultFileTemplate")) test.web_app.servlet[i].init_param.defaultFileTemplate = value["defaultFileTemplate"].GetString();
			if (value.HasMember("useJSP")) test.web_app.servlet[i].init_param.useJSP = value["useJSP"].GetBool();
			if (value.HasMember("jspListTemplate")) test.web_app.servlet[i].init_param.jspListTemplate = value["jspListTemplate"].GetString();
			if (value.HasMember("jspFileTemplate")) test.web_app.servlet[i].init_param.jspFileTemplate = value["jspFileTemplate"].GetString();
			if (value.HasMember("cachePackageTagsTrack")) test.web_app.servlet[i].init_param.cachePackageTagsTrack = value["cachePackageTagsTrack"].GetInt();
			if (value.HasMember("cachePackageTagsStore")) test.web_app.servlet[i].init_param.cachePackageTagsStore = value["cachePackageTagsStore"].GetInt();
			if (value.HasMember("cachePackageTagsRefresh")) test.web_app.servlet[i].init_param.cachePackageTagsRefresh = value["cachePackageTagsRefresh"].GetInt();
			if (value.HasMember("cacheTemplatesTrack")) test.web_app.servlet[i].init_param.cacheTemplatesTrack = value["cacheTemplatesTrack"].GetInt();
			if (value.HasMember("cacheTemplatesStore")) test.web_app.servlet[i].init_param.cacheTemplatesStore = value["cacheTemplatesStore"].GetInt();
			if (value.HasMember("cacheTemplatesRefresh")) test.web_app.servlet[i].init_param.cacheTemplatesRefresh = value["cacheTemplatesRefresh"].GetInt();
			if (value.HasMember("cachePagesTrack")) test.web_app.servlet[i].init_param.cachePagesTrack = value["cachePagesTrack"].GetInt();
			if (value.HasMember("cachePagesStore")) test.web_app.servlet[i].init_param.cachePagesStore = value["cachePagesStore"].GetInt();
			if (value.HasMember("cachePagesRefresh")) test.web_app.servlet[i].init_param.cachePagesRefresh = value["cachePagesRefresh"].GetInt();
			if (value.HasMember("cachePagesDirtyRead")) test.web_app.servlet[i].init_param.cachePagesDirtyRead = value["cachePagesDirtyRead"].GetInt();
			if (value.HasMember("searchEngineListTemplate")) test.web_app.servlet[i].init_param.searchEngineListTemplate = value["searchEngineListTemplate"].GetString();
			if (value.HasMember("searchEngineFileTemplate")) test.web_app.servlet[i].init_param.searchEngineFileTemplate = value["searchEngineFileTemplate"].GetString();
			if (value.HasMember("searchEngineRobotsDb")) test.web_app.servlet[i].init_param.searchEngineRobotsDb = value["searchEngineRobotsDb"].GetString();
			if (value.HasMember("useDataStore")) test.web_app.servlet[i].init_param.useDataStore = value["useDataStore"].GetBool();
			if (value.HasMember("dataStoreClass")) test.web_app.servlet[i].init_param.dataStoreClass = value["dataStoreClass"].GetString();
			if (value.HasMember("redirectionClass")) test.web_app.servlet[i].init_param.redirectionClass = value["redirectionClass"].GetString();
			if (value.HasMember("dataStoreName")) test.web_app.servlet[i].init_param.dataStoreName = value["dataStoreName"].GetString();
			if (value.HasMember("dataStoreDriver")) test.web_app.servlet[i].init_param.dataStoreDriver = value["dataStoreDriver"].GetString();
			if (value.HasMember("dataStoreUrl")) test.web_app.servlet[i].init_param.dataStoreUrl = value["dataStoreUrl"].GetString();
			if (value.HasMember("dataStoreUser")) test.web_app.servlet[i].init_param.dataStoreUser = value["dataStoreUser"].GetString();
			if (value.HasMember("dataStorePassword")) test.web_app.servlet[i].init_param.dataStorePassword = value["dataStorePassword"].GetString();
			if (value.HasMember("dataStoreTestQuery")) test.web_app.servlet[i].init_param.dataStoreTestQuery = value["dataStoreTestQuery"].GetString();
			if (value.HasMember("dataStoreLogFile")) test.web_app.servlet[i].init_param.dataStoreLogFile = value["dataStoreLogFile"].GetString();
			if (value.HasMember("dataStoreInitConns")) test.web_app.servlet[i].init_param.dataStoreInitConns = value["dataStoreInitConns"].GetInt();
			if (value.HasMember("dataStoreMaxConns")) test.web_app.servlet[i].init_param.dataStoreMaxConns = value["dataStoreMaxConns"].GetInt();
			if (value.HasMember("dataStoreConnUsageLimit")) test.web_app.servlet[i].init_param.dataStoreConnUsageLimit = value["dataStoreConnUsageLimit"].GetInt();
			if (value.HasMember("dataStoreLogLevel")) test.web_app.servlet[i].init_param.dataStoreLogLevel = value["dataStoreLogLevel"].GetString();
			if (value.HasMember("maxUrlLength")) test.web_app.servlet[i].init_param.maxUrlLength = value["maxUrlLength"].GetInt();

			if (value.HasMember("mailHost")) test.web_app.servlet[i].init_param.mailHost = value["mailHost"].GetString();
			if (value.HasMember("mailHostOverride")) test.web_app.servlet[i].init_param.mailHostOverride = value["mailHostOverride"].GetString();
			if (value.HasMember("log")) test.web_app.servlet[i].init_param.log = value["log"].GetInt();
			if (value.HasMember("logLocation")) test.web_app.servlet[i].init_param.logLocation = value["logLocation"].GetString();
			if (value.HasMember("logMaxSize")) test.web_app.servlet[i].init_param.logMaxSize = value["logMaxSize"].GetString();
			if (value.HasMember("dataLog")) test.web_app.servlet[i].init_param.dataLog = value["dataLog"].GetInt();
			if (value.HasMember("dataLogLocation")) test.web_app.servlet[i].init_param.dataLogLocation = value["dataLogLocation"].GetString();
			if (value.HasMember("dataLogMaxSize")) test.web_app.servlet[i].init_param.dataLogMaxSize = value["dataLogMaxSize"].GetString();
			if (value.HasMember("removePageCache")) test.web_app.servlet[i].init_param.removePageCache = value["removePageCache"].GetString();
			if (value.HasMember("removeTemplateCache")) test.web_app.servlet[i].init_param.removeTemplateCache = value["removeTemplateCache"].GetString();
			if (value.HasMember("fileTransferFolder")) test.web_app.servlet[i].init_param.fileTransferFolder = value["fileTransferFolder"].GetString();
			if (value.HasMember("lookInContext")) test.web_app.servlet[i].init_param.lookInContext = value["lookInContext"].GetInt();
			if (value.HasMember("adminGroupID")) test.web_app.servlet[i].init_param.adminGroupID = value["adminGroupID"].GetInt();
			if (value.HasMember("betaServer")) test.web_app.servlet[i].init_param.betaServer = value["betaServer"].GetBool();
		}

	}

    // 2. Modify it by DOM.
    // Value& s = d["stars"].GetString();
    // s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    // StringBuffer buffer;
    // Writer<StringBuffer> writer(buffer);
    // d.Accept(writer);

}

BENCHMARK(BM_rapid_json_load);

BENCHMARK_MAIN();

