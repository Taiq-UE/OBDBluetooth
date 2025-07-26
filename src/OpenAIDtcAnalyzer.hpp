#ifndef OPENAI_DTC_ANALYZER_HPP
#define OPENAI_DTC_ANALYZER_HPP

#include <QObject>
#include <QString>

class OpenAIDtcAnalyzer : public QObject {
Q_OBJECT
public:
    explicit OpenAIDtcAnalyzer(QObject* parent = nullptr);

    Q_INVOKABLE QString analyzeDtcCodes(const QString& dtcCodes);

private:
    QString apiKey;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    QString sendRequestToOpenAI(const QString& payload);
    QString extractMessageContent(const QString& json);
    QString loadApiKey(const QString& apiKeyFilePath);
};

#endif // OPENAI_DTC_ANALYZER_HPP
