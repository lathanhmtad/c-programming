#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <windows.h>

int convertFromStringToInteger(std::string str_number)
{
    int number = 0;
    for(int i = 0; i < str_number.length(); i++)
    {
        char ch = str_number[i];
        if(ch >= '0' && ch <= '9')
        {
            int digit;
            switch(ch)
            {
                case '0': digit = 0;break;
                case '1': digit = 1;break;
                case '2': digit = 2;break;
                case '3': digit = 3;break;
                case '4': digit = 4;break;
                case '5': digit = 5;break;
                case '6': digit = 6;break;
                case '7': digit = 7;break;
                case '8': digit = 8;break;
                case '9': digit = 9;break;
            }
            
            if(number == 0)
            {
                number = digit;
            }
            else
            {
                number = number * 10 + digit;
            }
        }
        else 
        {
            return 0;
        }
    }
    return number;
}

float convertFromStringToFloat(std::string strNumber)
{
    float number = 0;
    std::string str_integer_part;
    std::string str_real_part;
    bool start_of_real_part = false;
    for(int i = 0; i < strNumber.length(); i++)
    {
        char ch = strNumber[i];
        if(ch == '.')
        {
            start_of_real_part = true;
            continue;
        }
        
        if(ch >= '0' && ch <= '9')
        {
            if(start_of_real_part == false)
            {
                str_integer_part += ch;
            }
            else 
            {
                str_real_part += ch;
            }
        }
    }
    
    int integer_part = convertFromStringToInteger(str_integer_part);
    float real_part = convertFromStringToInteger(str_real_part);
    while(real_part > 1)
    {
        real_part  = (float)real_part/10;
    }
    number = integer_part + real_part;
    return number;
}

std::string convertFromNumberToString(int number)
{
    std::string strNumber = "";
    std::string digits[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    
    while(number !=0 )  
    {
        int i = number % 10;
        strNumber = digits[i] + strNumber;
        number /= 10;
    }
    return strNumber;
}

std::string convertFromNumberToString(float number, int precision)
{
    std::string strNumber = "";
    
    int intergerPart = number;
    strNumber = convertFromNumberToString(intergerPart);
    
    float realPart = number - intergerPart;
    for(int i = 0; i < precision; i++) 
    {
        realPart *= 10;
    }
    if(realPart == 0)
        return strNumber;
    strNumber += "." + convertFromNumberToString((int)realPart);
    return strNumber; 
}

struct Student 
{
    Student(std::string fn, int a, float p)
    {
        fullName = fn;
        age = a;
        point = p;
        next = NULL;
    }

    Student()
    {

    }

    std::string fullName;
    int age;
    float point;
    Student *next;

    // load các phuong th?c student t? file
    void load(std::string line) 
    {
        int i, posOfDelim;
        std::string delim, info;
        delim = ";";
        posOfDelim = 0;
        i = 0;
        do
        {
            posOfDelim = line.find(delim);
            info = line.substr(0, posOfDelim);
            switch (i)
            {
            case 0:
                fullName = info;
                break;
            case 1:
                age = convertFromStringToInteger(info);
                break;
            case 2:
                point = convertFromStringToFloat(info);
                break;
            }
            line = line.substr(posOfDelim + 1, line.length() - 1);
            i++;
        } while(posOfDelim != std::string::npos);
    }

    void print(int i)
    {
        std::cout << "\t| " << std::setw(2) << i << "    |" << " " << std::setw(29) << fullName << "|"
        << " " << std::setw(9) << age << "| " << std::setw(9) << point << "|" << "\n";
    }
};

void swap(Student *i, Student *j)
{
    std::string temp1;
    int temp2;
    float temp3;

    temp1 = i->fullName;
    temp2 = i->age;
    temp3 = i->point;

    i->age = j->age;
    i->fullName = j->fullName;
    i->point = j->point;

    j->fullName = temp1;
    j->age = temp2;
    j->point = temp3;
}

int strcmp(std::string s1, std::string s2)
{
    int lenMin = s1.length() < s2.length() ? s1.length() : s2.length();
    int res = 0;

    for(int i = 0; i < lenMin; i++)
    {
        res = s1[i] - s2[i];
        if(res != 0)
            break;
    }
    return res;
}

std::string nameSeperation(std::string str)
{
    std::string res = "";
    for(int i = str.length() - 1; i >= 0; i--)
    {
        if(str[i] == ' ')
        {
            for(int j = i + 1; j < str.length(); j++)
            {
                res += str[j];
            }
            break;
        }
    }

    if(res == "")
        return str;
    else
        return res;
}


// Danh sach lien ket
struct LinkedList 
{
    Student *head = NULL;

    void printAll()
    {
        Student *p = head;
        int i = 1;
        
        std::cout << std::left;
        std::cout << "\t+-------+------------------------------+----------+----------+\n";
        std::cout << "\t|STT    | Ho ten                       | Tuoi     | Diem     |\n";
        std::cout << "\t+-------+------------------------------+----------+----------+\n";
        while (p != NULL)
        {
            std::cout << "\t| " << std::setw(2) << i << "    |" << " " << std::setw(29) << p->fullName << "|"
            << " " << std::setw(9) << p->age << "| " << std::setw(9) << p->point << "|" << "\n";
            p = p->next;
            i++;
        }
        std::cout << "\t+-------+------------------------------+----------+----------+\n";      
    }

    void append(Student *s)
    {
        if(head == NULL)
        {
            head = s;
            return;
        }

        Student *p = head;
        while(p->next != NULL)
        {
            p = p->next;
        }
        p->next = s;
    }

    void fix(int num, int command)
    {
        int i = 1;
        Student *p = head;

        if(command == 1)
        {
            std::string newName;

            std::cin.ignore();
            std::cout << "\t(?) Nhap ten: "; getline(std::cin, newName);        
            while(p != NULL)
            {
                if(i == num)
                {
                    p->fullName = newName;
                    break;
                }
                i++;
                p = p->next;
            }
        }
        else if(command == 2)
        {
            int newAge;

            std::cout << "\t(?) Nhap tuoi: "; std::cin >> newAge;        
            while(p != NULL)
            {
                if(i == num)
                {
                    p->age = newAge;
                    break;
                }
                i++;
                p = p->next;
            }
        }
        else 
        {
            float newPoint;

            std::cout << "\t(?) Nhap diem: "; std::cin >> newPoint;        
            while(p != NULL)
            {
                if(i == num)
                {
                    p->point = newPoint;
                    break;
                }
                i++;
                p = p->next;
            }
        }
    }

    void remove(int pos)
    {
        int i = 0;
        Student *p = head;
        Student *p0;

        while(p != NULL)
        {
            if(i == pos)
            {
                if(i == 0)
                {
                    head = p->next;
                }
                else if(p != NULL)
                {
                    p0->next = p->next;
                }
                else
                {
                    p0->next = NULL;
                }
            }
            i++;
            p0 = p;
            p = p->next;
        }
    }

    void search(std::string str)
    {
        int count = 1;
        Student *p = head;

        while(p != NULL)
        {   
            if(p->fullName.find(str) != -1)
            {
                p->print(count);
                count++;
            }
            p = p->next;
        }
    }

    void arrange(int command)
    {
        Student *p = head;

        if(command == 1)
        {
            while(p != NULL)
            {
                for(Student *pNode = p->next; pNode != NULL; pNode = pNode->next)
                {
                    if(strcmp(nameSeperation(p->fullName), nameSeperation(pNode->fullName)) > 0)
                        swap(p, pNode);
                }
                p = p->next;
            }
            printAll();
        }
        else if(command == 2)
        {
            while(p != NULL)
            {
                for(Student *pNode = p->next; pNode != NULL; pNode = pNode->next)
                {
                    if(p->age > pNode->age)
                    {
                       swap(p, pNode);
                    }
                }
                p = p->next;
            }
            printAll();
        }
        else
        {
            while(p != NULL)
            {
                for(Student *pNode = p->next; pNode != NULL; pNode = pNode->next)
                {
                    if(p->point > pNode->point)
                    {
                       swap(p, pNode);
                    }
                }
                p = p->next;
            }
            printAll();
        } 
    }

    void statistical()
    {
        Student *p = head;
        int i = 0;
        float mediumScore = 0;
        while(p != NULL)
        {   
            mediumScore += p->point;
            i++;
            p = p->next;
        }
        std::cout << "\t(!) Diem trung binh ca lop: " << (float)mediumScore / i << "\n";

        i = 0;
        int j = 0;
        p = head;
        float percentage;
        while(p != NULL)
        {
            if(p->point >= 8)
                j++;
            i++;
            p = p->next;
        }
        percentage = j * 100 / i;
        std::cout << "\t(!) Ti le sinh vien gioi: " << percentage << "%" << "\n";

        i = 0;
        j = 0;
        p = head;
        while(p != NULL)
        {
            if(p->point >= 6 && p->point < 8)
                j++;
            i++;
            p = p->next;
        }
        percentage = j * 100 / i;
        std::cout << "\t(!) Ti le sinh vien kha: " << percentage << "%" << "\n";

        i = 0;
        j = 0;
        p = head;
        while(p != NULL)
        {
            if(p->point < 6)
                j++;
            i++;
            p = p->next;
        }
        percentage = j * 100 / i;
        std::cout << "\t(!) Ti le sinh vien kem: " << percentage << "%" << "\n";

        p = head;
        float max = 0;
        while(p != NULL)
        {
            if(p->point > max)
                max = p->point;
            p = p->next;
        }
        std::cout << "\t(!) Sinh vien diem cao nhat (" << (max) << ") la: " << "\n";

        p = head;
        while(p != NULL)
        {
            if(p->point >= max)
            {
                std::cout << "\t\t" << p->fullName << "\n";
            }
            p = p->next;
        }
    }

    void backup(std::string filename)
    {
        std::ofstream output;
        output.open("data.txt");
        Student *p = head;
        std::string content = "";

        while(p != NULL)
        {
            content += p->fullName + ";" + convertFromNumberToString(p->age) + ";" + convertFromNumberToString(p->point, 1) + "\n" ;
            p = p->next;
        }
        output << content;
        output.close();

    }

};

// load du lieu tu file
void loadData(std::string filename, LinkedList *studentList) 
{
    Student *s = new Student;
    std::ifstream input;
    input.open("Data.txt");
    std::string line;

    while(getline(input, line))
    {
        s->load(line);
        Student *student = new Student(s->fullName, s->age, s->point);
        studentList->append(student);
    }

    input.close();
} 

// phát tri?n thêm ch?c nang thêm bao nhiêu sinh viên
void addStudent(LinkedList *studentList) 
{
    Student *student = new Student;

    std::cin.ignore();
    std::cout << "\t(?) Nhap ten: "; getline(std::cin, student->fullName);
    std::cout << "\t(?) Nhap tuoi: "; std::cin >> student->age;
    std::cout << "\t(?) Nhap diem: "; std::cin >> student->point;
    student->next = NULL;

    studentList->append(student);

    std::cout << "\t(!) Da them sinh vien co ten: " << student->fullName << " , tuoi: " << student->age << " , diem: " << student->point << "\n"; 
}

void menu(LinkedList *list)
{
	int command;
    while(true)
    {
        // Xoá màn hình
        system("cls");

        std::cout << "Danh sach thao tac:\n";
        std::cout << "1 - In danh sach SV\n";
        std::cout << "2 - Them\n";
        std::cout << "3 - Sua\n";
        std::cout << "4 - Xoa\n";
        std::cout << "5 - Tim kiem\n";
        std::cout << "6 - Sap xep\n";
        std::cout << "7 - Thong ke\n";
        std::cout << "8 - Sao luu\n";
        std::cout << "9 - Thoat\n";

        std::cout << "Nhap lenh: "; std::cin >> command;

        // Ði ki?m tra l?u ch?n
        if(command != 1 && command != 2 && command != 3 && command != 4 && command != 5 && command != 6 && command != 7 && command != 8 && command != 9) 
        {
            std::cout << "Luu chon khong hop le. Xin kiem tra lai!\n";
            system("pause");
        }
        else if(command == 1)
        {
            std::cout << "[1] In danh sach sinh vien: \n";
            list->printAll();
            system("pause");    // D?ng màn hình d? xem
        }
        else if(command == 2)
        {
            std::cout << "[2] Them sinh vien: \n";
            addStudent(list); 
            system("pause");
        }
        else if(command == 3)
        {
            int n, select;
            std::cout << "[3] Sua thong tin sinh vien: \n";
            std::cout << "\t(?) Nhap STT cua sinh vien can sua: "; std::cin >> n;
            std::cout << "\t(!) Ban muon sua gi: \n";
            std::cout << "\t 1 - Ten\n";
            std::cout << "\t 2 - Tuoi\n";
            std::cout << "\t 3 - Diem\n";
        
            std::cout << "\t(?) Chon: "; std::cin >> select;

            list->fix(n, select);
            system("pause");
        }
        else if(command == 4)
        {
            int n;
            std::cout << "[4] Xoa sinh vien:\n";
            std::cout << "\t(?) Nhap STT: "; std::cin >> n;
            list->remove(n - 1);
            std::cout << "\t(!) Da xoa sinh vien co STT la " << n << "\n";
            system("pause");
        }
        else if(command == 5)
        {
            std::string characters;
            std::cout << "[5] Tim kiem\n";
            std::cin.ignore();
            std::cout << "\t(?) Nhap ki tu: "; getline(std::cin, characters);
            std::cout << std::left;
            std::cout << "\t+-------+------------------------------+----------+----------+\n";
            std::cout << "\t|STT    | Ho ten                       | Tuoi     | Diem     |\n";
            std::cout << "\t+-------+------------------------------+----------+----------+\n";
            list->search(characters);
            std::cout << "\t+-------+------------------------------+----------+----------+\n";      
            system("pause");
        }
        else if(command == 6)
        {
            int select;
            std::cout << "[6] Sap xep\n";
            std::cout << "\t(!) Sap xep the nao:\n";
            std::cout << "\t(!) 1 - Sap xep theo ten ABC\n";     
            std::cout << "\t(!) 2 - Sap xep theo tuoi tang dan\n";
            std::cout << "\t(!) 3 - Sap xep theo diem tang dan\n";

            std::cout << "\t(?) Chon: "; std::cin >> select;

            list->arrange(select);
            system("pause");
        }
        else if(command == 7)
        {
            std::cout << "[7] Thong ke\n";
            list->statistical();
            system("pause");
        }
        else if(command == 8)
        {
            std::cout << "[8] Luu thong tin\n";
            std::cout << "\t(!) Dang luu du lieu: ";
            for(int i = 0; i < 15; i++)
            {
                std::cout << "| ";
                Sleep(200);
            }
            list->backup("Data.txt");
            std::cout << "\n\t(!) Da luu du lieu thanh cong\n";
            system("pause");

        }
        else
            break;  
    };
}

int main()
{
    const std::string fileName = "Data.txt";
    LinkedList *studentList = new LinkedList;
    loadData(fileName, studentList);
	menu(studentList);
    return 0;
}
