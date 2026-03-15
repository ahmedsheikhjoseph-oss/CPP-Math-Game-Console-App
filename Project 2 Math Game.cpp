/*
Project: Math Quiz Game (C++)
Course: Programming Advices - Algorithms & Problem Solving Level 2
Purpose: Practice random number generation, structured programming, and logical branching.
By: [Ahmed Sheikh Aldeen Yusef]
*/

#include <iostream>  
#include <cstdlib>   
#include <ctime>     
#include <string>

using namespace std;

// Enums to manage difficulty and operations clearly
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

// Struct to store individual question data
struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

// Struct to store the overall quiz results and statistics
struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

// --- Function Prototypes ---
void SetScreenColor(bool Right);
int RandomNumber(int From, int To);
int SimpleCalculator(int Number1, int Number2, enOperationType OpType);
string GetQuestionLevelText(enQuestionsLevel QuestionLevel);
string GetOpTypeSymbol(enOperationType OpType);
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType);
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz);
string GetFinalResultsText(bool Pass);
void PrintQuizzResults(stQuizz Quizz);
enQuestionsLevel ReadQuestionsLevel();
enOperationType ReadOpType();
short ReadHowManyQuestions();
void PlayMathGame();
void ResetScreen();
void StartGame();

int main()
{
    // Seed random number generator with current time
    srand((unsigned)time(NULL));
    
    StartGame();
    
    return 0;
}

// Controls the main game loop and replay option
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();
        cout << "\nDo you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

// Clears the console and resets colors
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

// Orchestrates the quiz flow
void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();

    // Generation phase
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }

    // Execution phase
    AskAndCorrectQuestionListAnswers(Quizz);
    
    // Result phase
    PrintQuizzResults(Quizz);
}

// Input validation for number of questions
short ReadHowManyQuestions()
{
    short NumberOfQuestions;
    do
    {
        cout << "How Many Questions do you want to answer (1 to 10)? ";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionLevel = 0;
    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OpType;
    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;

    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

// Creates a question based on selected difficulty and operation
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    
    Question.QuestionLevel = QuestionLevel;

    if (OpType == enOperationType::MixOp)
        OpType = (enOperationType)RandomNumber(1, 4);
    
    Question.OperationType = OpType;

    // Set number ranges based on difficulty
    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

    return Question;
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

// Performs the actual calculation logic
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:  return Number1 + Number2;
    case enOperationType::Sub:  return Number1 - Number2;
    case enOperationType::Mult: return Number1 * Number2;
    case enOperationType::Div:  return (Number2 != 0) ? (Number1 / Number2) : 0; 
    default: return Number1 + Number2;
    }
}

// Interaction logic: Asks questions and updates statistics
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        cout << "\n--------------------------- Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] --------------------------------\n";

        cout << Quizz.QuestionList[QuestionNumber].Number1 << " " << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << " " << Quizz.QuestionList[QuestionNumber].Number2 << " = ";
        cin >> Quizz.QuestionList[QuestionNumber].PlayerAnswer;

        if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
        {
            Quizz.QuestionList[QuestionNumber].AnswerResult = true;
            Quizz.NumberOfRightAnswers++;
            cout << "\nRight Answer :-) \n";
        }
        else
        {
            Quizz.QuestionList[QuestionNumber].AnswerResult = false;
            Quizz.NumberOfWrongAnswers++;
            cout << "\nWrong Answer :-( \n";
            cout << "The right answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << "\n";
        }

        SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
    }

    // Logic to determine if user passed the quiz
    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:  return "+";
    case enOperationType::Sub:  return "-";
    case enOperationType::Mult: return "x";
    case enOperationType::Div:  return "/";
    default: return "Mix";
    }
}

// Changes visual feedback based on answer correctness
void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); // Green
    else
    {
        system("color 4F"); // Red
        cout << "\a";       // Beep sound
    }
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Results is " << GetFinalResultsText(Quizz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions    : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level        : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "Operation Type         : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";
}

string GetFinalResultsText(bool Pass)
{
    return (Pass) ? "PASS :-)" : "FAIL :-(";
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
    return arrQuestionLevelText[QuestionLevel - 1];
}
