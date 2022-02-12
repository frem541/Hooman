#include "HumanUtility.h"
#include "iostream"
#include <string>
void showAllEducations()
{
	std::cout << "1 - Дошкольное" << std::endl;
	std::cout << "2 - Начальное" << std::endl;
	std::cout << "3 - Среднее неполное" << std::endl;
	std::cout << "4 - Среднее полное" << std::endl;
	std::cout << "5 - Профессиональное" << std::endl;
	std::cout << "6 - Незаконченное высшее" << std::endl;
	std::cout << "7 - Бакалавр" << std::endl;
	std::cout << "8 - Специалист" << std::endl;
	std::cout << "9 - Магистр" << std::endl;
	std::cout << "10 - Аспирант" << std::endl;
	std::cout << "11 - Образование неизвестно" << std::endl;
}

Education getEducation(int choice)
{
	Education education;
	switch (choice)
	{
	case 1: education = Education::PRESCHOOL; break;
	case 2: education = Education::PRIMARY_GENERAL; break;
	case 3: education = Education::BASIC_GENERAL; break;
	case 4: education = Education::FULL_GENERAL; break;
	case 5: education = Education::PROFESSIONAL; break;
	case 6: education = Education::UNDERGRADUATE; break;
	case 7: education = Education::HIGH_BACHELOR; break;
	case 8: education = Education::HIGH_SPECIALIST; break;
	case 9: education = Education::HIGH_MASTER; break;
	case 10: education = Education::HIGH_ASPIRANT; break;
	default: education = Education::UNKNOWN; break;
	}
	return education;
}

void showInfo(Human* human)
{
	human->showLastName();
	std::cout << ' ';
	human->showName();
	std::cout << ' ';
	human->showPatronymic();
	std::cout << ", ";
	human->showAddress();
	std::cout << ", ";
	human->showEducation();
	std::cout << ", ";
	human->showGender();
	std::cout << ", ";
	human->showAge();
	if (human->getAge()%10 == 1)
		std::cout << " год";
	else if (human->getAge()%10 >= 2 && human->getAge()%10 <= 4)
		std::cout << " года";
	else 
		std::cout << " лет";
	std::cout << std::endl;
}

void showСharacteristics()
{
	std::cout << "1 - Фамилия" << std::endl;
	std::cout << "2 - Имя" << std::endl;
	std::cout << "3 - Отчество" << std::endl;
	std::cout << "4 - Адрес" << std::endl;
	std::cout << "5 - Возраст" << std::endl;
	std::cout << "6 - Образование" << std::endl;
	std::cout << "7 - Пол" << std::endl;
}

void redactСharacteristic(char choice, Human* human)
{
	std::wstring str;
	uint8_t age;
	std::string strAge;
	int ichoice;
	Gender gender;
	std::string strEducation;
	wchar_t wchoice;
	switch (choice)
	{
	case '1':
		std::cout << "Введите фамилию: ";
		std::wcin >> str;
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		human->setLastName(str);
		break;
	case '2':
		std::cout << "Введите имя: ";
		std::wcin >> str;
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		human->setName(str);
		break;
	case '3':
		std::cout << "Введите отчество: ";
		std::wcin >> str;
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		human->setPatronymic(str);
		break;
	case '4':
		std::cout << "Введите адрес: ";
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(std::wcin, str);
		human->setAddress(str);
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
		human->setAge(age);
		break;
	case '6':
		do
		{
			std::cout << "Введите образование: " << std::endl;
			showAllEducations();
			std::cin >> strEducation;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			ichoice = atoi(strEducation.c_str());
		} while (ichoice < 1 || ichoice > 11);
		human->setEducation(getEducation(ichoice));
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
		human->setGender(gender);
		break;
	default:
		break;
	}
}