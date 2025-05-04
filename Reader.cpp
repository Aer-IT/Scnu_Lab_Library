#include "Reader.h"
#include <algorithm>

Reader::Reader() : id(0) {}

Reader::Reader(int id, const std::string& name, const std::string& contact)
    : id(id), name(name), contact(contact) {}

int Reader::getId() const {
    return id;
}

std::string Reader::getName() const {
    return name;
}

std::string Reader::getContact() const {
    return contact;
}

const std::vector<int>& Reader::getBorrowedBooks() const {
    return borrowedBooks;
}

void Reader::setId(int id) {
    this->id = id;
}

void Reader::setName(const std::string& name) {
    this->name = name;
}

void Reader::setContact(const std::string& contact) {
    this->contact = contact;
}

bool Reader::borrowBook(int bookId) {
    // 检查是否已经借了这本书
    if (std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId) != borrowedBooks.end()) {
        return false; // 已经借了这本书
    }
    
    borrowedBooks.push_back(bookId);
    return true;
}

bool Reader::returnBook(int bookId) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
    if (it == borrowedBooks.end()) {
        return false; // 没有借这本书
    }
    
    borrowedBooks.erase(it);
    return true;
}

void Reader::display() const {
    std::cout << "读者ID: " << id << std::endl;
    std::cout << "姓名: " << name << std::endl;
    std::cout << "联系方式: " << contact << std::endl;
    std::cout << "已借图书数量: " << borrowedBooks.size() << std::endl;
    
    if (!borrowedBooks.empty()) {
        std::cout << "已借图书ID: ";
        for (size_t i = 0; i < borrowedBooks.size(); ++i) {
            std::cout << borrowedBooks[i];
            if (i < borrowedBooks.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Reader& reader) {
    os << reader.id << "\n" << reader.name << "\n" << reader.contact << "\n";
    
    // 保存已借图书ID列表
    os << reader.borrowedBooks.size() << "\n";
    for (int bookId : reader.borrowedBooks) {
        os << bookId << " ";
    }
    
    return os;
}

std::istream& operator>>(std::istream& is, Reader& reader) {
    is >> reader.id;
    is.ignore();
    std::getline(is, reader.name);
    std::getline(is, reader.contact);
    
    // 读取已借图书ID列表
    size_t count;
    is >> count;
    reader.borrowedBooks.clear();
    
    for (size_t i = 0; i < count; ++i) {
        int bookId;
        is >> bookId;
        reader.borrowedBooks.push_back(bookId);
    }
    
    return is;
} 