#ifndef PYRUN_H
#define PYRUN_H


#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

#include <marshal.h>

#include <QString>

class PyRun
{
public:
    PyRun(QString);
    ~PyRun();
   // QString cssmin(QString);

    QString runPythonExpression(const QString &expression);
    QString eval(const QString &codeStr);
    QString eval2(const QString &codeStr);
private:
    std::wstring execFile;
    std::wstring pythonPath;
//    bool hasError();
//    PyObject* importModule(const QByteArray&, const QString&);
//    PyObject* callFunction(PyObject*, QString, PyObject*);
//    QString ObjectToString(PyObject*);
//public slots:

};

#endif // PYRUN_H
