#include "LibrarySystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

LibrarySystem::LibrarySystem(const std::string& bookFile, const std::string& readerFile)
    : bookFile(bookFile), readerFile(readerFile), nextBookId(1), nextReaderId(1) {
    loadBooks();
    loadReaders();
}

LibrarySystem::~LibrarySystem() {
    saveBooks();
    saveReaders();
}


void LibrarySystem::loadBooks() {
    std::ifstream file(bookFile);
    if (!file) {
        std::cout << "图书文件不存在，将创建新文件。" << std::endl;
        return;
    }
    
    books.clear();
    nextBookId = 1;
    
    while (!file.eof()) {
        Book book;
        file >> book;
        
        if (file.fail()) {
            break;
        }
        
        books.push_back(book);
        nextBookId = std::max(nextBookId, book.getId() + 1);
    }
    
    file.close();
}

void LibrarySystem::saveBooks() {
    std::ofstream file(bookFile);
    if (!file) {
        std::cout << "无法保存图书信息！" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < books.size(); ++i) {
        file << books[i];
        if (i < books.size() - 1) {
            file << "\n";
        }
    }
    
    file.close();
}

void LibrarySystem::loadReaders() {
    std::ifstream file(readerFile);
    if (!file) {
        std::cout << "读者文件不存在，将创建新文件。" << std::endl;
        return;
    }
    
    readers.clear();
    nextReaderId = 1;
    
    while (!file.eof()) {
        Reader reader;
        file >> reader;
        
        if (file.fail()) {
            break;
        }
        
        readers.push_back(reader);
        nextReaderId = std::max(nextReaderId, reader.getId() + 1);
    }
    
    file.close();
}

void LibrarySystem::saveReaders() {
    std::ofstream file(readerFile);
    if (!file) {
        std::cout << "无法保存读者信息！" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < readers.size(); ++i) {
        file << readers[i];
        if (i < readers.size() - 1) {
            file << "\n";
        }
    }
    
    file.close();
}

int LibrarySystem::findBookIndex(int id) const {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

int LibrarySystem::findReaderIndex(int id) const {
    for (size_t i = 0; i < readers.size(); ++i) {
        if (readers[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

bool LibrarySystem::addBook(const std::string& name, const std::string& author, const std::string& publisher) {
    Book book(nextBookId++, name, author, publisher);
    books.push_back(book);
    saveBooks();
    return true;
}

bool LibrarySystem::removeBook(int id) {
    int index = findBookIndex(id);
    if (index == -1) {
        return false;
    }
    
    // 检查是否有读者借了这本书
    for (const Reader& reader : readers) {
        const std::vector<int>& borrowedBooks = reader.getBorrowedBooks();
        if (std::find(borrowedBooks.begin(), borrowedBooks.end(), id) != borrowedBooks.end()) {
            std::cout << "该书已被借出，无法删除！" << std::endl;
            return false;
        }
    }
    
    books.erase(books.begin() + index);
    saveBooks();
    return true;
}

Book* LibrarySystem::findBook(int id) {
    int index = findBookIndex(id);
    if (index == -1) {
        return nullptr;
    }
    return &books[index];
}

void LibrarySystem::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "图书馆中没有图书！" << std::endl;
        return;
    }
    
    std::cout << "图书馆中共有 " << books.size() << " 本图书：" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    for (const Book& book : books) {
        book.display();
        std::cout << "=======================================" << std::endl;
    }
}

std::vector<Book*> LibrarySystem::searchBooks(const std::string& keyword) const {
    std::vector<Book*> results;
    std::string lowerKeyword = keyword;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
    
    for (const Book& book : books) {
        std::string name = book.getName();
        std::string author = book.getAuthor();
        std::string publisher = book.getPublisher();
        
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::transform(author.begin(), author.end(), author.begin(), ::tolower);
        std::transform(publisher.begin(), publisher.end(), publisher.begin(), ::tolower);
        
        if (name.find(lowerKeyword) != std::string::npos ||
            author.find(lowerKeyword) != std::string::npos ||
            publisher.find(lowerKeyword) != std::string::npos) {
            // 使用const_cast来处理const vector中的非const元素
            results.push_back(const_cast<Book*>(&book));
        }
    }
    
    return results;
}

bool LibrarySystem::addReader(const std::string& name, const std::string& contact) {
    Reader reader(nextReaderId++, name, contact);
    readers.push_back(reader);
    saveReaders();
    return true;
}

bool LibrarySystem::removeReader(int id) {
    int index = findReaderIndex(id);
    if (index == -1) {
        return false;
    }
    
    // 检查读者是否有未归还的图书
    if (!readers[index].getBorrowedBooks().empty()) {
        std::cout << "该读者有未归还的图书，无法删除！" << std::endl;
        return false;
    }
    
    readers.erase(readers.begin() + index);
    saveReaders();
    return true;
}

Reader* LibrarySystem::findReader(int id) {
    int index = findReaderIndex(id);
    if (index == -1) {
        return nullptr;
    }
    return &readers[index];
}

void LibrarySystem::displayAllReaders() const {
    if (readers.empty()) {
        std::cout << "图书馆中没有读者！" << std::endl;
        return;
    }
    
    std::cout << "图书馆中共有 " << readers.size() << " 位读者：" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    for (const Reader& reader : readers) {
        reader.display();
        std::cout << "=======================================" << std::endl;
    }
}

std::vector<Reader*> LibrarySystem::searchReaders(const std::string& keyword) const {
    std::vector<Reader*> results;
    std::string lowerKeyword = keyword;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);
    
    for (const Reader& reader : readers) {
        std::string name = reader.getName();
        std::string contact = reader.getContact();
        
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::transform(contact.begin(), contact.end(), contact.begin(), ::tolower);
        
        if (name.find(lowerKeyword) != std::string::npos ||
            contact.find(lowerKeyword) != std::string::npos) {
            // 使用const_cast来处理const vector中的非const元素
            results.push_back(const_cast<Reader*>(&reader));
        }
    }
    
    return results;
}

bool LibrarySystem::borrowBook(int readerId, int bookId) {
    Reader* reader = findReader(readerId);
    if (!reader) {
        std::cout << "读者ID不存在！" << std::endl;
        return false;
    }
    
    Book* book = findBook(bookId);
    if (!book) {
        std::cout << "图书ID不存在！" << std::endl;
        return false;
    }
    
    if (book->isBorrowed()) {
        std::cout << "该图书已被借出！" << std::endl;
        return false;
    }
    
    if (reader->borrowBook(bookId)) {
        book->setBorrowed(true);
        saveBooks();
        saveReaders();
        std::cout << "借书成功！" << std::endl;
        return true;
    }
    
    std::cout << "借书失败，可能是已经借了该书！" << std::endl;
    return false;
}

bool LibrarySystem::returnBook(int readerId, int bookId) {
    Reader* reader = findReader(readerId);
    if (!reader) {
        std::cout << "读者ID不存在！" << std::endl;
        return false;
    }
    
    Book* book = findBook(bookId);
    if (!book) {
        std::cout << "图书ID不存在！" << std::endl;
        return false;
    }
    
    if (!book->isBorrowed()) {
        std::cout << "该图书未被借出！" << std::endl;
        return false;
    }
    
    if (reader->returnBook(bookId)) {
        book->setBorrowed(false);
        saveBooks();
        saveReaders();
        std::cout << "还书成功！" << std::endl;
        return true;
    }
    
    std::cout << "还书失败，可能是没有借这本书！" << std::endl;
    return false;
}

void LibrarySystem::run() {
    while (true) {
        showMainMenu();
        
        int choice;
        std::cout << "请输入您的选择: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入错误，请重新输入！" << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                borrowReturnMenu();
                break;
            case 2:
                bookManagementMenu();
                break;
            case 3:
                readerManagementMenu();
                break;
            case 0:
                std::cout << "感谢使用图书管理系统，再见！" << std::endl;
                return;
            default:
                std::cout << "选择错误，请重新输入！" << std::endl;
                break;
        }
    }
}

void LibrarySystem::showMainMenu() const {
    std::cout << "\n==================图书管理系统==================" << std::endl;
    std::cout << "1. 借/还书" << std::endl;
    std::cout << "2. 图书管理" << std::endl;
    std::cout << "3. 读者维护" << std::endl;
    std::cout << "0. 退出系统" << std::endl;
    std::cout << "================================================" << std::endl;
}

void LibrarySystem::bookManagementMenu() {
    while (true) {
        std::cout << "\n==================图书管理==================" << std::endl;
        std::cout << "1. 添加图书" << std::endl;
        std::cout << "2. 删除图书" << std::endl;
        std::cout << "3. 查找图书" << std::endl;
        std::cout << "4. 显示所有图书" << std::endl;
        std::cout << "0. 返回主菜单" << std::endl;
        std::cout << "============================================" << std::endl;
        
        int choice;
        std::cout << "请输入您的选择: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入错误，请重新输入！" << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1: {
                std::string name, author, publisher;
                std::cin.ignore();
                
                std::cout << "请输入图书名称: ";
                std::getline(std::cin, name);
                
                std::cout << "请输入作者: ";
                std::getline(std::cin, author);
                
                std::cout << "请输入出版社: ";
                std::getline(std::cin, publisher);
                
                if (addBook(name, author, publisher)) {
                    std::cout << "图书添加成功！" << std::endl;
                } else {
                    std::cout << "图书添加失败！" << std::endl;
                }
                break;
            }
            case 2: {
                int id;
                std::cout << "请输入要删除的图书ID: ";
                std::cin >> id;
                
                if (removeBook(id)) {
                    std::cout << "图书删除成功！" << std::endl;
                } else {
                    std::cout << "图书删除失败！" << std::endl;
                }
                break;
            }
            case 3: {
                std::string keyword;
                std::cin.ignore();
                
                std::cout << "请输入关键字: ";
                std::getline(std::cin, keyword);
                
                std::vector<Book*> results = searchBooks(keyword);
                if (results.empty()) {
                    std::cout << "未找到匹配的图书！" << std::endl;
                } else {
                    std::cout << "找到 " << results.size() << " 本匹配的图书：" << std::endl;
                    std::cout << "=======================================" << std::endl;
                    
                    for (Book* book : results) {
                        book->display();
                        std::cout << "=======================================" << std::endl;
                    }
                }
                break;
            }
            case 4:
                displayAllBooks();
                break;
            case 0:
                return;
            default:
                std::cout << "选择错误，请重新输入！" << std::endl;
                break;
        }
    }
}

void LibrarySystem::readerManagementMenu() {
    while (true) {
        std::cout << "\n==================读者维护==================" << std::endl;
        std::cout << "1. 添加读者" << std::endl;
        std::cout << "2. 删除读者" << std::endl;
        std::cout << "3. 查找读者" << std::endl;
        std::cout << "4. 显示所有读者" << std::endl;
        std::cout << "0. 返回主菜单" << std::endl;
        std::cout << "============================================" << std::endl;
        
        int choice;
        std::cout << "请输入您的选择: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入错误，请重新输入！" << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1: {
                std::string name, contact;
                std::cin.ignore();
                
                std::cout << "请输入读者姓名: ";
                std::getline(std::cin, name);
                
                std::cout << "请输入联系方式: ";
                std::getline(std::cin, contact);
                
                if (addReader(name, contact)) {
                    std::cout << "读者添加成功！" << std::endl;
                } else {
                    std::cout << "读者添加失败！" << std::endl;
                }
                break;
            }
            case 2: {
                int id;
                std::cout << "请输入要删除的读者ID: ";
                std::cin >> id;
                
                if (removeReader(id)) {
                    std::cout << "读者删除成功！" << std::endl;
                } else {
                    std::cout << "读者删除失败！" << std::endl;
                }
                break;
            }
            case 3: {
                std::string keyword;
                std::cin.ignore();
                
                std::cout << "请输入关键字: ";
                std::getline(std::cin, keyword);
                
                std::vector<Reader*> results = searchReaders(keyword);
                if (results.empty()) {
                    std::cout << "未找到匹配的读者！" << std::endl;
                } else {
                    std::cout << "找到 " << results.size() << " 位匹配的读者：" << std::endl;
                    std::cout << "=======================================" << std::endl;
                    
                    for (Reader* reader : results) {
                        reader->display();
                        std::cout << "=======================================" << std::endl;
                    }
                }
                break;
            }
            case 4:
                displayAllReaders();
                break;
            case 0:
                return;
            default:
                std::cout << "选择错误，请重新输入！" << std::endl;
                break;
        }
    }
}

void LibrarySystem::borrowReturnMenu() {
    while (true) {
        std::cout << "\n==================借/还书==================" << std::endl;
        std::cout << "1. 借书" << std::endl;
        std::cout << "2. 还书" << std::endl;
        std::cout << "0. 返回主菜单" << std::endl;
        std::cout << "===========================================" << std::endl;
        
        int choice;
        std::cout << "请输入您的选择: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入错误，请重新输入！" << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1: {
                int readerId, bookId;
                
                std::cout << "请输入读者ID: ";
                std::cin >> readerId;
                
                std::cout << "请输入图书ID: ";
                std::cin >> bookId;
                
                borrowBook(readerId, bookId);
                break;
            }
            case 2: {
                int readerId, bookId;
                
                std::cout << "请输入读者ID: ";
                std::cin >> readerId;
                
                std::cout << "请输入图书ID: ";
                std::cin >> bookId;
                
                returnBook(readerId, bookId);
                break;
            }
            case 0:
                return;
            default:
                std::cout << "选择错误，请重新输入！" << std::endl;
                break;
        }
    }
} 