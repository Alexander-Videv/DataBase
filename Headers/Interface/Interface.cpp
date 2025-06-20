#include "Interface.hpp"

#include <fstream>
#include <sstream>

#include "../utils/func.cpp"

Interface *Interface::instance = nullptr;

Interface *Interface::get()
{
    if (!instance)
        instance = new Interface;

    return instance;
}

void Interface::release()
{
    delete instance;
    instance = nullptr;
}

void Interface::Run(std::istream &is)
{
    std::string line;
    running = true;

    while (running)
    {
        std::getline(is, line);
        parseCommand(line);
    }
    exit();
}

void Interface::create(const std::string &name)
{
    if (db)
        closeDB();

    this->db = new DataBase(name);
}

void Interface::addTable(const std::string &tableName)
{
    if (!checkDB())
        return;
    db->createTable(tableName);
}

void Interface::removeTable(const std::string &tableName)
{
    if (!checkDB())
        return;
    db->removeTable(tableName);
}

void Interface::showtables() const
{
    if (!checkDB())
        return;
    db->showTables();
}

void Interface::describe(const std::string &tableName) const
{
    if (!checkDB())
        return;

    db->describe(tableName);
}

void Interface::print(const std::string &tableName, int RPN) const
{
    if (!checkDB())
        return;
    db->printTable(tableName, std::cout, RPN);
}

void Interface::exportDB(const std::string &tableName, const std::string &fileName) const
{
    if (!checkDB())
        return;
    std::ofstream outputFile(fileName);

    db->printTable(tableName, outputFile);
    outputFile.close();
}

void Interface::select(int columnIndex, const std::string &value, const std::string &tableName) const
{
    if (!checkDB())
        return;
    db->select(columnIndex, value, tableName);
}

void Interface::modify(const std::string &tableName, int columnIndex, const std::string &newType)
{
    if (!checkDB())
        return;
    db->modify(tableName, columnIndex, newType);
}

void Interface::addColumn(const std::string &tableName, const std::string &columnName, const std::string &columnType)
{
    if (!checkDB())
        return;
    db->addColumn(tableName, columnName, columnType);
}

void Interface::update(const std::string &tableName, int searchIndex, const std::string &searchVal,
                       int targetIndex, const std::string &targetValue)
{
    if (!checkDB())
        return;
    db->update(tableName, searchIndex, searchVal, targetIndex, targetValue);
}

void Interface::deleteRows(const std::string &tableName, int searchIndex, const std::string &searchValue)
{
    if (!checkDB())
        return;
    db->deleteRowsFrom(tableName, searchIndex, searchValue);
}

void Interface::insert(const std::string &tableName, std::string &values)
{
    if (!checkDB())
        return;
    db->insertTo(tableName, values);
}

bool Interface::open(const std::string &fileName)
{
    std::ifstream input(fileName);

    if (!input)
    {
        std::cout << "Unable to open file!\n";
        return false;
    }

    DataBase *buff = new DataBase(fileName);

    if ((input >> *buff).fail() || input.bad())
    {
        std::cout << "Unable to read database from file : " << fileName << "\n";
        input.close();
        delete buff;
        return false;
    }

    if (db)
        closeDB();

    this->db = buff;

    currFileName = fileName;
    input.close();

    return true;
}

bool Interface::closeDB()
{
    if (!checkDB())
        return false;

    std::string input;
    std::cout << "Do you want to save changes made (y/n):\n";
    std::cin >> input;
    input = toLowerStr(input);

    if (input == "y")
    {
        if (!save())
        {
            std::cout << "Error, changes couldnt be saved\n";
            return false;
        }
    }
    else
    {
        std::cin.ignore(input.size());
    }

    delete db;
    db = nullptr;

    return true;
}

bool Interface::save() const
{
    return saveas(currFileName);
}

bool Interface::saveas(const std::string &saveFileName) const
{
    if (!checkDB())
        return false;
    std::ofstream saveFile(saveFileName);

    if (!saveFile)
        return false;

    if (!(saveFile << (*db)))
    {
        saveFile.close();
        return false;
    }

    saveFile.close();

    return true;
}

bool Interface::help(const std::string &command) const
{
    if (command.empty())
    {
        std::cout << "Commands : \n";
    }
    else
    {
    }

    return true;
}

void Interface::exit()
{
    delete db;
    db = nullptr;
}

bool Interface::checkDB() const
{
    if (!db)
    {
        std::cout << "Need to open a database first!\n";
        return false;
    }

    return true;
}

void Interface::parseCommand(std::string &line)
{
    std::string command;
    command = getNextToken(line);

    if (command == "open")
    {
        std::string fileName = line;
        open(fileName);
    }
    else if (command == "create")
    {
        std::string name = line;
        create(name);
    }
    else if (command == "help")
    {
        std::string additional = line;
        help(additional);
    }
    else if (command == "save")
    {
        save();
    }
    else if (command == "saveas")
    {
        std::string fileName = line;
        saveas(fileName);
    }
    else if (command == "close")
    {
        closeDB();
    }
    else if (command == "showtables")
    {
        showtables();
    }
    else if (command == "addtable")
    {
        std::string tableName = line;
        addTable(tableName);
    }
    else if (command == "removetable")
    {
        std::string tableName = line;
        removeTable(tableName);
    }
    else if (command == "describe")
    {
        std::string tableName = line;
        describe(tableName);
    }
    else if (command == "print")
    {
        std::string tableName = getNextToken(line);
        int RPN = getIndex(line) + 1;

        if (RPN < 0)
        {
            std::cout << "Cant print negative pages!\n";
            return;
        }

        print(tableName, RPN);
    }
    else if (command == "export")
    {
        std::string tableName = getNextToken(line);
        std::string fileName = getNextToken(line);

        exportDB(tableName, fileName);
    }
    else if (command == "select")
    {
        int colIndex = getIndex(line);

        std::string value = getValue(line);

        std::string tableName = getNextToken(line);

        select(colIndex, value, tableName);
    }
    else if (command == "modify")
    {
        std::string tableName = getNextToken(line);
        int columnIndex = getIndex(line);
        std::string newType = getNextToken(line);

        modify(tableName, columnIndex, newType);
    }
    else if (command == "addcolumn")
    {
        std::string tableName = getNextToken(line);
        std::string columnName = getNextToken(line);
        std::string columnType = getNextToken(line);

        addColumn(tableName, columnName, columnType);
    }
    else if (command == "update")
    {
        std::string tableName = getNextToken(line);

        int searchIndex = getIndex(line);

        std::string searchValue = getValue(line);

        int targetIndex = getIndex(line);

        std::string targetValue = getValue(line);

        update(tableName, searchIndex, searchValue, targetIndex, targetValue);
    }
    else if (command == "delete")
    {
        std::string tableName = getNextToken(line);

        int columnIndex = getIndex(line);

        std::string value = getValue(line);

        deleteRows(tableName, columnIndex, value);
    }
    else if (command == "insert")
    {
        std::string tableName = getNextToken(line);
        std::string values = line;
        insert(tableName, values);
    }
    else if (command == "exit")
    {
        running = false;
        return;
    }
    else
    {
        std::cout << "Invalid command.\n";
    }
}
