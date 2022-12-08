#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iomanip>
using namespace std;

struct Student
{
    string firstName;
    string lastName;
    string ID;
    double TestScores[6];
    double QuizScore;
    char grade;
    double Average = 0;
    double Averagequiz = 0;
    double Averagetest = 0;
};

void openFile(ifstream& sin, string& filename)
{
    cin >> filename;
    sin.open(filename);
    if (sin.fail())
    {
        cout << "Failed to open file.";
        exit(0);
    }
    if (sin.eof())
    {
        cout << "Empty file.";
        exit(0);
    }
}

void readList(ifstream& bin, string& coursename, string& courseid, string& location, struct Student std[50], int& count)
{

    int i, j;

    getline(bin, coursename);
    getline(bin, courseid);
    getline(bin, location);

    for (i = 0; i < 50; i++) {
        if (!bin.eof()) {
            count++;
            bin >> std[i].firstName;
            getline(bin, std[i].lastName);

            bin >> std[i].ID;
            bin >> std[i].QuizScore;
            for (j = 0; j < 5; j++)
            {
                bin >> std[i].TestScores[j];
            }
        }
        else
        {
            i = 50;
        }
    }
}

void processList(struct Student *std[50],int count)
{
    calcAverage(std[50],count);
    grade(std[50],count);
}

void calcAverage(struct Student std[50], int count)
{
    int j = 0;
    int i = 0;
    double testscore;
    double low = std[j].TestScores[0];
    for (i = 0; i < count; i++) {
        for (j = 0; j < 6; j++)
        {
            testscore = std[i].TestScores[j];
            if (testscore > 100 or testscore < 0)
            {
                std[i].Average = -1;
            }
            else if (low > testscore)
            {
                low = std[i].TestScores[j];
            }
            if (!std[i].Average == -1) {
                std[i].Averagetest = std[i].Average + std[i].TestScores[j];
            }
        }
        if (!std[i].Average == -1) {

            std[i].Averagetest = std[i].Average - low;
            std[i].Averagetest = (std[i].Average / 5) * .9;
            std[i].Averagequiz = std[i].QuizScore * .1;
            std[i].Average = std[i].Averagetest + std[i].Averagequiz;

        }
    }
}

void grade(struct Student std[50], int count)
{
    int i;
    for (i = 0; i < (count); i++)
    {
        if (std[i].Average <= 100 and std[i].Average >= 90)
        {
            std[i].grade = 'A';
        }else if (std[i].Average <= 89 and std[i].Average >= 80)
        {
            std[i].grade = 'B';
        }
        else if (std[i].Average <= 79 and std[i].Average >= 70)
        {
            std[i].grade = 'C';
        }
        else if (std[i].Average <= 69 and std[i].Average >= 60)
        {
            std[i].grade = 'D';
        }
        else if (std[i].Average <= 59 and std[i].Average >= 0)
        {
            std[i].grade = 'F';
        }
        else
        {
            std[i].grade = 'I';
        }
    }
}

void printToFile(int count, struct Student std[50], string& filename, string coursename, string courseid, string location)
{
    ofstream myfile;
    int i;

    myfile.open(filename);
    myfile << "Course Name:" << setw(10) << coursename << endl;
    myfile << "Course ID:" << setw(10) << courseid << endl;
    myfile << "Course Location:" << setw(10) << location << endl;
    myfile << "Name" << setw(10) << "ID" << "Average" << "Grade" << endl;

    for (i = 0; i < count; i++) {
        myfile << std[i].lastName << ", " << std[i].firstName << setw(10) << std[i].ID << setw(10) << std[i].Average << setw(10) << std[i].grade;
    }
    myfile.close();
}

void search(int count, struct Student std[50])
{
    int j,i;
    string search;
    cout << "Write the last name of the student you are looking for"<<endl;
    cin >> search;
    for (j=0;j<count;j++) 
    {
        if (search == std[j].lastName) 
        {
            cout << "Name:"<<setw(10)<<std[j].lastName<<", "<<std[j].firstName;
            cout << endl << "ID:" << setw(10) << std[j].ID<<endl;
            cout << "Quiz Score:"<<setw(10)<<fixed<<setprecision(2)<<std[j].QuizScore<<endl;
            for (i=0;i<6;i++) 
            {
                cout << fixed << setprecision(2)<<std[j].TestScores[i]<<setw(10);
            }
            cout << endl<<"Average:"<<setw(10)<< std[j].Average<<endl<<"Letter Grade:"<<setw(10)<<std[j].grade;
        }
        else 
        {
            cout << "No one with that last name is one the list";
        }
    }
}

void addStudent(int &count, struct Student std[50])
{
    ++count;
    cout << "What is the name of the new Student?" << endl; 
    cin >> std[(count)].firstName>>std[count].lastName;
    cout << "Student ID?"<<endl;
    cin >> std[(count)].ID;
    cout<< "Quiz Scores?"<<endl;
    cin >> std[(count)].QuizScore;
    cout << "What are the six test scores";
    cin >> std[(count)].TestScores[0] >> std[(count)].TestScores[1] >> std[(count)].TestScores[2];
    cin >> std[(count)].TestScores[3] >> std[(count)].TestScores[4] >> std[(count)].TestScores[5];
}

void removeStudent(int count,struct Student std[50])
{
    int j,i;
    string search;

    string FirstName = std[count].firstName;
    string LastName = std[count].lastName;
    string iD = std[count].ID;
    double testScores[6];
    double quizScore = std[count].QuizScore;
    char grade = std[count].grade;
    double average = std[count].Average;
    double averagequiz = std[count].Averagequiz;
    double averagetest = std[count].Averagetest;
    for (i = 0; i < 6; i++) 
    {
        testScores[i] = std[count].TestScores[i];
    }

    cout << "What is the last name of the student you want to remove?"<<endl;
    cin >> search;
    for (j = 0; j < count; j++) 
    {
        if (search == std[j].lastName) 
        {
            std[count].firstName = std[j].firstName;
            std[count].lastName = std[j].lastName;
            std[count].ID = std[j].ID;
            for (i = 0; i < 6; i++)
            {
                std[count].TestScores[i] = std[j].TestScores[i];
            }
            std[count].QuizScore = std[j].QuizScore;
            std[count].grade = std[j].grade;
            std[count].Average = std[j].Average;
            std[count].Averagequiz = std[j].Averagequiz;
            std[count].Averagetest = std[j].Averagetest;

            std[j].firstName = FirstName;
            std[j].lastName = LastName;
            std[j].ID = iD;
            for (i = 0; i < 6; i++)
            {
                std[j].TestScores[i] = testScores[i];
            }
            std[j].QuizScore = quizScore;
            std[j].grade = grade;
            std[j].Average = average;
            std[j].Averagequiz = averagequiz;
            std[j].Averagetest = averagetest;
            --count;
        }
        else 
        {
            cout << std[j].lastName << " is on the list.(" << std[j].lastName << "is the student we are trying to remove or find)";
        }
    }
}
void sortName(int count) 
{
    int j;
    for (j = 0; j < count; j++) 
    {
    
    }
}
void printToMonitor()
{ 

}

int main() {
    ifstream fin;
    string file;
    string coursename, courseid, location;
    struct Student *std[50];
        int count;
    // Calls in the main must be in the following form for the tests to pass
    openFile(fin, file);
    readList(fin, coursename, courseid, location, std[50], count);
    //processList();
    // printToFile();
     //search();
     //addStudent();
     //removeStudent();
     //printToMonitor();
     //sortName();
     //printToMonitor();
    

    return 0;
}
