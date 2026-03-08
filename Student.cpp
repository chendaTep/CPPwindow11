#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <limits>
// struct for the projects
struct Student
{
    std::string name;
    int ID;
};
// decoration
void loading(std::string message);
// usable fucntion
void addStudent(std::vector<Student> &students);
void removeStudent(std::vector<Student> &students);
void sortByName(std::vector<Student> &students);
void sortById(std::vector<Student> &stduents);
void showStudent(const std::vector<Student> &students);
void searchStudent(std::vector<Student> &students);
// auto fuction
int generateID(std::vector<Student> &students);
int findById(const std::vector<Student> &students, int id);

int main()
{
    std::vector<Student> students;
    srand(time(0)); // use this to get a random number must be in the main function 
    int choice;
    do
    {
        std::cout << std::setw(10) << std::string(6, '>') << " Menu " << std::string(6, '<') << std::endl;
        std::cout << '\n';
        std::cout << std::setw(6) << " 1.Add Student\n 2.Remove Student\n 3.Sort by Name\n 4.Sort by ID\n 5.Show Student\n 6.Search Student\n 7.Exit!\n ";
        std::cout << std::setw(4) << "==>" << " Option: ";
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!(std::cin >> choice))
        {
            std::cout << "Invalid! Please enter a number" << std::endl;
            return 0;
        }
        switch (choice)
        {
        case 1:
            addStudent(students);
            break;
        case 2:
            removeStudent(students);
            break;
        case 3:
            sortByName(students);
            break;
        case 4:
            sortById(students);
            break;
        case 5:
            showStudent(students);
            break;
        case 6:
            searchStudent(students);
            break;
        case 7:
            std::cout << "Have a nice day!" << std::endl;
            loading("Exiting program");
        }

    } while (choice != 7);

    return 0;
}
// declaration for the decoration
void loading(std::string message)
{
    std::string frame[] = {".", "..", "..."};
    for (int i = 0; i < 9; i++)
    {
        std::cout << "\r" << message << frame[i % 3] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}
// declaration for the auto fucntion
int generateID(std::vector<Student> &students)
{
    return rand() % 9000 + 1000;
}

// declaration for the usable fucntion

void addStudent(std::vector<Student> &students)
{
    Student ask_for_name;
    std::cout << std::setw(10) << std::string(6, '>') << " Add Student " << std::string(6, '<') << std::endl;
    std::cout << "\n";
    std::cout << "Enter your name: ";
    std::cin.ignore();
    getline(std::cin, ask_for_name.name);
    ask_for_name.ID = generateID(students);
    students.push_back(ask_for_name);
    std::cout << '\n';
    loading("Adding student");
    std::cout << '\n';
    std::cout << ask_for_name.name << " has been added to the system!" << std::endl;
}
void removeStudent(std::vector<Student> &students)
{
    int id;
    if (students.empty())
    {
        std::cout << "Currently! There is no student to remove!" << std::endl;
        return;
    }
    std::cout << std::setw(10) << std::string(6, '>') << " Remove student " << std::string(6, '<') << std::endl;
    std::cout << "\n";
    std::cout << "Enter ID :";
    std::cin >> id;
    int index = findById(students, id);

    if (index != -1)
    {
        std::string confirm_delete;
        bool check_input = false;

        while (!(check_input))
        {
            std::cout << "Are you sure to delete student name " << students[index].name << " ? (yes/no)" << std::endl;
            std::cin >> confirm_delete;
            if (confirm_delete == "y" || confirm_delete == "Y" || confirm_delete == "yes" || confirm_delete == "Yes" || confirm_delete == "YES" || confirm_delete == "n" || confirm_delete == "No" || confirm_delete == "no" || confirm_delete == "NO" || confirm_delete == "N")
            {
                check_input = true;
            }
            else
            {
                std::cout << "Invalid! Only possible choice either yes or no!!" << std::endl;
            }
        }
        if (confirm_delete == "y" || confirm_delete == "Y" || confirm_delete == "yes" || confirm_delete == "Yes" || confirm_delete == "YES")
        {
            std::cout << students[index].name << " has been removed from the system!" << std::endl;
            students.erase(students.begin() + index);
        }
        else
        {
            std::cout << "Canceled!" << std::endl;
        }
    } else {std::cout<<"Student ID " << id << " not found!" << std::endl; }
} 
void sortByName(std::vector<Student> &students)
{
    std::sort(students.begin(), students.end(), [](Student a, Student b)
              { return a.name < b.name; });
}
void sortById(std::vector<Student> &students)
{
    std::sort(students.begin(), students.end(), [](Student a, Student b)
              { return a.ID < b.ID; });
}
void showStudent(const std::vector<Student> &students)
{

    if (students.empty())
    {
        std::cout << "Currently! There is no student to show." << std::endl;
        return;
    }
    else
    {
        std::cout << std::setw(10) << std::string(6, '>') << " Students Display " << std::string(6, '<') << std::endl;
        std::cout << '\n';
        // header
        std::cout << std::left << std::setw(5) << "" << std::setw(35) << "Name" << std::setw(10) << "ID" << std::endl;
        std::cout << std::string(50, '-');
        std::cout << "\n";
        for (size_t i = 0; i < students.size(); i++)
        {
            std::cout << std::left << std::setw(5) << (std::to_string(i + 1) + ".") << std::setw(35) << students[i].name << std::setw(10) << students[i].ID << std::endl;
        }
    }
}
void searchStudent(std::vector<Student> &students)
{
    std::cout << std::setw(10) << std::string(6, '>') << " Search for student " << std::string(6, '<') << std::endl;
    std::cout << "\n";
    std::cout << "Enter ID to search: ";
    int id;

    std::cin >> id;

    int index = findById(students, id);
    if (index != -1)
    {
        loading("Finding student");
        std::cout << std::endl;
        std::cout << "Student found!" << std::endl;
        std::cout << std::left   << std::setw(15) << students[index].name << std::setw(10) << students[index].ID << std::endl;
} } 
int findById(const std::vector<Student> &students, int id)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].ID == id)
        {
            return i;
        }
    }
    return -1;
}