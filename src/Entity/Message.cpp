#include "Message.hpp"

Message::Message(QString sender, QString time, QString text)
    : sender(std::move(sender)), time(std::move(time)), text(std::move(text)) {}