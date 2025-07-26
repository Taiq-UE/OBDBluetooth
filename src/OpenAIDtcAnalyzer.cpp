#include "OpenAIDtcAnalyzer.hpp"

#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>

OpenAIDtcAnalyzer::OpenAIDtcAnalyzer(QObject* parent) : QObject(parent) {
    apiKey = loadApiKey("../openaiapikey.txt");
    if (apiKey.isEmpty()) {
        std::cerr << "Błąd: Nie udało się załadować klucza API!" << std::endl;
    }
}

QString OpenAIDtcAnalyzer::loadApiKey(const QString& apiKeyFilePath) {
    std::ifstream file(apiKeyFilePath.toStdString());
    std::string key;
    if (file.is_open()) {
        std::getline(file, key);
        file.close();
    } else {
        std::cerr << "Nie udało się otworzyć pliku z kluczem API!" << std::endl;
    }
    return QString::fromStdString(key);
}

size_t OpenAIDtcAnalyzer::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

QString OpenAIDtcAnalyzer::sendRequestToOpenAI(const QString& payload) {
    CURL* curl;
    CURLcode res;
    std::string response_string;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string auth = "Authorization: Bearer " + apiKey.toStdString();
        headers = curl_slist_append(headers, auth.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_CAINFO, "../cacert.pem");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        std::string payloadStd = payload.toStdString();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStd.c_str());
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

    return QString::fromStdString(response_string);
}

QString OpenAIDtcAnalyzer::extractMessageContent(const QString& json) {
    QString key = "\"content\": \"";
    int start = json.indexOf(key);
    if (start == -1) return "Błąd parsowania JSON";

    start += key.length();
    int end = json.indexOf("\"", start);
    if (end == -1) return "Błąd parsowania JSON";

    QString content = json.mid(start, end - start);
    return content.replace("\\n", "\n");
}

QString OpenAIDtcAnalyzer::analyzeDtcCodes(const QString& dtcCodes) {
    QString prompt = QString("Podaj możliwe przyczyny i sposoby naprawy błędów OBD2: %1").arg(dtcCodes);

    QString json_payload = QString(R"({
        "model": "gpt-4o",
        "messages": [
            {"role": "system", "content": "Jesteś ekspertem diagnostyki samochodowej. Nie używaj żadnych potwierdzeń i powitań, tylko od razu przejdź do analizy."},
            {"role": "user", "content": "%1"}
        ],
        "temperature": 0.7
    })").arg(prompt);

    QString response = sendRequestToOpenAI(json_payload);
    return extractMessageContent(response);
}

bool OpenAIDtcAnalyzer::saveAnalysisToDesktop(const QString& content, const QString& filename) {
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    if (desktopPath.isEmpty()) {
        qWarning("Nie udało się znaleźć ścieżki do pulpitu.");
        return false;
    }

    QDir dir(desktopPath);
    QString filePath = dir.filePath(filename);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Nie udało się zapisać pliku na pulpicie.");
        return false;
    }

    QTextStream out(&file);
    out << content;
    file.close();
    return true;
}

