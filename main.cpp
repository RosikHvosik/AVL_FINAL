#include <iostream>
#include <string>
#include "avl.h"
#include "key.h"
#include "parsing.h"

int main() {
    AVL_tree tree;

    std::string inputFile = "Data.txt";
    std::string outputFile = "Output.txt";
    try {
        tree.readFromFile(inputFile);
        std::cout << "Данные успешно считаны из файла " << inputFile << ".\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при чтении файла: " << e.what() << std::endl;
        return 1;
    }


    std::cout << "\nДерево после чтения данных:\n";
    tree.printTree(tree.root);

    try {
        FIO fioToDelete("Опоров", "Иван", "Иванович");
        int lineToDelete = 3;
        bool heightDecreased = false;

        std::cout << "\nУдаляем элемент: " << fioToDelete.surname<<" "<<fioToDelete.name<<" "<<fioToDelete.patronymic<<" строка "<<lineToDelete<<"\n";
        tree.delete_node(fioToDelete,tree.root,heightDecreased, lineToDelete);

        std::cout << "\nДерево после удаления элемента:\n";
        tree.printTree(tree.root);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при удалении элемента: " << e.what() << std::endl;
    }

    try {
        tree.printToFile(outputFile);
        std::cout << "\nДанные успешно записаны в файл " << outputFile << ".\n"<<endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при записи файла: " << e.what() << std::endl;
        return 1;
    }
    FIO fioToSearch("Лидов","Иван","Иванович");
    std::cout<<"Элемент для поиска в дереве: "<<fioToSearch.surname<<" "<<fioToSearch.name<<" "<<fioToSearch.patronymic<<"\n"<< endl;
    tree.search(fioToSearch, tree.root);
    return 0;
}
/*
Иванов Иван Иванович
Петров Пётр Петрович
Сидоров Сергей Сергеевич
Кузнецова Мария Николаевна
Александров Александр Александрович
*/