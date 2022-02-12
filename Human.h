#pragma once
#include <memory>
#include <unordered_map>

struct wcstring_comparer
{
	bool operator()(const wchar_t* left, const wchar_t* right) const;
};

struct wcstring_hasher
{
	size_t operator()(const wchar_t* wcstr) const;
};

enum class Gender : int8_t { MALE, FEMALE, UNKNOWN };
enum class Education : int8_t
{
	PRESCHOOL,
	PRIMARY_GENERAL,
	BASIC_GENERAL,
	FULL_GENERAL,
	PROFESSIONAL,
	UNDERGRADUATE,
	HIGH_BACHELOR,
	HIGH_SPECIALIST,
	HIGH_MASTER,
	HIGH_ASPIRANT,
	UNKNOWN
};

class Human
{
public:
	void setName(const wchar_t* name, size_t length);
	void setPatronymic(const wchar_t* patronymic, size_t length);
	void setLastName(const wchar_t* lastName, size_t length);
	void setAddress(const wchar_t* address, size_t length);

	void setName(const wchar_t* name);
	void setPatronymic(const wchar_t* patronymic);
	void setLastName(const wchar_t* lastName);
	void setAddress(const wchar_t* address);

	void setName(const std::wstring& name);
	void setPatronymic(const std::wstring& patronymic);
	void setLastName(const std::wstring& lastName);
	void setAddress(const std::wstring& address);

	template <size_t length>
	void setName(const wchar_t(&name)[length]);
	template <size_t length>
	void setPatronymic(const wchar_t(&patronymic)[length]);
	template <size_t length>
	void setLastName(const wchar_t(&lastName)[length]);
	template <size_t length>
	void setAddress(const wchar_t(&address)[length]);

	void setEducation(Education Education);
	void setGender(Gender Gender);
	void setAge(int8_t age);

	std::unique_ptr<wchar_t[]> getName(size_t& length) const;
	std::unique_ptr<wchar_t[]> getPatronymic(size_t& length) const;
	std::unique_ptr<wchar_t[]> getLastName(size_t& length) const;
	std::unique_ptr<wchar_t[]> getAddress(size_t& length) const;

	std::unique_ptr<wchar_t[]> getName() const;
	std::unique_ptr<wchar_t[]> getPatronymic() const;
	std::unique_ptr<wchar_t[]> getLastName() const;
	std::unique_ptr<wchar_t[]> getAddress() const;

	Education getEducation() const;
	Gender getGender() const;
	uint8_t getAge() const;

	void showName() const;
	void showPatronymic() const;
	void showLastName() const;
	void showAddress() const;
	void showEducation() const;
	void showGender() const;
	void showAge() const;

	Human();
	Human(const std::wstring& lastName, const std::wstring& name, const std::wstring& patronymic,
		const std::wstring& address, const Education education, const Gender gender, const short age);
	Human(const wchar_t* lastName, const wchar_t* name, const wchar_t* patronymic,
		const wchar_t* address, const Education education, const Gender gender, const short age);
	Human(const wchar_t* lastName, const size_t nameLength, const wchar_t* name, const size_t patronymicLength, const wchar_t* patronymic, const size_t lastNameLength,
		const wchar_t* address, const size_t addressLength, const Education education, const Gender gender, const short age);
	template<size_t nameLength, size_t patronymicLength, size_t lastNameLength, size_t addressLength>
	Human(const wchar_t(&lastName)[lastNameLength], const wchar_t(&name)[nameLength], const wchar_t(&patronymic)[patronymicLength],
		const wchar_t(&address)[addressLength], const Education education, const Gender gender, const short age);
	Human(const Human& human);
	~Human();

	static void insertHuman(Human**& humans, size_t length, const Human* human, size_t index);
	static void insertHuman(Human*& humans, size_t length, const Human* human, size_t index);
	static void deleteHuman(Human**& humans, size_t length, size_t index);
	static void deleteHuman(Human*& humans, size_t length, size_t index);

	static std::list<Human*> getHumansWithAgeBiggerThan(Human** humans, size_t length, short age);
	static std::list<Human> getHumansWithAgeBiggerThan(Human* humans, size_t length, short age);
	static std::list<Human*> getHumansWithHighEducation(Human** humans, size_t length);
	static std::list<Human> getHumansWithHighEducation(Human* humans, size_t length);
	static std::list<Human*> getHumansWithGender(Human** humans, size_t length, Gender gender);
	static std::list<Human> getHumansWithGender(Human* humans, size_t length, Gender gender);

protected:

	wchar_t* validateAndConvertStr(const wchar_t* str, size_t& length);
	static std::string generateOutOfRangeMessage(size_t length, size_t index);

private:
	uint8_t age_;
	Education Education_;
	Gender Gender_;
	size_t nameLength_;
	size_t patronymicLength_;
	size_t lastNameLength_;
	size_t addressLength_;

	wchar_t* name_;
	wchar_t* patronymic_;
	std::shared_ptr<wchar_t[]> lastName_;
	std::shared_ptr<wchar_t[]> address_;

	static std::unordered_map<wchar_t*, size_t, wcstring_hasher, wcstring_comparer> names_;
	static std::unordered_map<wchar_t*, size_t, wcstring_hasher, wcstring_comparer> patronymics_;
};

template <size_t length>
void Human::setName(const wchar_t(&name)[length])
{
	setName(const_cast<wchar_t*>(name), length);
}

template <size_t length>
void Human::setPatronymic(const wchar_t(&patronymic)[length])
{
	setPatronymic(const_cast<wchar_t*>(patronymic), length);
}

template <size_t length>
void Human::setLastName(const wchar_t(&lastName)[length])
{
	setLastName(const_cast<wchar_t*>(lastName), length);
}

template <size_t length>
void Human::setAddress(const wchar_t(&address)[length])
{
	setAddress(const_cast<wchar_t*>(address), length);
}

template<size_t nameLength, size_t patronymicLength, size_t lastNameLength, size_t addressLength>
Human::Human(const wchar_t(&lastName)[lastNameLength], const wchar_t(&name)[nameLength], const wchar_t(&patronymic)[patronymicLength],
	const wchar_t(&address)[addressLength], const Education education, const Gender gender, const short age)
{
	setName(const_cast<wchar_t*>(name), nameLength);
	setPatronymic(const_cast<wchar_t*>(patronymic), patronymicLength);
	setLastName(const_cast<wchar_t*>(lastName), lastNameLength);
	setAddress(const_cast<wchar_t*>(address), addressLength);
	setEducation(education);
	setGender(gender);
}

