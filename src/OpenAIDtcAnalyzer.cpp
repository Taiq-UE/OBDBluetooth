#include "OpenAIDtcAnalyzer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

OpenAIDtcAnalyzer::OpenAIDtcAnalyzer() {
    apiKey = loadApiKey("openaiapikey.txt");
    if (apiKey.empty()) {
        std::cerr << "Błąd: Nie udało się załadować klucza API!" << std::endl;
    }
}

std::string OpenAIDtcAnalyzer::loadApiKey(const std::string& apiKeyFilePath) {
    std::ifstream apiKeyFile(apiKeyFilePath);
    std::string apiKey;
    if (apiKeyFile.is_open()) {
        std::getline(apiKeyFile, apiKey);
        apiKeyFile.close();
    } else {
        std::cerr << "Nie udało się otworzyć pliku z kluczem API!" << std::endl;
    }
    return apiKey;
}

size_t OpenAIDtcAnalyzer::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string OpenAIDtcAnalyzer::sendRequestToOpenAI(const std::string& payload) {
    CURL* curl;
    CURLcode res;
    std::string response_string;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();

    return response_string;
}

std::string OpenAIDtcAnalyzer::extractMessageContent(const std::string& json) {
    std::string key = "\"content\": \"";
    size_t start = json.find(key);
    if (start == std::string::npos) return "Błąd parsowania JSON";

    start += key.length();
    size_t end = json.find("\"", start);
    if (end == std::string::npos) return "Błąd parsowania JSON";

    return json.substr(start, end - start);
}

std::string OpenAIDtcAnalyzer::analyzeDtcCodes(const std::string& dtcCodes) {
    std::string json_payload = R"({
        "model": "gpt-4",
        "messages": [
            {"role": "system", "content": "Jesteś ekspertem diagnostyki samochodowej."},
            {"role": "user", "content": "Podaj możliwe przyczyny i sposoby naprawy błędów OBD2: )" + dtcCodes + R"("}
        ],
        "temperature": 0.7
    })";

    std::string response = sendRequestToOpenAI(json_payload);
    return extractMessageContent(response);
}
