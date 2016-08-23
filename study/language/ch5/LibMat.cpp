#include <iostream>
#include <typeinfo>
using namespace std;

class LibMat{
public:
	LibMat(){
		cout << "LibMat::LibMat() default constructor!\n";
	}
	virtual ~LibMat(){
		cout<< "LibMat::~LibMat() destructor!\n";
	}
	virtual void print() const{
		cout << "LibMat::print()!\n";
	}
};

class Book : public LibMat{
public:
	Book(const string &title, const string &author)
		: _title(title), _author(author){
		cout << "Book::Book(" << _title << ", "
			 << _author << ") constructor!\n";
	}
	virtual ~Book(){
		cout<< "Book::~Book() destructor!\n";
	}
	virtual void print() const{
		cout << "Book::print()!\n"
			 << "title:  " << _title << endl
			 << "author: " << _author << endl;
	}
	const string &get_title() const{return _title;}
	const string &get_author() const{return _author;}
protected:
	string _title;
	string _author;
};

class AudioBook : public Book{
public:
	AudioBook(const string &title,
			  const string &author, const string &narrator)
		: Book(title, author), _narrator(narrator){
		cout << "AudioBook::AudioBook(" << _title
			 << ", " << _author
			 << ", " << _narrator
			 << ") constructor\n";
	}
	virtual ~AudioBook(){
		cout << "AudioBook::~AudioBook() destructor!\n";
	}
	virtual void print() const{
		cout << "AudioBook::print():\n"
			 << "title:    " << _title << endl
			 << "author:   " << _author << endl
			 << "narrator: " << _narrator << endl;
	}
	const string &get_narrator() const{return _narrator;}
protected:
	string _narrator;
};

void print(const LibMat &mat){
	cout << "in global print():\n";
	mat.print();
}

int main()
{
	Book book("book1", "author1");
	LibMat *pm = &book;
#if 1
	if(typeid(*pm) == typeid(Book)){
		Book *pt = static_cast<Book*>(pm);
		pt->get_title();
	}
#endif
#if 0
	cout << "\nCreating a LibMat object to print()\n";
	LibMat libmat;
	print(libmat);
#endif

#if 0
	cout << "\nCreating a Book object to print()\n";
	Book book("book1", "author1");
	print(book);
#endif

#if 0
	cout << "\nCreating a AudioBook object to print()\n";
	AudioBook abook("book2", "author2", "narrator");
	print(abook);
#endif
	return 0;
}
