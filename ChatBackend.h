#ifndef CHATBACKEND_H
#define CHATBACKEND_H

#include <QObject>
#include <QString>
#include <QStringList>

class ChatBackend : public QObject {
    Q_OBJECT

public:
    explicit ChatBackend(QObject *parent = nullptr);

signals:
    void newMessageReceived(const QString &message);
    void userListUpdated(const QStringList &users);

};

#endif // CHATBACKEND_H
