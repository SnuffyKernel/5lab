#include <iostream>
#include <string>
#include <vector>

class Account {
public:
    std::string username;
    std::string password;

    std::string email;
    std::string phoneNumber;

    void showAccountInfo() const {
        std::cout << "Username: " << username << std::endl;
        std::cout << "Password: " << password << std::endl;
        if (!email.empty()) std::cout << "Email: " << email << std::endl;
        if (!phoneNumber.empty()) std::cout << "Phone Number: " << phoneNumber << std::endl;
    }
};

class AccountBuilder {
protected:
    Account account;

public:
    virtual void setUsername(const std::string& username) = 0;
    virtual void setPassword(const std::string& password) = 0;
    virtual void setEmail(const std::string& email) = 0;
    virtual void setPhoneNumber(const std::string& phoneNumber) = 0;
    virtual Account getAccount() const = 0;
};

class ConcreteAccountBuilder : public AccountBuilder {
    bool hasSetUsername = false;
    bool hasSetPassword = false;
public:
    void setUsername(const std::string& username) override {
        account.username = username;
        hasSetUsername = true;
    }
    void setPassword(const std::string& password) override {
        account.password = password;
        hasSetPassword = true;
    }

    void setEmail(const std::string& email) override {
        account.email = email;
    }

    void setPhoneNumber(const std::string& phoneNumber) override {
        account.phoneNumber = phoneNumber;
    }

    Account getAccount() const override {
        if (!hasSetUsername || !hasSetPassword) {
            throw std::runtime_error("Username and password are required");
        }
        return account;
    }
};

class AccountManager {
private:
    std::vector<Account> accounts;

public:
    void addAccount(const Account& account) {
        accounts.push_back(account);
    }

    void removeAccount(const std::string& username) {
        auto it = std::remove_if(accounts.begin(), accounts.end(),
            [username](const Account& acc) { return acc.username == username; });
        accounts.erase(it, accounts.end());
    }

    void showAllAccounts() const {
        for (const auto& account : accounts) {
            account.showAccountInfo();
            std::cout << "------------------------\n";
        }
    }
};

int main() {
    ConcreteAccountBuilder builder1;
    builder1.setUsername("user123");
    builder1.setPassword("password123");
    builder1.setEmail("user123@gmail.ru");
    builder1.setPhoneNumber("+574902357809");
    Account user1Account = builder1.getAccount();

    ConcreteAccountBuilder builder2;
    builder2.setUsername("Snuffy");
    builder2.setPassword("12345");
    builder2.setEmail("snuffy@mail.com");
    builder2.setPhoneNumber("+839759876");
    Account user2Account = builder2.getAccount();

    ConcreteAccountBuilder builder3;
    builder3.setUsername("Yu");
    builder3.setPassword("567807");
    Account user3Account = builder3.getAccount();

    AccountManager accountManager;
    accountManager.addAccount(user1Account);
    accountManager.addAccount(user2Account);
    accountManager.addAccount(user3Account);

    accountManager.showAllAccounts();

    std::cout <<std::endl <<"Delet Account: user123" << std::endl << std::endl;
    std::cout << "------------------------" <<std::endl;
    accountManager.removeAccount("user123");


    accountManager.showAllAccounts();

    return 0;
}