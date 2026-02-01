#ifndef SOKRAT3_DB_H
#define SOKRAT3_DB_H

#include <QDebug>
#include <QString>
#include <QFile>

#include "CommonDefineType.h"


class Sokrat3_DB
{
public:
    Sokrat3_DB(const QString db_path);

    void GetListModulesName(QStringList& list);

private:
    bool OpenParseSystemFile();

private:

    QString db_path_{};
    QString sokrat_name_{};
    QStringList modules_names_;
    QString module_name_{};
    SModuleDataBase moduleDB_;
};

#endif // SOKRAT3_DB_H
