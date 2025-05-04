#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
private:
    int id;                 // 图书ID
    std::string name;       // 图书名称
    std::string author;     // 作者
    std::string publisher;  // 出版社
    bool borrowed;          // 借阅状态（true为已借出）

public:
    Book();
    Book(int id, const std::string& name, const std::string& author, const std::string& publisher);
    
    // 获取图书信息
    int getId() const;
    std::string getName() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    bool isBorrowed() const;
    
    // 设置图书信息
    void setId(int id);
    void setName(const std::string& name);
    void setAuthor(const std::string& author);
    void setPublisher(const std::string& publisher);
    void setBorrowed(bool status);
    
    // 显示图书信息
    void display() const;
    
    // 文件读写辅助函数
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend std::istream& operator>>(std::istream& is, Book& book);
};

#endif // BOOK_H 