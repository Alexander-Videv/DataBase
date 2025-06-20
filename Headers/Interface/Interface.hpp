#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "../DataBase/DataBase.hpp"
#include <iostream>

class Interface
{
public:
    static Interface *get();
    static void release();
    void Run(std::istream &is = std::cin);

public:
    Interface(const Interface &other) = delete;
    Interface &operator=(const Interface &other) = delete;

private:
    Interface() : currFileName(""), db(nullptr), running(false) {};
    ~Interface() { exit(); };

private:
    void create(const std::string &name, const std::string &fileName);

    void addTable(const std::string &tableName);
    void removeTable(const std::string &tableName);

    void insert(const std::string &tableName, std::string &values);
    void addColumn(const std::string &tableName, const std::string &columnName, const std::string &columnType);
    void deleteRows(const std::string &tableName, int searchIndex, const std::string &searchValue);

    void showtables() const;
    void describe(const std::string &tableName) const;
    void print(const std::string &tableName, int RPN = 0) const;
    void exportDB(const std::string &tableName, const std::string &fileName) const;
    void select(int columnIndex, const std::string &value, const std::string &tableName) const;

    void modify(const std::string &tableName, int columnIndex, const std::string &newType);
    void update(const std::string &tableName, int searchIndex, const std::string &searchVal,
                int targetIndex, const std::string &targetValue);

    bool open(const std::string &fileName);
    bool save() const;
    bool saveas(const std::string &saveFileName) const;
    bool help(const std::string &command = "") const;
    bool closeDB();
    void exit();

private:
    bool checkDB() const;
    void parseCommand(std::string &command);

    static Interface *instance;

    std::string currFileName;
    DataBase *db;

    bool running;
};

#endif // INTERFACE_HPP