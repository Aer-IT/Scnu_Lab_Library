#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>
#include <vector>

class Reader {
private:
    int id;                    // 读者ID
    std::string name;          // 读者姓名
    std::string contact;       // 联系方式
    std::vector<int> borrowedBooks;  // 已借图书ID列表

public:
    Reader();
    Reader(int id, const std::string& name, const std::string& contact);
    
    // 获取读者信息
    int getId() const;
    std::string getName() const;
    std::string getContact() const;
    const std::vector<int>& getBorrowedBooks() const;
    
    // 设置读者信息
    void setId(int id);
    void setName(const std::string& name);
    void setContact(const std::string& contact);
    
    // 借书和还书
    bool borrowBook(int bookId);
    bool returnBook(int bookId);
    
    // 显示读者信息
    void display() const;
    
    // 文件读写辅助函数
    friend std::ostream& operator<<(std::ostream& os, const Reader& reader);
    friend std::istream& operator>>(std::istream& is, Reader& reader);
};

#endif // READER_H 