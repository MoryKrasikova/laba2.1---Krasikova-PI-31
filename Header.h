﻿//файл заголовков
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
//класс для слова от компьютера
class word {
private:
    char* randomWord; // Указатель для хранения случайного слова
    int length; // Длина слова

public:
    // Конструктор
    word() : randomWord(nullptr), length(0) {}

    // Деструктор для освобождения памяти
    ~word() {
        delete[] randomWord;
    }

    // Метод для выбора случайного слова
    void selectRandomWord(const std::string& filename) {
        std::ifstream file(filename); // Открываем файл
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла" << std::endl;
            return;
        }

        std::vector<std::string> words; // Вектор для хранения слов
        std::string word;

        // Читаем все слова из файла
        while (file >> word) {
            words.push_back(word); // Добавляем каждый считанный токен в вектор
        }

        if (!words.empty()) {
            srand(static_cast<unsigned int>(time(nullptr))); // Инициализация генератора случайных чисел
            int randomIndex = rand() % words.size(); // Генерация случайного индекса

            length = words[randomIndex].length(); // Узнаем длину случайного слова
            randomWord = new char[length + 1]; // Выделяем память для массива (длина + 1 для '\0')

            strncpy(randomWord, words[randomIndex].c_str(), length); // Копируем слово в массив символов
            randomWord[length] = '\0'; // Обеспечиваем завершение строки нулем
        }
    }

    // Метод для получения слова
    const char* getRandomWord() const {
        return randomWord;
    }

    // Метод для получения длины слова
    int getLength() const {
        return length;
    }
};
//класс для ответа от пользователя
class answers
{
protected:
    int wronganswers;//кол-во неерных ответов
    int rightanswers;//кол-во верных
private:
    char answer;//буква от пользователя
    int tries; // Количество попыток
    const char* currentWord; // Текущее слово
public:
    // Конструктор
    answers() : answer(), wronganswers(0), rightanswers(0), tries(6), currentWord(nullptr) {}

    // Деструктор для освобождения памяти
    ~answers() {
    }
    // Метод для установки слова
    void setCurrentWord(const char* word) {
        currentWord = word;
    }
    // Метод для установки буквы от пользователя
    void setAnswer(char ans) {
        if ((ans >= 'А' && ans <= 'я')) {
            answer = tolower(ans); // Приводим к нижнему регистру
        }
    }
    void check(int wordLength, char* usedLetters, char* ansPeople) {
        int kol = 0; // Количество совпадений
        int kol1 = 0; // Количество использованных букв

        for (int i = 0; i < wordLength; i++) {
            if (answer == currentWord[i]) { // Сравнение без учета регистра
                kol += 1;
                ansPeople[i] = currentWord[i]; // Открываем букву в ansPeople
            }
        }
        for (int i = 0; i < strlen(usedLetters); i++) {
            if (answer == usedLetters[i]) { // Сравнение без учета регистра
                kol1 += 1;
                usedLetters[i] = '.'; // Убираем использованную букву
            }
        }
        // Проверка на правильный или неверный ответ
        if (kol > 0 && kol1 > 0) { // Верный ответ
            rightanswers += 1;
            std::cout << "Вы угадали букву: " << ansPeople << std::endl;
        }
        else { // Неверный ответ
            wronganswers += 1;
            std::cout << "Вы не угадали букву или уже использовали её: " << ansPeople << std::endl;
            tries = 6 - wronganswers; // Обновление количества оставшихся попыток
            std::cout << "У вас осталось " << tries << " попыток." << std::endl;
        }
    }
    int getRightAnswers() const {
        return rightanswers;
    }

    // Метод для получения количества неверных ответов
    int getWrongAnswers() const {
        return wronganswers;
    }
};
//структура для результата игры
class gameresult: public answers
{
private:
    int win;//кол-во выигрышей
    int loss;//кол-во проигрышей
    int winresult;//баллы при выигрыше
public:
    // Конструктор
    gameresult() : win(0), loss(6), winresult(0){

    }

    // Деструктор для освобождения памяти
    ~gameresult() {
    }
    int getRightAnswers() const {
        return rightanswers; // Доступ к переменной из базового класса
    }

    // Получение количества неверных ответов
    int getWrongAnswers() const {
        return wronganswers; // Доступ к переменной из базового класса
    }
    void kolwin()
    {
        win += 1;
    }
    int getWin() const
    {
        return win;
    }

    void kolloss()
    {
        loss += 1;
    }
    int getLoss() const {
        return loss;
    }

    void winres(){
        winresult = rightanswers + wronganswers;
    }
    int getWinResult() const {
        return winresult;
     }
};
