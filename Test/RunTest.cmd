@echo on
del dbData.db
del CreateFile.sql
del InsertFile.sql 
jolOpenDBFTest.exe sample.dbf CreateFile.sql InsertFile.sql CATNO
pause
