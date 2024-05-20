#pragma once

#include<fstream>

using namespace std;

class Account {
public:
	Account() = default;
	~Account() = default;
	
	void account_set(string account,string password) {
		this->account = account;
		this->password = password;
		this->max_score = 0;
	}
	void update_score(int new_score) {
		if (new_score > max_score)
			max_score = new_score;
	}
	int get_score() const {
		return max_score;
	}
	string get_account() {
		return account;
	}
	bool operator == (const string& acc) {
		return this->account == acc;
	}
	bool operator==(const Account& acc) {
		return this->account == acc.account && this->password == acc.password;
	}
	friend istream& read(istream& is, Account& acc);
	friend ostream& print(ostream& os, const Account& acc);
private:
	string account{};
	string password{};
	int max_score = 0;
};

istream& read(istream& is, Account& acc) {
	is >> acc.account >> acc.password >> acc.max_score;
	return is;
}
ostream& print(ostream& os, const Account& acc) {
	os << acc.account << ' ' << acc.password << ' ' << acc.max_score;
	return os;
}