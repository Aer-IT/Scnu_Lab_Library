#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <vector>
#include <string>
#include <map>
#include "Book.h"
#include "Reader.h"

class LibrarySystem {
private:
    std::vector<Book> books;
    std::vector<Reader> readers;
    std::string bookFile;
    std::string readerFile;
    int nextBookId;
    int nextReaderId;
    
    // 辅助函数
    void loadBooks();
    void saveBooks();
    void loadReaders();
    void saveReaders();
    
    // 查找函数
    int findBookIndex(int id) const;
    int findReaderIndex(int id) const;

public:
    LibrarySystem(const std::string& bookFile = "book.dat", const std::string& readerFile = "reader.dat");
    ~LibrarySystem();
    
    // 图书管理
    bool addBook(const std::string& name, const std::string& author, const std::string& publisher);
    bool removeBook(int id);
    Book* findBook(int id);
    void displayAllBooks() const;
    std::vector<Book*> searchBooks(const std::string& keyword) const;
    
    // 读者管理
    bool addReader(const std::string& name, const std::string& contact);
    bool removeReader(int id);
    Reader* findReader(int id);
    void displayAllReaders() const;
    std::vector<Reader*> searchReaders(const std::string& keyword) const;
    
    // 借还书操作
    bool borrowBook(int readerId, int bookId);
    bool returnBook(int readerId, int bookId);
    
    // 菜单函数
    void run();
    void showMainMenu() const;
    void bookManagementMenu();
    void readerManagementMenu();
    void borrowReturnMenu();
};

#endif // LIBRARY_SYSTEM_H 