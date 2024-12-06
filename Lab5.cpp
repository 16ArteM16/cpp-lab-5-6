#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;

public:
    Book(string t = "", string a = "", string i = "") : title(t), author(a), isbn(i) {}

    // Метод для установки деталей книги
    void setDetails(string t, string a, string i) {
        title = t;
        author = a;     
        isbn = i;
    }

    
    void display() const {
        cout << "Название: " << title << ", Автор: " << author << ", ISBN: " << isbn << endl;
    }

    string getIsbn() const {
        return isbn;
    }
    string getTitle() const {
        return title;
    }
    string getAuthor() const {
        return author;
    }
};

class User {
private:
    string name;
    int userId;

public:
    User(string n = "", int id = 0) : name(n), userId(id) {}

    // Метод для установки данных пользователя
    void setDetails(string n, int id) {
        name = n;
        userId = id;
    }

    
    void display() const {
        cout << "Пользователь: " << name << ", ID: " << userId << endl;
    }

    int getUserId() const {
        return userId;
    }

    // Виртуальная функция для выполнения действия пользователем
    virtual void performAction() = 0;
};

class Member : public User {
public:
   
    Member(string n = "", int id = 0) : User(n, id) {}

    // Переопределение виртуальной функции для члена библиотеки
    void performAction() {
        cout << "Пользователь взял книгу." << endl;
    }
};

class Librarian : public User {
public:
   
    Librarian(string n = "", int id = 0) : User(n, id) {}

    // Переопределение виртуальной функции для библиотекаря
    void performAction() {
        cout << "Библиотекарь управляет каталогом книг." << endl;
    }
};

class Loan {
private:
    Book* book;        // Указатель на книгу
    User* user;        // Указатель на пользователя
    bool isReturned;   // Статус возврата книги

public:
   
    Loan(Book* b = nullptr, User* u = nullptr, bool returned = false)
        : book(b), user(u), isReturned(returned) {}

    // Метод для отображения информации о выдаче
    void display() const {
        if (book && user) {
            cout << "Книга: ";
            book->display();
            cout << "Взято: ";
            user->display();
            cout << "Статус: " << (isReturned ? "Возвращена" : "Не возвращена") << endl;
        } else {
            cout << "Ошибка информации!" << endl;
        }
    }

    // Метод для пометки книги как возвращенной
    void returnBook() {
        isReturned = true;
    }
};

int main() {
    // Создаем массивы книг и пользователей
    const int MAX_BOOKS = 3;
    const int MAX_USERS = 2;
    const int MAX_LOANS = 3;

    Book books[MAX_BOOKS];  // Статический массив книг
    User* users[MAX_USERS]; // Статический массив пользователей, указатели на User
    Loan loans[MAX_LOANS];  // Массив записей о выдаче книг

    
    books[0].setDetails("Евгений Онегин", "А.С. Пушкин", "978-5-392-41084-2");
    books[1].setDetails("Преступление и наказание", "Ф.М. Достоевский", "978-5-17-090630-7");
    books[2].setDetails("Гроза", "А.Н. Островский", "978-5-04-119071-2");

    // Инициализация пользователей
    users[0] = new Member("Борис", 1);  // Создаем нового члена библиотеки
    users[1] = new Librarian("Евгений", 2);  // Создаем библиотекаря

    // Создаем записи о выдаче книг
    loans[0] = Loan(&books[0], users[0]);  
    loans[1] = Loan(&books[1], users[0]);  
    loans[2] = Loan(&books[2], users[1]);  

    // Выводим книги
    cout << "Книги в библиотеке:" << endl;
    for (int i = 0; i < MAX_BOOKS; i++) {
        books[i].display();  // Отображаем каждую книгу
    }

    // Выводим информацию о пользователях
    cout << "\nПользователи в системе:" << endl;
    for (int i = 0; i < MAX_USERS; i++) {
        users[i]->display();  // Отображаем каждого пользователя
    }

    // Пользователи выполняют свои действия
    cout << "\nДействия пользователей:" << endl;
    for (int i = 0; i < MAX_USERS; i++) {
        users[i]->performAction(); // Виртуальные действия пользователей
    }

  // Выводим информацию о выдачах книг
    cout << "\nИнформация о выдачах книг:" << endl;
    for (int i = 0; i < MAX_LOANS; i++) {
        loans[i].display();
    }


    // Помечаем одну книгу как возвращенную
    cout << "\nКнига 'Евгений Онегин' возвращена..." << endl;
    loans[0].returnBook();
    loans[0].display();
    
    for (int i = 0; i < MAX_USERS; i++) {
        delete users[i];
    }
    return 0;
}
