#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <qjsonmarshalerlib_global.h>
#include <qjsonmarshaler.h>
#include "employee.h"
const QString USER_JSON_FILE_NAME = "user_data.json";

void writeEmployeeToJsonFile(Employee * e);
Employee * readEmployeeFromJsonFile();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Employee employee;

    writeEmployeeToJsonFile(&employee);

    Employee * employee2 = readEmployeeFromJsonFile();

    return a.exec();
}

void writeEmployeeToJsonFile(Employee * e)
{
    QJsonObject jsonUser =  QJsonMarshaler::Marshal(e);
    QJsonDocument document(jsonUser);
    QFile file(USER_JSON_FILE_NAME);
    if(file.exists())
        file.remove();
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(QString(document.toJson()).toStdString().c_str());
        file.close();
    }
}

Employee * readEmployeeFromJsonFile()
{
    QFile file (USER_JSON_FILE_NAME);
    if(file.open(QIODevice::ReadOnly))
    {
        QJsonObject jsonObj = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
        return QJsonMarshaler::Unmarshal<Employee>(jsonObj);
    }
    throw -1;
}

