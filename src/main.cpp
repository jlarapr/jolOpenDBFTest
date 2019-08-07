#include <iostream>
#include <chrono>
#include <ctime>

#include <dbffile.h>
#include "dblite.h"

using namespace std;

int main(int argc, const char **argv) {

    cout << "DBF TO SQL FILE TEST" << endl;

    //argv[1] ="sample.dbf"; //input dbf        "C:\\BASE DE DATO MMM 837P\\MMM837P2.DBF";
    //argv[2] ="Create.sql"; //OutPutCreateFile "C:\\BASE DE DATO MMM 837P\\Create.sql";
    //argv[3] ="Insert.sql"; //OutPutInsertFile "C:\\BASE DE DATO MMM 837P\\Insert.sql";
    //argv[4] = "CATNO";      //KeyColumnName          "V0DOCUMENT";

    //argc = argc + 4;

    if(argc < 5)
    {
        cout << "Usage: jolOpenDBFTest <input.dbf> <OutPutCreateFile.sql> <OutPutInsertFile.sql> <KeyColumnName>" << endl;
        return -1;
    }

    try
    {
        cout << argv[1] << endl;

        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();

        std::time_t start_time = std::chrono::system_clock::to_time_t(start);
        std::cout << "\nProceso start en " << std::ctime(&start_time) <<endl;

        time_t instanteInicial, instanteFinal;
        instanteInicial = time(nullptr);

        DbfFile_c file(argv[1]);


        file.tblName("tblData");

        if(argc == 5)
            file.DumpAllAndCreateSqlFile(argv[2],argv[3],argv[4]);
        else
        {
            cout << "Usage: jolOpenDBFTest <input.dbf> <OutPutCreateFile.sql> <OutPutInsertFile.sql> <KeyColumnName>" << endl;
            return  -1;
            //file.DumpFields(argv[2], argv+3, static_cast<size_t>(argc-3));
        }

        end = std::chrono::system_clock::now();
        instanteFinal = time(nullptr);

        // Restamos el tiempo final menos el inicial para saber
        // cuanto dura el proceso.
        // Si este valor es muy alto habrá que mejorar los
        // algoritmos internos de las
        // clases a fin de obtener un buen performance.
        std::chrono::duration<std::chrono::system_clock::rep,std::chrono::system_clock::period> elapsed_seconds = end - start;

        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        //std::chrono::duration<double> segundos = end-start;

        std::cout << "\nProceso finalizado en "
                  << std::ctime(&end_time)
                  << "Duracion: " << elapsed_seconds.count()
                  << "s\n";

        cout << "Segundos empleados: " << instanteFinal - instanteInicial << endl;
        //cout << "Segundos empleados: " << segundos.count() << endl;

        start = std::chrono::system_clock::now();
        instanteInicial = time(nullptr);

        start_time = std::chrono::system_clock::to_time_t(start);
        std::cout << "\nProceso Insert start en " << std::ctime(&start_time) <<endl;

        ifstream ifs(argv[2]);
        string create;
        getline(ifs,create,static_cast<char>(ifs.eof()));

        ifs.close();
        ifstream ifsInsert(argv[3]);
        std::string insert;
        getline(ifsInsert,insert,static_cast<char>(ifsInsert.eof()));

        DBLite sqldb("dbData.db");
        sqldb.createTable(create);
        sqldb.insertData(insert.c_str());

        //while (ifsInsert) {
        //    getline(ifsInsert,insert);
        //    sqldb.insertData(insert.c_str());
        //}

        ifsInsert.close();

        sqldb.closeDB();

        end = std::chrono::system_clock::now();
        instanteFinal = time(nullptr);

        //segundos = end - start;

        end_time = std::chrono::system_clock::to_time_t(end);
        cout << "Segundos empleados: " << instanteFinal - instanteInicial << endl;
        //cout << "Segundos empleados: " << segundos.count() << endl;
        std::cout << "\nProceso finalizado en " << std::ctime(&end_time) << endl;

    }
    catch(const exception &e)
    {
        cerr << e.what();
        return -1;
    }

    return 0;
}
