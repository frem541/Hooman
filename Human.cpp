#include "Human.h"
#include <iostream>
#include <sstream>

bool wcstring_comparer::operator()(const wchar_t* left, const wchar_t* right) const
{
	return std::wcscmp(left, right) == 0;
}

size_t wcstring_hasher::operator()(const wchar_t* wcstr) const
{
	return std::hash<std::wstring_view>()(std::wstring_view(wcstr, std::wcslen(wcstr)));
}
std::unordered_map<wchar_t*, size_t, wcstring_hasher, wcstring_comparer> Human::names_;
std::unordered_map<wchar_t*, size_t, wcstring_hasher, wcstring_comparer> Human::patronymics_;

void Human::setName(const wchar_t* name, size_t length)
{
	wchar_t* newName = validateAndConvertStr(name, length);

	std::unordered_map<wchar_t*, size_t, wcstring_hasher, wcstring_comparer>::iterator it;
	it = names_.find(const_cast<wchar_t*>(newName));

	if (it != names_.end())
	{
		if (name_ != it->first)
		{
			if (name_ != NULL)
			{
				if (names_[name_] == 1)
				{
					names_.erase(name_);
					delete[] name_;
				}
				else
					names_[name_]--;
			}
			name_ = it->first;
			it->second++;
		}
		delete[] newName;
	}
	else
	{	
		names_.insert(std::pair(const_cast<wchar_t*>(newName), 1));
		if (name_ != NULL)
			if (names_[name_] == 1)
			{
				names_.erase(name_);
				delete[] name_;
			}
		name_ = newName;
	}
	nameLength_ = length;
}

void Human::setPatronymic(const wchar_t* patronymic, size_t length)
{
	wchar_t* newPatronymic = validateAndConvertStr(patronymic, length);

	std::unordered_map<wchar_t*, size_t, wcstring_hasher, wcstring_comparer>::iterator it;
	it = patronymics_.find(const_cast<wchar_t*>(newPatronymic));

	if (it != patronymics_.end()) 
	{
		if (patronymic_ != it->first)
		{
			if (patronymic_ != NULL)
			{
				if (patronymics_[patronymic_] == 1)
				{
					patronymics_.erase(patronymic_);
					delete[] patronymic_;
				}
				else
					patronymics_[patronymic_]--;
			}
			patronymic_ = it->first;
			it->second++;
		}
		delete[] newPatronymic;
	}
	else
	{
		patronymics_.insert(std::pair(const_cast<wchar_t*>(newPatronymic), 1));
		if (patronymic_ != NULL)
			if (patronymics_[patronymic_] == 1)
			{
				patronymics_.erase(patronymic_);
				delete[] patronymic_;
			}
		patronymic_ = newPatronymic;
	}
	patronymicLength_ = length;
}

void Human::setLastName(const wchar_t* lastName, size_t length)
{
	wchar_t* newLastName = validateAndConvertStr(lastName, length);
	lastName_.reset(newLastName);
	lastNameLength_ = length;
}

void Human::setAddress(const wchar_t* address, size_t length)
{
	wchar_t* newAddress = validateAndConvertStr(address, length);
	address_.reset(newAddress);
	addressLength_ = length;
}

void Human::setName(const wchar_t* name)
{
	size_t length = wcslen(name);
	setName(name, length);
}

void Human::setPatronymic(const wchar_t* patronymic)
{
	size_t length = wcslen(patronymic);
	setPatronymic(patronymic, length);
}

void Human::setLastName(const wchar_t* lastName)
{
	size_t length = wcslen(lastName);
	wchar_t* newLastName = new wchar_t[length + 1];
	memcpy(newLastName, lastName, length * sizeof(wchar_t));
	newLastName[length] = '\0';
	lastName_.reset(newLastName);
	lastNameLength_ = length;
}

void Human::setAddress(const wchar_t* address)
{
	size_t length = wcslen(address);
	wchar_t* newAddress = new wchar_t[length + 1];
	memcpy(newAddress, address, length * sizeof(wchar_t));
	newAddress[length] = '\0';
	address_.reset(newAddress);
	addressLength_ = length;
}

void Human::setName(const std::wstring& name)
{
	setName(name.c_str());
}
void Human::setPatronymic(const std::wstring& patronymic)
{
	setPatronymic(patronymic.c_str());
}
void Human::setLastName(const std::wstring& lastName)
{
	setLastName(lastName.c_str());
}
void Human::setAddress(const std::wstring& address)
{
	setAddress(address.c_str());
}

void Human::setEducation(Education Education)
{
	Education_ = Education;
}

void Human::setGender(Gender Gender)
{
	Gender_ = Gender;
}

void Human::setAge(int8_t age)
{
	age_ = age;
}

std::unique_ptr<wchar_t[]> Human::getName(size_t& length) const
{
	wchar_t* returnValue = new wchar_t[nameLength_];
	memcpy(returnValue, name_, nameLength_ * sizeof(wchar_t));
	std::unique_ptr<wchar_t[]> ptr(returnValue);
	length = nameLength_;
	return ptr;
}

std::unique_ptr<wchar_t[]> Human::getPatronymic(size_t& length) const
{
	wchar_t* returnValue = new wchar_t[patronymicLength_];
	memcpy(returnValue, patronymic_, patronymicLength_ * sizeof(wchar_t));
	std::unique_ptr<wchar_t[]> ptr(returnValue);
	length = patronymicLength_;
	return ptr;
}

std::unique_ptr<wchar_t[]> Human::getLastName(size_t& length) const
{
	wchar_t* returnValue = new wchar_t[lastNameLength_];
	memcpy(returnValue, lastName_.get(), lastNameLength_ * sizeof(wchar_t));
	std::unique_ptr<wchar_t[]> ptr(returnValue);
	length = lastNameLength_;
	return ptr;
}

std::unique_ptr<wchar_t[]> Human::getAddress(size_t& length) const
{
	wchar_t* returnValue = new wchar_t[addressLength_];
	memcpy(returnValue, address_.get(), addressLength_ * sizeof(wchar_t));
	std::unique_ptr<wchar_t[]> ptr(returnValue);
	length = addressLength_;
	return ptr;
}

std::unique_ptr<wchar_t[]> Human::getName() const
{
	wchar_t* returnValue = new wchar_t[nameLength_];
	memcpy(returnValue, name_, nameLength_ * sizeof(wchar_t));
	std::unique_ptr<wchar_t[]> ptr(returnValue);
	return ptr;
}

std::unique_ptr<wchar_t[]> Human::getPatronymic() const
{
	wchar_t* returnValue = new wchar_t[patronymicLength_];
	memcpy(returnValue, patronymic_, patronymicLength_ * sizeof(wchar_t));
	std::unique_ptr<wchar_t[]> ptr(returnValue);
	return ptr;
}

std::unique_ptr<wchar_t[]> Human::getLastName() const
{
	wchar_t* returnValue = new wchar_t[lastNameLength_];
	memcpy(returnValue, lastName_.get(), lastNameLength_ * sizeof(wchar_t));
	std::unique_ptr<wchar_t[]> ptr(returnValue);
	return ptr;
}

std::unique_ptr<wchar_t[]> Human::getAddress() const
{
	wchar_t* returnValue = new wchar_t[addressLength_];
	memcpy(returnValue, address_.get(), addressLength_ * sizeof(wchar_t));
	std::unique_ptr<wchar_t[]> ptr(returnValue);
	return ptr;
}

Education Human::getEducation() const
{
	return Education_;
}

Gender Human::getGender() const
{
	return Gender_;
}

uint8_t Human::getAge() const
{
	return age_;
}

void Human::showName() const
{
	std::wcout << name_;
}

void Human::showPatronymic() const
{
	std::wcout << patronymic_;
}

void Human::showLastName() const
{
	std::wcout << lastName_.get();
}

void Human::showAddress() const
{
	std::wcout << address_.get();
}

void Human::showEducation() const
{
	switch(Education_)
	{
	case Education::PRESCHOOL: std::cout << "дошкольное"; break;
	case Education::PRIMARY_GENERAL: std::cout << "начальное"; break;
	case Education::BASIC_GENERAL: std::cout << "среднее неполное"; break;
	case Education::FULL_GENERAL: std::cout << "среднее полное"; break;
	case Education::PROFESSIONAL: std::cout << "профессиональное"; break;
	case Education::UNDERGRADUATE: std::cout << "незаконченное высшее"; break;
	case Education::HIGH_BACHELOR: std::cout << "бакалавр"; break;
	case Education::HIGH_SPECIALIST: std::cout << "специалист"; break;
	case Education::HIGH_MASTER: std::cout << "магистр"; break;
	case Education::HIGH_ASPIRANT: std::cout << "аспирант"; break;
	default: std::cout << "образование неизвестно"; break;
	}
}

void Human::showGender() const
{
	switch (Gender_)
	{
	case Gender::MALE: std::cout << "мужчина"; break;
	case Gender::FEMALE: std::cout << "женщина"; break;
	default: std::cout << "неизвестно"; break;
	}
}

void Human::showAge() const
{
	std::cout << static_cast<int>(age_);
}

Human::Human()
{
	wchar_t* defaultStr = new wchar_t[1];
	defaultStr[0]= L'\0';
	setName(defaultStr, 1);
	setPatronymic(defaultStr, 1);
	setLastName(defaultStr, 1);
	setAddress(defaultStr, 1);
	Education_ = Education::UNKNOWN;
	Gender_ = Gender::UNKNOWN;
	delete[] defaultStr;
}

Human::Human(const std::wstring& lastName, const std::wstring& name, const std::wstring& patronymic,
	const std::wstring& address, const Education education, const Gender gender, const short age)
{
	name_ = NULL;
	patronymic_ = NULL;
	setName(name);
	setPatronymic(patronymic);
	setLastName(lastName);
	setAddress(address);
	setEducation(education);
	setAge(age);
	setGender(gender);
}

Human::Human(const wchar_t* lastName, const wchar_t* name, const wchar_t* patronymic,
	const wchar_t* address, const Education education, const Gender gender, const short age)
{
	name_ = NULL;
	patronymic_ = NULL;
	setName(name);
	setPatronymic(patronymic);
	setLastName(lastName);
	setAddress(address);
	setEducation(education);
	setAge(age);
	setGender(gender);
}

Human::Human(const wchar_t* lastName, const size_t nameLength, const wchar_t* name, const size_t patronymicLength, const wchar_t* patronymic, const size_t lastNameLength,
	const wchar_t* address, const size_t addressLength, const Education education, const Gender gender, const short age)
{
	name_ = NULL;
	patronymic_ = NULL;
	setName(name, nameLength);
	setPatronymic(patronymic, patronymicLength);
	setLastName(lastName, lastNameLength);
	setAddress(address, addressLength);
	setEducation(education);
	setAge(age);
	setGender(gender);
}

Human::Human(const Human& human)
{
	setName(human.name_);
	setPatronymic(human.patronymic_);

	lastName_ = human.lastName_;
	lastNameLength_ = human.lastNameLength_;

	address_ = human.address_;
	addressLength_ = human.addressLength_;

	Education_ = human.Education_;
	Gender_ = human.Gender_;
	age_ = human.age_;
}

Human::~Human()
{
	std::unordered_map<wchar_t*, size_t, wcstring_hasher, wcstring_comparer>::iterator it;
	it = names_.find(name_);
	if (it->second > 1)
		it->second--;
	else
	{
		names_.erase(name_);
		delete[] name_;
	}

	it = patronymics_.find(patronymic_);
	if (it->second > 1)
		it->second--;
	else
	{
		patronymics_.erase(patronymic_);
		delete[] patronymic_;
	}
}

void Human::insertHuman(Human**& humans, size_t length, const Human* human, size_t index)
{
	if (index == 0 && length == 0)
	{
		delete[] humans;
		humans = new Human *[1];
		humans[0] = new Human(*human);
	}
	else if (index <= length)
	{
		if (length == ULLONG_MAX)
			throw std::overflow_error("array length is bigger than size_t max value");

		Human** newArray = new Human*[length + 1];
		size_t i;

		for (i = 0; i < index; i++)
			newArray[i] = new Human(*humans[i]);

		newArray[i] = new Human(*human);

		for (i = index + 1; i < length + 1; i++)
			newArray[i] = new Human(*humans[i-1]);

		for (int i = 0; i < length; i++)
			delete humans[i];
		delete[] humans;
		humans = newArray;
	}
	else
	{
		throw std::out_of_range(generateOutOfRangeMessage(length, index));
	}
}

void Human::insertHuman(Human*& humans, size_t length, const Human* human, size_t index)
{
	if (index == 0 && length == 0)
	{
	delete[] humans;
	humans = new Human[1];
	humans[0] = *human;
	}
	else if (index <= length)
	{
		if (length == ULLONG_MAX)
			throw std::overflow_error("array length is bigger than size_t max value");

		Human* newArray = new Human[length + 1];
		size_t i;

		for (i = 0; i < index; i++)
			newArray[i] = humans[i];

		newArray[i] = *human;

		for (i = index + 1; i < length + 1; i++)
			newArray[i] = humans[i - 1];

		delete[] humans;
		humans = newArray;
	}
	else
	{
		throw std::out_of_range(generateOutOfRangeMessage(length, index));
	}
}

void Human::deleteHuman(Human**& humans, size_t length, size_t index)
{
	if (length == 0)
		throw std::out_of_range("array is empty");
	if (index < length)
	{
		if (length == 1)
		{
			delete humans[0];
			delete humans;
			humans = new Human*[0];
			return;
		}
		Human** newArray = new Human*[length - 1];
		size_t i;

		for (i = 0; i < index; i++)
			newArray[i] = new Human(*humans[i]);

		for (i = index + 1; i < length; i++)
			newArray[i - 1] = new Human(*humans[i]);

		for (i = 0; i < length; i++)
			delete humans[i];
		delete[] humans;

		humans = newArray;
	}
	else
	{
		throw std::out_of_range(generateOutOfRangeMessage(length, index));
	}
}

void Human::deleteHuman(Human*& humans, size_t length, size_t index)
{
	if (length == 0)
		throw std::out_of_range("array is empty");
	if (index < length)
	{
		if (length == 1)
		{
			delete humans;
			humans = new Human[0];
			return;
		}
		Human* newArray = new Human[length - 1];
		size_t i;

		for (i = 0; i < index; i++)
			newArray[i] = humans[i];

		for (i = index; i < length - 1; i++)
			newArray[i] = humans[i + 1];
	}
	else
	{
		throw std::out_of_range(generateOutOfRangeMessage(length, index));
	}
}

std::list<Human*> Human::getHumansWithAgeBiggerThan(Human** humans, size_t length, short age)
{
	std::list<Human*> returnHumans;
	for (size_t i = 0; i < length; i++)
	{
		if (humans[i]->getAge() > age)
			returnHumans.push_back(new Human(*humans[i]));
	}
	return returnHumans;
}

std::list<Human> Human::getHumansWithAgeBiggerThan(Human* humans, size_t length, short age)
{
	std::list<Human> returnHumans;
	for (size_t i = 0; i < length; i++)
	{
		if (humans[i].getAge() > age)
			returnHumans.push_back(humans[i]);
	}
	return returnHumans;
}

std::list<Human*> Human::getHumansWithHighEducation(Human** humans, size_t length)
{
	std::list<Human*> returnHumans;
	for (size_t i = 0; i < length; i++)
	{
		if (humans[i]->getEducation() >= Education::HIGH_BACHELOR && humans[i]->getEducation() <= Education::HIGH_ASPIRANT)
			returnHumans.push_back(new Human(*humans[i]));
	}
	return returnHumans;
}

std::list<Human> Human::getHumansWithHighEducation(Human* humans, size_t length)
{
	std::list<Human> returnHumans;
	for (size_t i = 0; i < length; i++)
	{
		if (humans[i].getEducation() >= Education::HIGH_BACHELOR && humans[i].getEducation() <= Education::HIGH_ASPIRANT)
			returnHumans.push_back(humans[i]);
	}
	return returnHumans;
}

std::list<Human*> Human::getHumansWithGender(Human** humans, size_t length, Gender gender)
{
	std::list<Human*> returnHumans;
	for (size_t i = 0; i < length; i++)
	{
		if (humans[i]->getGender() == gender)
			returnHumans.push_back(new Human(*humans[i]));
	}
	return returnHumans;
}

std::list<Human> Human::getHumansWithGender(Human* humans, size_t length, Gender gender)
{
	std::list<Human> returnHumans;
	for (size_t i = 0; i < length; i++)
	{
		if (humans[i].getGender() == gender)
			returnHumans.push_back(humans[i]);
	}
	return returnHumans;
}

wchar_t* Human::validateAndConvertStr(const wchar_t* str, size_t& length)
{
	length = wcsnlen_s(str, length);
	wchar_t* convertedStr = new wchar_t[length + 1];
	memcpy(convertedStr, str, length * sizeof(wchar_t));
	convertedStr[length] = '\0';
	return convertedStr;
}

std::string Human::generateOutOfRangeMessage(size_t length, size_t index)
{
	std::stringstream errorMessage;
	errorMessage << "index is bigger than array length: index = "
		<< index
		<< ", length = "
		<< length;
	return errorMessage.str();
}