#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <limits>
#include <fstream>
// struct for the projects
struct Student
{
    std::string name;
    int ID;
};
// save && load file from HDD
void saveToFile(const std::vector<Student> &students);
void loadFromFile(std::vector<Student> &students);
// decoration
void loading(std::string message);
// usable fucntion
// this fuction allow user to modify the info
void addStudent(std::vector<Student> &students);
void removeStudent(std::vector<Student> &students);
void updateStudent(std::vector<Student> &students);
// Menu that ask for user to choose sort by name or ID
void showStudentMenu(std::vector<Student> &students);
// this is use to show student after the user choose which method to show
void showStudent(const std::vector<Student> &students);
void searchStudent(std::vector<Student> &students);
// auto fuction
int generateID(std::vector<Student> &students);
int findById(const std::vector<Student> &students, int id);

int main()
{
    std::vector<Student> students;
    loadFromFile(students); 
    srand(time(0)); // use this to get a random number must be in the main function

    int choice;
    do
    {
        std::cout << std::setw(10) << std::string(6, '>') << " Menu " << std::string(6, '<') << std::endl;
        std::cout << '\n';
        std::cout << std::setw(6) << " 1.Add Student\n 2.Remove Student\n 3.Show Student\n 4.Search Student\n 5.Update student\n 6.Exit!\n ";
        std::cout << std::setw(4) << "==>" << " Option: ";
        if (!(std::cin >> choice))
        {
            std::cout << "Invalid! Please enter a number" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
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
            showStudentMenu(students);
            break;
        case 4:
            searchStudent(students);
            break;
        case 5:
            updateStudent(students);
            break;
        case 6:
        saveToFile(students); 
            std::cout << "Have a nice day!" << std::endl;
            loading("Exiting program");
        }

    } while (choice != 6);

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
// declaration for the auto fucntion(generate ID for student)
int generateID(std::vector<Student> &students)
{
    int id;
    do
    {
        id = rand() % 9000 + 1000;
    } while (findById(students, id) != -1);
    return id;
}

// declaration for the usable fucntion
// add student
void addStudent(std::vector<Student> &students)
{
    Student ask_for;
    std::cout << std::setw(10) << std::string(6, '>') << " Add Student " << std::string(6, '<') << std::endl;
    std::cout << "\n";
    std::cout << "Enter your name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, ask_for.name);
    ask_for.ID = generateID(students);
    students.push_back(ask_for);
    std::cout << '\n';
    loading("Adding student");
    std::cout << '\n';
    std::cout << ask_for.name << " has been added to the system!" << std::endl;
    std::cout << "Student ID: " << ask_for.ID << std::endl;
}
// remove student
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
    }
    else
    {
        std::cout << "Student ID " << id << " not found!" << std::endl;
    }
}

// Menu
void showStudentMenu(std::vector<Student> &students)
{
    if (students.empty())
    {
        std::cout << "Currently! There is no student to show." << std::endl;
        return;
    }
    int choice;
    do
    {
        std::cout << std::setw(10) << std::string(6, '>') << " Show Student " << std::string(6, '<') << std::endl;
        std::cout << std::setw(5) << " 1. Sort By name\n 2. Sort By ID\n 3. Exit!\n";
        std::cout << std::setw(2) << "==> Option:";
        if (!(std::cin >> choice))
        {
            std::cout << "Invalid! choice." << std::endl;
            return;
        }
        else
        {
            switch (choice)
            {
            case 1:
                std::sort(students.begin(), students.end(), [](Student a, Student b)
                          { return a.name < b.name; });
                showStudent(students);
                break;
            case 2:
                std::sort(students.begin(), students.end(), [](Student a, Student b)
                          { return a.ID < b.ID; });
                showStudent(students);
                break;
            case 3:
                loading("Exiting");
                std::cout << "\n";
                break;
            }
        }
    } while (choice != 3);
}
void showStudent(const std::vector<Student> &students)
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
        std::cout << std::endl;
    }
    std::cout << "Total Students: " << students.size() << std::endl;
    std::cout << std::string(50, '-');
    std::cout << std::endl;
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
        std::cout << std::left << std::setw(15) << students[index].name << std::setw(10) << students[index].ID << std::endl;
    }
    else
    {
        std::cout << "Student " << id << " not found!" << std::endl;
    }
}
int findById(const std::vector<Student> &students, int id)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i].ID == id)
        {
            return i;
        }
    }
    return -1;
}
void updateStudent(std::vector<Student> &students)
{
    int id;
    std::cout << std::setw(10) << std::string(6, '>') << " Update Student " << std::string(6, '<') << std::endl;
    std::cout << "\n";
    if (students.empty())
    {
        std::cout << "Currently there is no student avialable" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cout << "Enter ID: ";
    std::cin >> id;
    int index = findById(students, id);
    if (index != -1)
    {

        std::string old_name = students[index].name;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        loading("Finding student");
        std::cout << "Student found: " << old_name << std::endl;
        std::cout << "Enter new name: ";
        getline(std::cin, students[index].name);
        std::cout << old_name << " has been updated to " << students[index].name << std::endl;
    }
    else
    {
        std::cout << "Student not found!" << std::endl;
    }
}
// declaration for the save && load file
void saveToFile(const std::vector<Student> &students)
{
    

    std::ofstream save_file("student.txt");
    if (!save_file)
    {
        std::cout << "Error cannot find file!" << std::endl;
        return;
    }
    for (size_t i = 0; i < students.size(); i++)
    {
        save_file<< students[i].name << "," << students[i].ID << std::endl;
    }
    save_file.close();
}
void loadFromFile(std::vector<Student> &students)
{
    std::ifstream load_file("student.txt");
    if (!load_file)
    {
        return;
    }
    std::string search_for_file;
    while (getline(load_file, search_for_file))
    {
        Student s;
        size_t commaPos = search_for_file.find(',');
        s.name = search_for_file.substr(0, commaPos);
        s.ID = std::stoi(search_for_file.substr(commaPos + 1));
        students.push_back(s);
    }
    load_file.close();
}