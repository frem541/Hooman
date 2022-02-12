#include "Human.h"
#include "HumanUtility.h"
#include <iostream>
#include <string>
#include <windows.h>

#ifdef max
#undef max
#endif

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("Color F0");
	Human** humanArray = new Human*[1];
	Human* human;
	size_t humanArrayLength = 0;
	std::wstring name, patronymic, lastName, address;
	std::string strAge, strEducation;
	Education education;
	Gender gender;
	uint8_t age;
	wchar_t wchoice;
	char choice;
	int ichoice;
	size_t index;
	std::string strIndex;
	std::list<Human*> list;
	do
	{
		system("CLS");
		std::cout << "1 - Добавить гражданина к массиву" << std::endl;
		std::cout << "2 - Удалить гражданина с указанным индексом из массива" << std::endl;
		std::cout << "3 - Показать гражданина с указанным индексом" << std::endl;
		std::cout << "4 - редактировать гражданина" << std::endl;
		std::cout << "5 - Найти граждан, возраст которых превышает заданный" << std::endl;
		std::cout << "6 - Найти граждан с высшим образованием" << std::endl;
		std::cout << "7 - Найти граждан заданного пола" << std::endl;
		std::cout << "8 - Вывести список всех граждан" << std::endl;
		std::cout << "9 - Выход из программы" << std::endl;
		std::cout << "(1..9): ";
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice)
		{
		case '1':
			std::cout << "Введите фамилию: ";
			std::wcin >> lastName;
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Введите имя: ";
			std::wcin >> name;
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Введите отчество: ";
			std::wcin >> patronymic;
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Введите адрес: ";
			getline(std::wcin, address);
			do
			{
				std::cout << "Введите возраст: ";
				std::cin >> strAge;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				ichoice = atoi(strAge.c_str());
			} while (ichoice == 0 || ichoice > 200);
			age = ichoice;
			do
			{
				std::cout << "Введите образование: " << std::endl;
				showAllEducations();
				std::cin >> strEducation;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				ichoice = atoi(strEducation.c_str());
			} while (ichoice < 1 || ichoice > 11);
			education = getEducation(ichoice);
			do
			{
				std::cout << "Введите пол (М/Ж): ";
				std::wcin >> wchoice;
				std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (wchoice == L'М' || wchoice == L'м' || wchoice == L'M' || wchoice == L'm')
					gender = Gender::MALE;
				else if (wchoice == L'Ж' || wchoice == L'ж' || wchoice == L'F' || wchoice == L'f')
					gender = Gender::FEMALE;
			} while (wchoice != L'М' && wchoice != L'м' && wchoice != L'Ж' && wchoice != L'ж' &&
				wchoice != L'M' && wchoice != L'm' && wchoice != L'F' && wchoice != L'f');
			do
			{
				std::cout << "Введите индекс (-1 - в конец массива): " << std::endl;
				std::cin >> strIndex;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				index = _atoi64(strIndex.c_str());
				ichoice = atoi(strIndex.c_str());
			} while (((index == 0 && strIndex[0] != '0') || index > humanArrayLength) && ichoice != -1);
			if (ichoice == -1)
			{
				if (humanArrayLength > 0)
					index = humanArrayLength;
				else
					index = 0;
			}
			human = new Human(lastName, name, patronymic, address, education, gender, age);
			Human::insertHuman(humanArray, humanArrayLength, human, index);
			delete human;
			humanArrayLength++;
			break;
		case '2':
			do
			{
				std::cout << "Введите индекс: " << std::endl;
				std::cin >> strIndex;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				index = _atoi64(strIndex.c_str());
			} while (index == 0 && strIndex[0] != '0');
			try
			{
				Human::deleteHuman(humanArray, humanArrayLength, index);
				humanArrayLength--;
			}
			catch (std::out_of_range ex)
			{
				std::cout << ex.what();
			}
			break;
		case '3':
			do
			{
				std::cout << "Введите индекс: " << std::endl;
				std::cin >> strIndex;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				index = _atoi64(strIndex.c_str());
			} while (index == 0 && strIndex[0] != '0');
			if (index < humanArrayLength)
				showInfo(humanArray[index]);
			else
			{
				std::cout << "Элемента с таким индексом не существует!" << std::endl;
				break;
			}
			break;
		case '4':
			do
			{
				std::cout << "Введите индекс: " << std::endl;
				std::cin >> strIndex;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				index = _atoi64(strIndex.c_str());
			} while (index == 0 && strIndex[0] != '0' && index < humanArrayLength);
			showСharacteristics();
			do
			{
				std::cout << "Выберите характеристику для редактирования: ";
				std::cin >> choice;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} while (choice < '1' && choice > '7');
			redactСharacteristic(choice, humanArray[index]);
			break;
		case '5':
			do
			{
				std::cout << "Введите возраст: ";
				std::cin >> strAge;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				ichoice = atoi(strAge.c_str());
			} while (ichoice == 0 || ichoice > 200);
			age = ichoice;
		list = Human::getHumansWithAgeBiggerThan(humanArray, humanArrayLength, age);
		for (Human* hum : list)
			showInfo(hum);
		break;
		case '6':
			list = Human::getHumansWithHighEducation(humanArray, humanArrayLength);
			for (Human* hum : list)
				showInfo(hum);
			break;
		case '7':
			do
			{
				std::cout << "Введите пол (М/Ж): ";
				std::wcin >> wchoice;
				std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (wchoice == L'М' || wchoice == L'м' || wchoice == L'M' || wchoice == L'm')
					gender = Gender::MALE;
				else if (wchoice == L'Ж' || wchoice == L'ж' || wchoice == L'F' || wchoice == L'f')
					gender = Gender::FEMALE;
			} while (wchoice != L'М' && wchoice != L'м' && wchoice != L'Ж' && wchoice != L'ж' &&
					wchoice != L'M' && wchoice != L'm' && wchoice != L'F' && wchoice != L'f');
			list = Human::getHumansWithGender(humanArray, humanArrayLength, gender);
			for (Human* hum : list)
				showInfo(hum);
			break;
		case '8':
			for (size_t i = 0; i < humanArrayLength; i++)
			{
				std::cout << i+1 << ". ";
				showInfo(humanArray[i]);
			}
			break;
		case '9':
			exit(EXIT_SUCCESS);
		default:
			wchoice = L'y';
			continue;
			break;
		}
		do
		{
			std::cout << "Продолжить? (y/n): ";
			std::wcin >> wchoice;
		} while (wchoice != L'y' && wchoice != L'Y' && wchoice != L'д' && wchoice != L'Д' &&
			wchoice != L'n' && wchoice != L'N' && wchoice != L'н' && wchoice != L'Н');
	} while (wchoice == L'y' || wchoice == L'Y' || wchoice == L'д' || wchoice == L'Д');
	return 0;
}
