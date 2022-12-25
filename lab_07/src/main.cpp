/*Файл с фамилиями из паспортного стола отсортирован в алфавитном порядке. Создать индексный файл для поиска информации по фамилии*/

#include <iostream>
#include <fstream>
#include <string>

const static char *path_data = "src/firstnames.txt", *path_id = "src/k_index.txt";

using namespace std;

struct entry {
	std::string key_;
	int key_p_;
};

void createIndexFile() {
	ifstream fin(path_data);
	ofstream fout(path_id);
	
	if (!fin.is_open()) {
		cout << "> ошибка открытия файла!\n";
	}
	else {
		char buff[13]{};

		for (int i = 0; !fin.eof(); ++i) {
			int pFile = fin.tellg();
			
			fin >> buff;
			if ((i + 1) % 10 == 0) {
				fout << buff << " " << pFile;
				if (i + 10 < 100) {
					fout << endl;
				}
			}
		}
		cout << "> индексный файл создан!\n";
	}
	fin.close();
	fout.close();
}

void search(string key) {
	ifstream file(path_id);

	if (!file.is_open()) {
		cout << "> ошибка открытия файла!\n";
	}
	else {
		entry *data = new entry[2]{};
		int idBeg = 0;

		for (; !file.eof(); idBeg += 10) {
			file >> data[0].key_ >> data[0].key_p_;
			if (data[0].key_ > key) {
				entry temp{ data[0].key_, data[0].key_p_ };
				data[0] = data[1];
				data[1] = temp;

				break;
			}
			if (!file.eof()) {
				file >> data[1].key_ >> data[1].key_p_;
				if (data[1].key_ > key) {
					idBeg += 10;
					break;
				}
				idBeg += 10;
			}
		}
		idBeg += (idBeg < 10) ? 1 : ((idBeg == 100) ? -10 : 0);
		file.close();
		
		file.open(path_data);
		if (!file.is_open()) {
			cout << "> ошибка открытия файла!\n";
		}
		else {
			char buff[15]{};

			cout << "> результат поиска: ";
			for (file.seekg(data[0].key_p_); file.tellg() < data[1].key_p_; ++idBeg) {
				file >> buff;
				if (buff == key) {
					cout << "[" << idBeg << "] " << buff << endl;
					break;
				}
			}
			if (buff != key) {
				cout << "совпадений не найдено" << endl;
			}
		}
		delete[] data;
		file.close();
	}
}

int main() {
	setlocale(LC_ALL, "ru");

	//createIndexFile();
	search("Зибзй");

	return 0;
}