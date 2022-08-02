#include <iostream>
#include <fstream>

bool read_massiv(std::fstream& fin, int*& mass, int& item_count)
{
    const int min_el_count = 2; //минимальное количество элементов в исходном файле
    item_count = 0;             //Количество элементов в массиве

    while (!fin.eof())
    {
        if (fin >> item_count)
        {
            if (item_count >= min_el_count)
            {
                mass = new int[item_count];
                for (int i = 0; i < item_count; ++i)
                {
                    if (!(fin >> mass[i]))
                    {
                        std::cout << "Ошибка чтения " << i + 1 << " элемента" << std::endl;
                        delete[] mass;
                        mass = nullptr;
                        return false;
                    }
                }
                return true;
            }
            else //Считанное количество элементов меньше минимального
            {
                std::cout << "Считанное из файла количество элементов " << item_count << " меньше минимально допустимого " << min_el_count << std::endl;
                return false;
            }
        }
        else  //Ошибка чтения количества элементов в файле
        {
            std::cout << "Ошибка чтения количества элементов из исходного файла" << std::endl;
            return false;
        }
    }
    std::cout << "Считан конец файла до оканчания считывания всех элементов массива" << std::endl;
    return false;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    const std::string in_file_name = "in.txt";
    std::fstream fin(in_file_name, std::fstream::in);
    if (fin.is_open())
    {
        //Файл успешно открылся
        //Читаем содержимое исходного файла

        int* src1;                  //Исходный массив 1
        int* src2;                  //Исходный массив 2
        int item_count_1;           //Количество элементов в первом массиве
        int item_count_2;           //Количество элементов во втором массиве


        if (read_massiv(fin, src1, item_count_1) && read_massiv(fin, src2, item_count_2))
        {
            fin.close();
            const std::string out_file_name = "out.txt";
            std::fstream fout(out_file_name, std::fstream::out);
            if (fout.is_open())
            {
                //Выводим исходные массивы в выходной файл
                fout << item_count_2 << "\n" << src2[item_count_2 - 1] << " ";
                for (int i = 0; i < item_count_2 - 1; ++i)
                {
                    fout << src2[i] << " ";
                }
                fout << "\n" << item_count_1 << "\n";;

                for (int i = 1; i < item_count_1 - 1; ++i)
                {
                    fout << src1[i] << " ";
                }
                fout << item_count_1 << " " << src1[0] << std::endl;
                fout.close();
            }
            delete[] src1;
            src1 = nullptr;
            delete[] src2;
            src2 = nullptr;
        }
        else
        {
            fin.close();
            return 1;
        }
    }
    else  //Файл не открылся
    {
        std::cout << "Ошибка открытия исходного файла " << in_file_name << std::endl;
        return 10;
    }
    return 0;
}

