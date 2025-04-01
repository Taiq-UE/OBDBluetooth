#ifndef OPENAI_DTC_ANALYZER_HPP
#define OPENAI_DTC_ANALYZER_HPP

#include <string>
#include <curl/curl.h>

class OpenAIDtcAnalyzer {
public:
    explicit OpenAIDtcAnalyzer();
    std::string analyzeDtcCodes(const std::string& dtcCodes);

private:
    std::string apiKey;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::string sendRequestToOpenAI(const std::string& payload);
    std::string extractMessageContent(const std::string& json);
    std::string loadApiKey(const std::string& apiKeyFilePath);
};

#endif // OPENAI_DTC_ANALYZER_HPP
