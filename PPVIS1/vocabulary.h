#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;
template<typename T>
	///Класс, реализующий дерево, в котором храниться словарь
class Vocabulary 
{
private:
	template<typename T>
		///Класс, реализующий узел дерева
	class Node
	{
	public:
		Node* pRight;
		Node* pLeft;
		T Word_E;
		T Word_R;
		Node(T Word_E = T(), T Word_R = T(), Node* pRight = nullptr, Node* pLeft = nullptr)
		{
			this->Word_E = Word_E;
			this->Word_R = Word_R;
			this->pLeft = pLeft;
			this->pRight = pRight;
		}
	};
public:

	///Семя дерева
	Node<T>* head;
	///Количество узлов дерева
	int size;
	///Конструктор, устанавливающий начальное состояние дерева
	Vocabulary();
	///Функция, принимающая и заносящая в дерево значения
	void push_back(T Word_E, T Word_R);
	///Функция, выводящая данные по элементу
	void show_data(T Word_E);
	///Функция, меняющая данные по элементу
	void change_data(T Word_E, T Word_R);
	///Функция, удаляющая элемент
	void delete_element(T Word_E);
	///Функция, рекурсивно выводящая все элементы дерева
	void Show_Tree(Node<T>* Vocabulary);
	///Функция, рекурсивно записывающая дерево в файл
	void Fout(Node<T>* current, ofstream& fout);
	///Функция, рекурсивно добавляющая отдельную ветвь в дерево
	void Paste(Node<T>* Vocabulary);
	///Функция, возвращающая текущее количество узлов дерева.
	int GetSize()
	{
		return size;
	}
};

template<typename T>
Vocabulary<T>::Vocabulary()
{
	size = 0;
	head = nullptr;
}

template<typename T>
void Vocabulary<T>::push_back(T Word_E, T Word_R)
{
	if (head == nullptr)
	{
		head = new Node<T>;
		head->Word_E = Word_E;
		head->Word_R = Word_R;
	}
	else
	{
		Node<T>* current = this->head;
		while (current->pLeft || current->pRight != nullptr)
		{
			if (Word_E <= current->Word_E)
			{
				if (current->pLeft == nullptr) { break; }
				current = current->pLeft;
			}
			if (Word_E > current->Word_E)
			{
				if (current->pRight == nullptr) { break; }
				current = current->pRight;
			}
		}
		if (Word_E <= current->Word_E)
		{
			current->pLeft = new Node<T>(Word_E);
			current->pLeft->Word_E = Word_E;
			current->pLeft->Word_R = Word_R;
		}
		else
		{
			current->pRight = new Node<T>(Word_E);
			current->pRight->Word_E = Word_E;
			current->pRight->Word_R = Word_R;
		}
	}
	size++;
}

template<typename T>
void Vocabulary<T>::show_data(T Word_E)
{
	Node<T>* current = this->head;
	if (head == nullptr)
	{
		cout << "Словарь пуст\n";
	}
	else
	{
		while (current != nullptr)
		{
			if (Word_E == current->Word_E)
			{
				cout << "Английский: " << current->Word_E << "\tРусский: " << current->Word_R << endl;
				break;
			}
			if (current->pLeft == nullptr && current->pRight == nullptr)
			{
				current = nullptr;
				cout << "Такого узла нет!";
				break;
			}
			if (Word_E < current->Word_E && current->pLeft != nullptr)
			{
				current = current->pLeft;
			}
			if (Word_E > current->Word_E&& current->pRight != nullptr)
			{
				current = current->pRight;
			}
		}
	}
}

template<typename T>
void Vocabulary<T>::change_data(T Word_E, T Word_R)
{
	Node<T>* current = this->head;
	if (head == nullptr)
	{
		cout << "Словарь пуст\n";
	}
	else
	{
		while (current != nullptr)
		{
			if (Word_E == current->Word_E)
			{
				current->Word_R = Word_R;
				cout << "Английский: " << current->Word_E << "\tРусский: " << current->Word_R << endl;
				break;
			}
			if (current->pLeft == nullptr && current->pRight == nullptr)
			{
				current = nullptr;
				cout << "Такого узла нет!";
				break;
			}
			if (Word_E < current->Word_E && current->pLeft != nullptr)
			{
				current = current->pLeft;
			}
			if (Word_E > current->Word_E&& current->pRight != nullptr)
			{
				current = current->pRight;
			}
		}
	}
}

template<typename T>
void Vocabulary<T>::Paste(Node<T>* current)
{
	if (current)
	{
		Paste(current->pLeft);
		Paste(current->pRight);
		push_back(current->Word_E, current->Word_R);
	}
}

template<typename T>
void Vocabulary<T>::delete_element(T Word_E)
{
	Node<T>* current = this->head;
	Node<T>* save = this->head;
	Node<T>* savetopush = this->head;
	if (head == nullptr)
	{
		cout << "Словарь пуст\n";
	}
	else
	{
		while (current->pLeft != nullptr || current->pRight != nullptr)
		{
			if (head->Word_E == Word_E)
			{
				if (head->pLeft == nullptr && head->pRight == nullptr)
				{
					delete(head);
					head = nullptr;
					size--;
					break;
				}
				if (head->pLeft != nullptr && head->pRight == nullptr)
				{
					save = head->pLeft;
					delete(head);
					head = save;
					size--;
					break;
				}
				if (head->pLeft == nullptr && head->pRight != nullptr)
				{
					save = head->pRight;
					delete(head);
					head = save;
					size--;
					break;
				}
				if (head->pLeft != nullptr && head->pRight != nullptr)
				{
					savetopush = head->pLeft;
					save = head->pRight;
					delete(head);
					head = save;
					Paste(savetopush);
					size--;
					break;
				}
			}
			if (Word_E == current->pLeft->Word_E)
			{
				if (current->pLeft->pLeft == nullptr && current->pLeft->pRight == nullptr)
				{
					delete (current->pLeft);
					current->pLeft = nullptr;
					size--;
					break;
				}
				if (current->pLeft->pLeft == nullptr && current->pLeft->pRight != nullptr)
				{
					save = current->pLeft->pRight;
					delete (current->pLeft);
					current = save;
					size--;
					break;
				}
				if (current->pLeft->pRight == nullptr && current->pLeft->pLeft != nullptr)
				{
					save = current->pLeft->pLeft;
					delete (current->pLeft);
					current = save;
					size--;
					break;
				}
				if (current->pLeft->pRight != nullptr && current->pLeft->pLeft != nullptr)
				{
					save = current->pLeft->pLeft;
					savetopush = current->pLeft->pRight;
					delete (current->pLeft);
					size--;
					Paste(savetopush);
					break;
				}
			}
			if (Word_E == current->pRight->Word_E)
			{
				if (current->pRight->pLeft == nullptr && current->pRight->pRight == nullptr)
				{
					delete (current->pRight);
					current->pRight = nullptr;
					size--;
					break;
				}
				if (current->pRight->pLeft == nullptr && current->pRight->pRight != nullptr)
				{
					save = current->pRight->pRight;
					delete (current->pRight);
					current = save;
					size--;
					break;
				}
				if (current->pRight->pRight == nullptr && current->pRight->pLeft != nullptr)
				{
					save = current->pRight->pLeft;
					delete (current->pRight);
					current = save;
					size--;
					break;
				}
				if (current->pRight->pRight != nullptr && current->pRight->pLeft != nullptr)
				{
					save = current->pRight->pLeft;
					savetopush = current->pRight->pRight;
					delete (current->pRight);
					size--;
					Paste(savetopush);
					break;
				}
			}
			if (current->pLeft == nullptr && current->pRight == nullptr)
			{
				current = nullptr;
				cout << "Такого узла нет!";
				break;
			}
			if (Word_E < current->Word_E && current->pLeft != nullptr)
			{
				current = current->pLeft;
			}
			if (Word_E > current->Word_E&& current->pRight != nullptr)
			{
				current = current->pRight;
			}
		}
	}
}


template<typename T>
void Vocabulary<T>::Show_Tree(Node<T>* current)
{
	if (current)
	{
		Show_Tree(current->pLeft);
		cout << current->Word_E << "\t" << current->Word_R << endl;
		Show_Tree(current->pRight);
	}
}

template<typename T>
void Vocabulary<T>::Fout(Node<T>* current, ofstream& fout)
{
	if (current)
	{
		Fout(current->pLeft, fout);
		fout << endl << current->Word_E << endl << current->Word_R;
		Fout(current->pRight, fout);
	}
}