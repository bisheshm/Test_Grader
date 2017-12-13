// Author:        Bishesh Manandhar
// Course:        CS 1336.003
// Date:          12/2/2017
// Assignment:    Lecture Homework 9 Exercise 2
// Compiler:      Visual Studio C++ 2017

// Description:   This program will check student answers with a answer key and print out a student report for every student.

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Function Prototypes
int checkAnswers(char correctAnswers[], char studentAnswers[], int numElements);
void checkQuestions(char correctAnswers[], char studentAnswers[], int numElements, ofstream&outfile);

// Main function
int main()
{
   // Constant function for array sizes
   const int SIZE_CORRECTANS = 20,  // Correct size for correct answers array
      SIZE_STUDENT = 220,           // Size of student answers
      SIZE_GRADES = 11;             // Number of students

   // Arrays for answers
   char correctAnswers[SIZE_CORRECTANS];     // Correct answer array
   char studentAnswers[SIZE_STUDENT];        // Student answer array

   // Array to hold grades for each student
   int grades[SIZE_GRADES];

   // Int variables for calculations
   int countCorrect = 0,      // Count correct answers
      countStudent = 0,       // Count student answers
      missedQuestions,        // Number of missed questions
      lowest,                 // Lowest grade
      highest,                // Highest grade
      correctNum,             // How many student got correct
      numStudents,            // Number of students
      person,                 // Individual student
      percent;                // Percent grade

   // Opening correct answers file
   ifstream correctAnswersFile;
   correctAnswersFile.open("CorrectAnswers.txt");

   // Opening student answers file
   ifstream studentAnswersFile;
   studentAnswersFile.open("StudentAnswers.txt");

   // Output error message if files opened incorrectly
   if ((!correctAnswersFile) || (!studentAnswersFile))
   {
      cout << "One or more of the files was opened incorrectly." << endl;
   }
   // Else, proceed with program
   else
   {
      // Reading data into correct answers array from input file
      while (correctAnswersFile >> correctAnswers[countCorrect] && countCorrect < SIZE_CORRECTANS)
      {
         countCorrect++;
      }
      // Close correct answers file
      correctAnswersFile.close();

      // Reading data into student answers array from input file
      while (studentAnswersFile >> studentAnswers[countStudent] && countStudent < SIZE_STUDENT)
      {
         countStudent++;
      }
      // Close student answers file
      studentAnswersFile.close();

      // Opening output file
      ofstream outfile;
      outfile.open("ExamAnalysis.txt");

      // If output file was not opened correctly, display error message
      if (!outfile)
      {
         cout << "The output file for the exam analysis was not opened correctly." << endl;
      }
      // Else proceed with program
      else
      {
         // For all of the students, calculate report
         for (numStudents = 0; numStudents < SIZE_STUDENT / 20; numStudents++)
         {
            // Call missed questions function
            missedQuestions = checkAnswers(correctAnswers, studentAnswers, SIZE_CORRECTANS);

            // Get correc number of questions using num of missed questions
            correctNum = 20 - missedQuestions;
            
            // Calculate percent
            percent = (static_cast <double> (correctNum) / 20) * 100;

            // Input percent into grades array
            grades[numStudents] = percent;

            // Output to outfile report
            outfile << "Report for Student " << numStudents + 1 << endl;
            outfile << "---------------------" << endl;
            outfile << "Missed " << missedQuestions << " out of 20 questions for " << percent << "%" << " correct." << endl;

            // Continue output the questions missed by calling checkQuestions
            outfile << "Questions missed:" << endl;
            outfile << "   ";
            checkQuestions(correctAnswers, studentAnswers, SIZE_CORRECTANS, outfile);

            // Checking if student passed exam
            if (percent >= 70)
            {
               outfile << "This student passed the exam!" << endl;
            }
            // Checking if student failed exam
            else if (percent < 70)
            {
               outfile << "This student failed the exam." << endl;
            }
            outfile << endl << endl;
         }

         // Creating variables for highest and person with highest score
         highest = 0;
         person = 0;

         // Loop to find highest score in grades array
         for (int count = 0; count < SIZE_STUDENT / 20; count++)
         {
            if (grades[count] > highest)
            {
               highest = grades[count];
               person = count + 1;
            }
         }

         // Ouputting student with highest score
         outfile << "Student " << person << " had the best grade with " << grades[person - 1] << "%" << endl;

         // Variables for lowest score and person with lowest score
         lowest = 101;
         person = 0;

         // Loop to find lowest score in grades array
         for (int count = 0; count < SIZE_STUDENT / 20; count++)
         {
            if (grades[count] < lowest)
            {
               lowest = grades[count];
               person = count + 1;
            }
         }

         // Output student with worst grade
         outfile << "Student " << person << " had the worst grade with " << grades[person - 1] << "%" << endl;
         // Close output file
         outfile.close();
      }
   }
   cout << endl;
   system("pause");
   return 0;
}     // End of function main()


/********************************************************************************************
Function:   int checkAnswers(char correctAnswers[], char studentAnswers[], int numElements) *
Descr:      This function will check the 20 answers of the student and compare it with the  * 
            20 correct answers. It will count every missed question, and return the total   *
            number of missed questions as an int. It will do this by looping through        *
            the correct answers array and checking to see the values of ouput at the index  *
            of each array. An if statement is then used to see whether or not those values  *
            match or not.                                                                   *
Input:      char correctAnswers[], char studentAnswers[], int numElements                   *
Return:     int wrong - number of missed questions                                          *
********************************************************************************************/
int checkAnswers(char correctAnswers[], char studentAnswers[], int numElements)
{
   // Creating static int variable to process through student answers
   static int currentQuestion = 0;

   // Creating variables for wrong answers and a counter
   int wrong = 0;

   // Looping through every element in correct answer array to see if student answer is correct
   for (int x = 0; x < numElements; x++)
   {
      // If it is not correct, then increment wrong by one
      if (studentAnswers[currentQuestion] != correctAnswers[x])
      {
         wrong++;
      }
      currentQuestion++;
   }
   // Return number of wrong questions
   return wrong;
}     // End of function checkAnswers


/*******************************************************************************************************************
Function:   void checkQuestions(char correctAnswers[], char studentAnswers[], int numElements, ofstream&outfile)   *
Descr:      This function will go through every element in the correct answer array and check it with the student  *
            answers. If the student answer is not equal to the correct answer, then it will output the question    *
            number missed, along with the correct answer. It will do this by using the index values of the correct *
            and student answer arrays. The number of question is the index plus one because the index number of an *
            array starts at 0, while the exam starts at question 1.                                                *
Input:      char correctAnswers[], char studentAnswers[], int numElements, ofstream&outfile                        *
Return:     Void function that will print out thw question missed, incorrect answer, and correct answer.           *
*******************************************************************************************************************/
void checkQuestions(char correctAnswers[], char studentAnswers[], int numElements, ofstream&outfile)
{
   // Creating count variable to modify output later
   int count = 0;

   // Static int variable to process through student answers
   static int currentQuestion = 0;

   // Checking to see if question was missed or not
   for (int b = 0; b < numElements; b++)
   {
      // If question missed, output question number, student answer, and correct answer using indexes
      if (studentAnswers[currentQuestion] != correctAnswers[b])
      {
         outfile << (b + 1) << "(" << studentAnswers[currentQuestion] << "/" << correctAnswers[b] << "), ";
         count++;

         // Modifying output to 7 missed questions per line to make report look more appealing
         if (count % 7 == 0)
         {
            outfile << endl;
            outfile << "   ";
         }
      }
      currentQuestion++;
   }
   outfile << endl;
}     // End of function checkQuestions
