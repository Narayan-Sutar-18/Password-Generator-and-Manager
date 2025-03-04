#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

const int maxPasswords = 100;

class generate_password
{
protected:
    int length;
    string character_set = "#8@4z9$F3q&aR+d5Wv1k%7N!6UbKpV^2O|E=s6~Y?tj-Z_/i*X9GmS7D<;:LlT0oH,.IuQ>gJc^-@BfA&XwNjPq|y3vU*";
    string username, apl, gen_password;

public:
    generate_password(string u_name, string ap, int len)
    {
        username = u_name;
        apl = ap;
        length = len;
        generate_pass();
    }

    string generate_pass()
    {
        srand(time(0));
        gen_password = "";
        for (int i = 0; i < length; i++)
        {
            gen_password += character_set[rand() % character_set.length()];
        }

        return gen_password;
    }

    void display()
    {
        cout << "\nUsername: " << username << "\nApp/web name: " << apl << "\nGenerated password:  " << gen_password << endl;
    }

    string getUsername()
    {
        return username;
    }

    string getPassword()
    {
        return gen_password;
    }
};

class manage_password : public generate_password
{
public:
    manage_password() : generate_password("", "", 0) {}

    manage_password(string u_name, string ap, int len) : generate_password(u_name, ap, len) {}

    void save_password()
    {
        ofstream outfile("passwords.txt", ios::app);

        if (!outfile.is_open())
        {
            cout << "Error while opening file..." << endl;
        }
        else
        {
            outfile << apl << "\n";
            outfile << username << "\n";
            outfile << gen_password << "\n";
            cout << "Password saved successfully." << endl;
        }
        outfile.close();
    }

    void read_details()
    {
        ifstream infile("passwords.txt");

        if (!infile.is_open())
        {
            cout << "Error while opening file..." << endl;
        }
        else
        {
            string allPasswords;
			while (getline(infile, apl) && getline(infile, username) && getline(infile, gen_password))
            {
                 allPasswords += "Username: " + username + "\nPassword: " + gen_password + "\nApp/Website: " + apl + "\n\n";
            }
            cout << allPasswords;
        }
        infile.close();
    }

    bool search_password(string searchUsername, string &foundPassword)
    {
        ifstream infile("passwords.txt");

        if (!infile.is_open())
        {
            cout << "Error while opening file..." << endl;
            return false;
        }
        else
        {
            while (getline(infile, apl) && getline(infile, username) && getline(infile, gen_password))
            {
                if (username == searchUsername)
                {
                    foundPassword = gen_password;
                    infile.close();
                    return true;
                }
            }
            infile.close();
            return false;
        }
    }
};

int main()
{
    manage_password passwords[maxPasswords];

    int n,i=0,choice;
    string user, a, searchUsername, foundPassword;

    cout << "1. Generate Password\n2. Get all passwords\n3. Search Password\n4. Exit" << endl;

    do
    {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nEnter your password username: ";
            cin >> user;
            cout << "\nEnter which Application/Website password is needed: ";
            cin >> a;
            cout << "\nEnter length of password (strong password if >=8 characters): ";
            cin >> n;

            passwords[i] = manage_password(user, a, n);
            //passwords[i].generate_pass();
            passwords[i].display();
            passwords[i].save_password();
            break;
        case 2:
            cout << "\nAll passwords are:" << endl;
            passwords[i].read_details();
            break;
        case 3:
			cout << "Enter the username to search: ";
            cin >> searchUsername;

            if (passwords[i].search_password(searchUsername, foundPassword))
            {
                cout << "Password found: " << foundPassword << endl;
            }
            else
            {
                cout << "Password not found." << endl;
            }
            break;
        case 4:
        	cout<<"\nSuccesfully Exited..."<<endl;
            exit(0);
        default:
            cout << "Invalid input" << endl;
        }
        i++;
    } while (choice != 4);

    return 0;
}
