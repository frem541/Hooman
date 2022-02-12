#include "HumanUtility.h"
#include "iostream"
#include <string>
void showAllEducations()
{
	std::cout << "1 - ����������" << std::endl;
	std::cout << "2 - ���������" << std::endl;
	std::cout << "3 - ������� ��������" << std::endl;
	std::cout << "4 - ������� ������" << std::endl;
	std::cout << "5 - ����������������" << std::endl;
	std::cout << "6 - ������������� ������" << std::endl;
	std::cout << "7 - ��������" << std::endl;
	std::cout << "8 - ����������" << std::endl;
	std::cout << "9 - �������" << std::endl;
	std::cout << "10 - ��������" << std::endl;
	std::cout << "11 - ����������� ����������" << std::endl;
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
		std::cout << " ���";
	else if (human->getAge()%10 >= 2 && human->getAge()%10 <= 4)
		std::cout << " ����";
	else 
		std::cout << " ���";
	std::cout << std::endl;
}

void show�haracteristics()
{
	std::cout << "1 - �������" << std::endl;
	std::cout << "2 - ���" << std::endl;
	std::cout << "3 - ��������" << std::endl;
	std::cout << "4 - �����" << std::endl;
	std::cout << "5 - �������" << std::endl;
	std::cout << "6 - �����������" << std::endl;
	std::cout << "7 - ���" << std::endl;
}

void redact�haracteristic(char choice, Human* human)
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
		std::cout << "������� �������: ";
		std::wcin >> str;
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		human->setLastName(str);
		break;
	case '2':
		std::cout << "������� ���: ";
		std::wcin >> str;
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		human->setName(str);
		break;
	case '3':
		std::cout << "������� ��������: ";
		std::wcin >> str;
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		human->setPatronymic(str);
		break;
	case '4':
		std::cout << "������� �����: ";
		std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(std::wcin, str);
		human->setAddress(str);
		break;
	case '5':
		do
		{
			std::cout << "������� �������: ";
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
			std::cout << "������� �����������: " << std::endl;
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
			std::cout << "������� ��� (�/�): ";
			std::wcin >> wchoice;
			std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (wchoice == L'�' || wchoice == L'�' || wchoice == L'M' || wchoice == L'm')
				gender = Gender::MALE;
			else if (wchoice == L'�' || wchoice == L'�' || wchoice == L'F' || wchoice == L'f')
				gender = Gender::FEMALE;
		} while (wchoice != L'�' && wchoice != L'�' && wchoice != L'�' && wchoice != L'�' &&
			wchoice != L'M' && wchoice != L'm' && wchoice != L'F' && wchoice != L'f');
		human->setGender(gender);
		break;
	default:
		break;
	}
}