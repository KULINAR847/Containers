#include "pyrun.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

PyRun::PyRun(QString execFile)
{
//    this->execFile = execFile.toStdWString();

//    QStringList pythonPath;
//    pythonPath << QDir::toNativeSeparators(QFileInfo(QFileInfo(execFile).absoluteDir(), "libpy34.zip").canonicalFilePath());

//    this->pythonPath = pythonPath.join(":").toStdWString();

//    // Path of our executable
//    Py_SetProgramName((wchar_t*) this->execFile.c_str());

//    // Set module search path
//    Py_SetPath(this->pythonPath.c_str());

//    Py_NoSiteFlag = 1;

    // Initialize the Python interpreter
    Py_InitializeEx(0);

    qDebug() << "Python interpreter version:" << QString(Py_GetVersion());
    qDebug() << "Python standard library path:" << QString::fromWCharArray(Py_GetPath());

//    QFile f("://res/rcssmin.py.codeobj");

//    if(f.open(QIODevice::ReadOnly))
//    {
//        QByteArray codeObj = f.readAll();
//        f.close();
//        importModule(codeObj, "rcssmin");
//    }
}

PyRun::~PyRun()
{
    Py_Finalize();
}

QString PyRun::runPythonExpression(const QString &expression)
{
    QString Result = "";

    qDebug() << "start func";
    PyObject *d = PyDict_New();;

//    PyObject *l_dict;
//    PyObject *m = PyImport_ImportModule("__main__");
//    if (m) d = PyModule_GetDict(m);

    //PyObject *output = PyRun_String(exp.toLatin1().data(), Py_single_input, m_dict, m_dict);
    PyObject *output = PyRun_String(QString(expression).toLatin1().data(), Py_eval_input, d, d);
    qDebug() << output;

    PyObject *rep = PyObject_Repr(output);
    if (!PyUnicode_Check(rep)) {
        qDebug() << "repr is not unicode (this should not happen!)\n";
        Result = "repr is not unicode (this should not happen!)\n";
    }
    else
    {
//        const char *str_rep = PyUnicode_AsUTF8(rep);
//        //puts(str_rep);
        Result = QString(PyUnicode_AsUTF8(rep));
        qDebug() << "Result = " << Result;
    }

    qDebug() << "Py_XDECREF";
    Py_XDECREF(d);
    Py_XDECREF(output);

    return Result;
}

// Сделаем функцию которая возвращает вычисленное значение в строке где имеется return и нет отступов
QString PyRun::eval2(const QString &codeStr)
{
    QString Result = "";
    QStringList commands = codeStr.split("\n");

    // Вначале выполним все подготовительные команды
    foreach(QString command, commands)
    {
        if(command.indexOf("return") == 0)
        {
            Result = command.remove(0,7);
            break;
        }

        PyRun_SimpleString(command.toLatin1().data());
    }
    qDebug() << Result;

    // А теперь разберёмся с последним return
    PyObject *code_obj = Py_CompileString(Result.toLatin1().data(), "code_in_block", Py_eval_input);
    //PyObject* main_module = PyImport_AddModule("__main__");
    //PyObject* global_dict = PyModule_GetDict(main_module);
    PyObject *global_dict = PyDict_New();
    PyObject *local_dict = PyDict_New();

    if(code_obj) {

            // If the compilation was successful, the resulting code
            // object is evaluated.
            PyObject* output = PyEval_EvalCode(code_obj, global_dict, local_dict);

            //mat_eval_compiled_code(code_obj, Py_eval_input);
            //Py_DECREF(code_obj);

            PyObject *rep = PyObject_Repr(output);
            if (!PyUnicode_Check(rep)) {
                qDebug() << "repr is not unicode (this should not happen!)\n";
                Result = "repr is not unicode (this should not happen!)\n";
            }
            else
            {
                Result = QString(PyUnicode_AsUTF8(rep));
                qDebug() << "Result = " << Result;
            }


            Py_XDECREF(output);
            Py_XDECREF(rep);

    }


    //PyObject* output = PyEval_EvalCode(code, global_dict, local_dict);



    qDebug() << "Py_XDECREF";
    Py_XDECREF(global_dict);
    Py_XDECREF(local_dict);
    Py_XDECREF(code_obj);
    //Py_XDECREF(main_module);




//    PyObject* result = PyObject_Str(obj);
//    PyObject_Print(result, stdout, 0);

    return Result;
}



QString PyRun::eval(const QString &codeStr)
{
    QString Result = "";

    PyObject *moduleMainString = PyUnicode_FromString("__main__");
    PyObject *moduleMain = PyImport_Import(moduleMainString);

    PyRun_SimpleString(
        "def eval(a, b):\n"\
        "   import os\n"\
        "   return os.__doc__\n"\
    );

    PyRun_SimpleString(codeStr.toLatin1().data());

    PyObject *func = PyObject_GetAttrString(moduleMain, "eval");
    PyObject *args = PyTuple_Pack(2, PyFloat_FromDouble(3.0), PyFloat_FromDouble(4.0));

    PyObject *output = PyObject_CallObject(func, args);


    PyObject *rep = PyObject_Repr(output);
    if (!PyUnicode_Check(rep)) {
        qDebug() << "repr is not unicode (this should not happen!)\n";
        Result = "repr is not unicode (this should not happen!)\n";
    }
    else
    {
        Result = QString(PyUnicode_AsUTF8(rep));
        qDebug() << "Result = " << Result;
    }

    Py_XDECREF(moduleMainString);
    Py_XDECREF(moduleMain);
    Py_XDECREF(func);
    Py_XDECREF(args);
    Py_XDECREF(output);
    Py_XDECREF(rep);

    qDebug() << "all done " << Result;

    return Result;
}
