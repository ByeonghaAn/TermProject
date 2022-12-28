#ifndef BookList_h
#define BookList_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Book
{
private:
	string title;
	string author;
	int year;
	string genre;

public:
	Book() : title(""), author(""), year(2016), genre("")
	{}

	void setTitle(string newTitle)
	{
		this->title = newTitle;
	}
	void setAuthor(string newAuthor)
	{
		this->author = newAuthor;
	}
	void setYear(int newYear)
	{
		this->year = newYear;
	}
	void setGenre(string newGenre)
	{
		this->genre = newGenre;
	}

	string getTitle() const
	{
		return this->title;
	}
	string getAuthor() const
	{
		return this->author;
	}
	int getYear() const
	{
		return this->year;
	}
	string getGenre() const
	{
		return this->genre;
	}

	void displayBook(ostream& out) const
	{
		out << "Title: " << this->title << endl;
		out << "Author: " << this->author << endl;
		out << "Year: " << this->year << endl;
		out << "Genre: " << this->genre << endl;
	}
};

class BookList
{
private:
	Book books[10];
	int count;
	int size;

	void slideUp(int location)
	{
		for (int i = count; i > location; i--)
		{
			this->books[i] = this->books[i - 1];
		}
		this->books[location] = Book();
	}
	void slideDown(int location)
	{
		for (int i = location; i < (count - 1); i++)
		{
			this->books[i] = this->books[i + 1];
		}
		this->books[count - 1] = Book();
	}

public:
	BookList() : count(0), size(10)
	{}

	void addBook(Book b)
	{
		if (count < size)
		{
			this->books[count] = b;
			this->count++;
		}
	}
	void addBookAt(Book b, int location)
	{
		if (location <= 0 && count < size)
		{
			for (int i = (count - 1); i >= 0; i--)
			{
				this->books[i + 1] = this->books[i];
			}
			this->books[0] = b;
			this->count++;
		}
		else if (location >= count && count < size)
		{
			this->books[count] = b;
			this->count++;
		}
		else if (location > 0 && location < count && count < size)
		{
			for (int i = (count - 1); i >= location; i--)
			{
				this->books[i + 1] = this->books[i];
			}
			this->books[location] = b;
			this->count++;
		}
	}
	Book findBook(int location) const
	{
		if (location >= 0 && location < count)
		{
			return this->books[location];
		}
		else
		{
			return Book();
		}
	}
	Book removeBook(int location)
	{
		Book removeB;

		if (location >= 0 && location < count)
		{
			removeB = this->books[location];

			for (int i = location; i < (count - 1); i++)
			{
				this->books[i] = this->books[i + 1];
			}
			this->books[count - 1] = Book();
			this->count--;

			return removeB;
		}
		else
		{
			return Book();
		}
	}
	void displayBooks(std::ostream& out) const
	{
		out << "Books in my list:" << endl;
		for (int i = 0; i < count; i++)
		{
			this->books[i].displayBook(out);
		}
	}
};

#endif