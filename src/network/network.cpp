#include <string>
#include <vector>

#include <openssl/crypto.h>
#define CURL_STATICLIB
#include <curl/curl.h>

#include <asset.hpp>
#include <network.hpp>
#include <settings.hpp>
#include <system.hpp>

namespace MetaModule::network
{

static const std::vector<std::string> methodNames = {
	"GET",
	"POST",
	"PUT",
	"DELETE",
};

static CURL *createCurl() {
	CURL *curl = curl_easy_init();
	assert(curl);

	// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	std::string userAgent = rack::APP_NAME + " " + rack::APP_EDITION_NAME + "/" + rack::APP_VERSION;
	curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
	// Timeout to wait on initial HTTP connection.
	// This is lower than the typical HTTP timeout of 60 seconds to avoid DAWs from aborting plugin scans.
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);

	// If curl can't resolve a DNS entry, it sends a signal to interrupt the process.
	// However, since we use curl on non-main thread, this crashes the application.
	// So tell curl not to signal.
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

	// Load root certificates
	std::string caPath = rack::asset::system("cacert.pem");
	curl_easy_setopt(curl, CURLOPT_CAINFO, caPath.c_str());

	// Don't verify HTTPS certificates if verifyHttpsCerts is false
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, rack::settings::verifyHttpsCerts);

	return curl;
}

static size_t writeStringCallback(char *ptr, size_t size, size_t nmemb, void *userdata) {
	std::string *str = (std::string *)userdata;
	size_t len = size * nmemb;
	str->append(ptr, len);
	return len;
}

static std::string getCookieString(const rack::network::CookieMap &cookies) {
	std::string s;
	for (const auto &pair : cookies) {
		s += rack::network::encodeUrl(pair.first);
		s += "=";
		s += rack::network::encodeUrl(pair.second);
		s += ";";
	}
	return s;
}

std::string requestRaw(rack::network::Method method,
					   const std::string &url,
					   const std::string &reqStr,
					   const rack::network::CookieMap &cookies) {
	using namespace rack::network;

	std::string urlS = url;
	CURL *curl = createCurl();

	curl_easy_setopt(curl, CURLOPT_URL, urlS.c_str());

	// Set HTTP method
	if (method == METHOD_GET) {
		// This is CURL's default
	} else if (method == METHOD_POST) {
		curl_easy_setopt(curl, CURLOPT_POST, true);
	} else if (method == METHOD_PUT) {
		curl_easy_setopt(curl, CURLOPT_PUT, true);
	} else if (method == METHOD_DELETE) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
	}

	// Set headers
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	// Cookies
	if (!cookies.empty()) {
		curl_easy_setopt(curl, CURLOPT_COOKIE, getCookieString(cookies).c_str());
	}

	// Body callbacks
	if (reqStr.c_str())
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, reqStr.c_str());

	std::string resText;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeStringCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resText);

	// Perform request
	INFO("Requesting Raw %s %s", methodNames[method].c_str(), urlS.c_str());
	CURLcode res = curl_easy_perform(curl);

	// Cleanup
	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);

	if (res != CURLE_OK) {
		WARN("Could not request %s: %s", urlS.c_str(), curl_easy_strerror(res));
		return "";
	}

	return resText;
}

} // namespace MetaModule::network