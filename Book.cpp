#include "Book.h"

Book::Book() : id(0), borrowed(false) {}

Book::Book(int id, const std::string& name, const std::string& author, const std::string& publisher)
    : id(id), name(name), author(author), publisher(publisher), borrowed(false) {}

int Book::getId() const {
    return id;
}

std::string Book::getName() const {
    return name;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getPublisher() const {
    return publisher;
}

bool Book::isBorrowed() const {
    return borrowed;
}

void Book::setId(int id) {
    this->id = id;
}

void Book::setName(const std::string& name) {
    this->name = name;
}

void Book::setAuthor(const std::string& author) {
    this->author = author;
}

void Book::setPublisher(const std::string& publisher) {
    this->publisher = publisher;
}

void Book::setBorrowed(bool status) {
    this->borrowed = status;
}

void Book::display() const {
    std::cout << "图书ID: " << id << std::endl;
    std::cout << "书名: " << name << std::endl;
    std::cout << "作者: " << author << std::endl;
    std::cout << "出版社: " << publisher << std::endl;
    std::cout << "状态: " << (borrowed ? "已借出" : "可借阅") << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.id << "\n" << book.name << "\n" << book.author << "\n" 
       << book.publisher << "\n" << book.borrowed;
    return os;
}

std::istream& operator>>(std::istream& is, Book& book) {
    is >> book.id;
    is.ignore();
    std::getline(is, book.name);
    std::getline(is, book.author);
    std::getline(is, book.publisher);
    is >> book.borrowed;
    return is;
} 