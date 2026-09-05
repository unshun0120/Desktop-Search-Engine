#include <string>
#include <vector>
#include <iostream>

#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include <QJsonArray>

using namespace std;

vector<float> getEmbedding(const string& text) {
    /*
     text -> 轉成JSON -> 送給ollama -> 等待ollama -> 取得JSON -> 從JSON裡取出1024個數字 
     */

    // JSON
    // {
    // "model": "qwen3-embedding:0.6b",
    // "input": "你的文字"
    // }
    // 製作要送給 Ollama 的資料
    QJsonObject json;
    json["model"] = "qwen3-embedding:0.6b";
    json["input"] = QString::fromStdString(text);
    
    // 把 JSON 轉成 HTTP 之後能送的文字
    QJsonDocument document(json);
    QByteArray body = document.toJson(QJsonDocument::Compact);
    // cout << body.toStdString() << endl;

    // 2. HTTP POST
    // http://localhost:11434/api/embed
    QNetworkAccessManager manager;
    // 告訴它要送去哪
    QNetworkRequest request(QUrl("http://localhost:11434/api/embed"));
    // 告訴 Ollama, 送過去的是 JSON
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 送出去
    QNetworkReply *reply = manager.post(request, body);

    QEventLoop loop;

    QObject::connect(
        reply,
        &QNetworkReply::finished,
        &loop,
        &QEventLoop::quit
    );

    loop.exec();
    

    // 3. 收到 JSON response, 檢查 Ollama 有沒有出錯
    if(reply->error() != QNetworkReply::NoError) {
        cout << reply->errorString().toStdString() << endl;
        return {};
    }
    // 拿到 Ollama 回傳的 JSON
    /*
     長：
        {
            "model": "qwen3-embedding:0.6b",
            "embeddings": [
                [
                    -0.03780573,
                    0.018257326,
                    -0.007943505,
                    ...
                ]
            ]
        }
     */
    QByteArray response_body = reply->readAll();
    //cout << response_body.toStdString() << endl;

    // 4. 讀 response["embeddings"][0]
    // 把 JSON 拆開
    QJsonDocument response_doc = QJsonDocument::fromJson(response_body);
    QJsonObject response_json = response_doc.object();
    // 取出embedding (二維 array)
    QJsonArray embeddings = response_json["embeddings"].toArray();
    // 把外面第一層 [0] 拿掉
    QJsonArray values = embeddings[0].toArray();

    // 5. 轉成 vector<float>
    vector<float> embedding;
    for(auto const& val: values) {
        embedding.push_back(static_cast<float>(val.toDouble()));
    }

    return embedding;
}
