#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QObject>
#include "src/Utilities/Utilities.hpp"

class Playground : public QObject
{
    Q_OBJECT
public:
    explicit Playground(QObject *parent = nullptr);

signals:

public slots:
    void callMe();

private:
    std::unordered_set<Token *> tokens;
    std::unordered_set<Account *> accounts;
};

#endif // PLAYGROUND_H
