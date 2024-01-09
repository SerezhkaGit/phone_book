#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class phone_book
{
private:
    struct data
    {
        char* PIB{ new char[100] };
        char* home_phone{ new char[20] };
        char* work_phone{ new char[20] };
        char* mobile_phone{ new char[20] };
    };

    int size = 0;
    data* arr = nullptr;

public:
    phone_book()
    {
        cout << "\nWelcome ;D\nThe phone book";
    }
    void fil_data(data*& arr, int i)
    {
        cout << "\nEnter your full name: ";
        cin.ignore(256, '\n');
        cin.getline(arr[i].PIB, 100);

        cout << "\nEnter your home phone: ";
        cin.getline(arr[i].home_phone, 20);

        cout << "\nEnter your work phone: ";
        cin.getline(arr[i].work_phone, 20);

        cout << "\nEnter your mobile phone: ";
        cin.getline(arr[i].mobile_phone, 20);
       
    }

    void display(int i)
    {
        cout << "\n---------- Account " << i + 1 << "----------";
        cout << "\n User PIB is: " << arr[i].PIB;
        cout << "\n Home phone: " << arr[i].home_phone;
        cout << "\n Work phone: " << arr[i].work_phone;
        cout << "\n Mobile phone: " << arr[i].mobile_phone;
        cout << "\n-----------------------------" << endl;
    }

    void show_data()
    {
        for (int i = 0; i < size; i++)
        {
            display(i);
        }
    }

    void add_account()
    {
        int new_size = size + 1;
        data* tmp = new data[new_size];

        for (int i = 0; i < size; i++)
        {
            tmp[i] = arr[i];
        }

        fil_data(tmp, size);

        delete[] arr;
        arr = tmp;
        size = new_size;
    }

    void delete_account()
    {
        if (size == 0)
        {
            cout << "\nNo accounts to delete." << endl;
            return;
        }

        int new_size = size - 1;
        data* tmp = new data[new_size];

        int number;
        cout << "\nEnter the account number you want to delete: ";
        cin >> number;

        for (int i = 0, j = 0; i < new_size; i++, j++)
        {
            if (j == number - 1)
            {
                j++;
            }
            tmp[i] = arr[j];
        }

        delete[] arr;
        arr = tmp;
        size = new_size;
    }

    void search()
    {
        char* pib{ new char[100] };
        cout << "\nEnter account's PIB you're looking for: ";
        cin.ignore(256, '\n');
        cin.getline(pib, 100);

        bool found = false;

        for (int i = 0; i < size; i++)
        {
            if (strcmp(pib, arr[i].PIB) == 0)
            {
                display(i);
                found = true;
                break;
            }
        }

        if (!found)
        {
           cout << "\nSorry, but we didn't find such account :(";
        }

        delete[] pib;
    }

    void safe_to_file(const char* path)
    {
        ofstream fout;
        fout.open(path);
        if (!fout.is_open())
        {
            cout << "The file wasn't opened :(";
        }
        else 
        {
            for (int i = 0; i < size; i++)
            {
                fout << "\nAccount " << i+1 << ": " << arr[i].PIB << ',' << arr[i].home_phone << ',' << arr[i].mobile_phone << ',' << arr[i].work_phone << endl;
            }
            cout << "\nThe information was added to file successufully";
        }
        fout.close();
    }

    void load_from_file(const char* path)
    {
        ifstream fin;
        fin.open(path);

        delete[] arr;
        size = 0;

        if (!fin.is_open())
        {
            cout << "\nThe file wasn't opened";
        }
        else 
        {
            while (fin)
            {
                data entry;
                fin.getline(entry.PIB, 100, ',');
                fin.getline(entry.home_phone, 20, ',');
                fin.getline(entry.work_phone, 20, ',');
                fin.getline(entry.mobile_phone, 20, '\n');

                if (fin)
                {
                    size++;
                    data* tmp = new data[size];
                    for (int i = 0; i < size - 1; i++)
                    {
                        tmp[i] = arr[i];
                    }
                    tmp[size - 1] = entry;

                    delete[] arr;
                    arr = tmp;
                }
            }
            cout << "\nThe information was dowloaded successufully";
            fin.close();
        }
    }

    ~phone_book()
    {
        for (int i = 0; i < size; i++)
        {
            delete[] arr[i].PIB;
            delete[] arr[i].home_phone;
            delete[] arr[i].work_phone;
            delete[] arr[i].mobile_phone;
        }
        delete[] arr;
    }
};

int main()
{
    phone_book k;

    bool l = true;
    int num;
    while (l)
    {
        cout << "\n\nEnter 1 to leave the program";
        cout << "\nEnter 2 to add account";
        cout << "\nEnter 3 to show account";
        cout << "\nEnter 4 to delete account";
        cout << "\nEnter 5 to search the account";
        cout << "\nEnter 6 to safe infirmation to file";
        cout << "\nEnter 7 to load infirmation from file" << endl;
        cin >> num;

        if (num == 1)
        {
            l = false;
        }
        else if (num == 2)
        {
            k.add_account();
        }
        else if (num == 3)
        {
            k.show_data();
        }
        else if (num == 4)
        {
            k.delete_account();
        }
        else if (num == 5)
        {
            k.search();
        }
        else if (num == 6)
        {
            const char* path = "MyFile.txt";
            k.safe_to_file(path);
        }
        else if (num == 7)
        {
            const char* path = "MyFile.txt";
            k.load_from_file(path);
        }
    }

    return 0;
}



